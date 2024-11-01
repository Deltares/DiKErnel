// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util;
using ILGPU;
using ILGPU.Runtime;
using ILGPU.Runtime.Cuda;

namespace DiKErnel.GpuConsole
{
    internal static class AsphaltWaveImpactGpuCalculator
    {
        private static readonly float maximumPeakStressPartial = MathF.Pow(10, 6);

        public static DataResult<CalculationOutput> Calculate(IProfileData profileData,
                                                              IReadOnlyList<AsphaltWaveImpactLocationDependentInput>
                                                                  locationDependentInputItems,
                                                              IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                              CalculationMode locationCalculationMode = CalculationMode.Sequential)
        {
            try
            {
                Dictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems,
                                               timeDependentOutputItemsPerLocation, profileData,
                                               locationCalculationMode);

                List<LocationDependentOutput> locationDependentOutputItems =
                    locationDependentInputItems
                        .Select(ldi => ldi.GetLocationDependentOutput(timeDependentOutputItemsPerLocation[ldi]))
                        .ToList();

                return new DataResult<CalculationOutput>(new CalculationOutput(locationDependentOutputItems),
                                                         EventRegistry.Flush());
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event("An unhandled error occurred while performing the calculation. See stack " +
                                                 $"trace for more information:{Environment.NewLine}{e.Message}", EventType.Error));

                return new DataResult<CalculationOutput>(EventRegistry.Flush());
            }
        }

        private static void CalculateTimeStepsForLocations(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyCollection<AsphaltWaveImpactLocationDependentInput> locationDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, CalculationMode locationCalculationMode)
        {
            switch (locationCalculationMode)
            {
                case CalculationMode.Sequential:
                {
                    foreach (AsphaltWaveImpactLocationDependentInput locationDependentInput in locationDependentInputItems)
                    {
                        CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                      locationDependentInput);
                    }

                    break;
                }
                case CalculationMode.Parallel:
                {
                    Parallel.ForEach(locationDependentInputItems,
                                     (locationDependentInput, state, index) =>
                                     {
                                         CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation,
                                                                       profileData,
                                                                       locationDependentInput);
                                     });

                    break;
                }
                default:
                    throw new ArgumentOutOfRangeException(nameof(locationCalculationMode), locationCalculationMode, null);
            }
        }

        private static void CalculateTimeStepsForLocation(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            # region Location dependent output

            double z = profileData.GetVerticalHeight(locationDependentInput.X);

            double subLayerThickness;
            double subLayerElasticModulus;

            if (locationDependentInput.SubLayer != null)
            {
                subLayerThickness = locationDependentInput.SubLayer.Thickness;
                subLayerElasticModulus = locationDependentInput.SubLayer.ElasticModulus;
            }
            else
            {
                subLayerThickness = 0;
                subLayerElasticModulus = locationDependentInput.UpperLayer.ElasticModulus;
            }

            double logFlexuralStrength = AsphaltWaveImpactFunctions.LogFlexuralStrength(locationDependentInput.FlexuralStrength);

            double computationalThickness = AsphaltWaveImpactFunctions.ComputationalThickness(
                locationDependentInput.UpperLayer.Thickness, subLayerThickness, locationDependentInput.UpperLayer.ElasticModulus,
                subLayerElasticModulus);

            double stiffnessRelation = AsphaltWaveImpactFunctions.StiffnessRelation(
                computationalThickness, subLayerElasticModulus, locationDependentInput.SoilElasticity,
                locationDependentInput.StiffnessRelationNu);

            (double, double)? notchOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.NotchOuterBerm);
            (double, double)? crestOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.CrestOuterBerm);

            double horizontalPosition = locationDependentInput.X;
            if (notchOuterBerm != null && crestOuterBerm != null && horizontalPosition > crestOuterBerm.Value.Item1
                && horizontalPosition <= notchOuterBerm.Value.Item1)
            {
                horizontalPosition = crestOuterBerm.Value.Item1;
            }

            ProfileSegment profileSegment = profileData.GetProfileSegment(horizontalPosition);

            double outerSlope = AsphaltWaveImpactFunctions.OuterSlope(profileSegment.StartPoint.X, profileSegment.StartPoint.Z,
                                                                      profileSegment.EndPoint.X, profileSegment.EndPoint.Z);

            # endregion

            var input = new AsphaltWaveImpactGpuInput((float) logFlexuralStrength, (float) stiffnessRelation,
                                                      (float) computationalThickness, (float) outerSlope, (float) z,
                                                      (float) locationDependentInput.Fatigue.Alpha,
                                                      (float) locationDependentInput.Fatigue.Beta,
                                                      (float) locationDependentInput.AverageNumberOfWavesCtm,
                                                      (float) locationDependentInput.DensityOfWater,
                                                      (float) locationDependentInput.ImpactNumberC);

            var context = Context.Create(builder => builder.EnableAlgorithms().Cuda());
            Accelerator accelerator = context.GetPreferredDevice(preferCPU: false).CreateAccelerator(context);

            accelerator.PrintInformation();

            MemoryBuffer1D<TimeDependentGpuInput, Stride1D.Dense> timeDependentGpuInputItems =
                accelerator.Allocate1D(timeDependentInputItems
                                       .Select(tdi => new TimeDependentGpuInput((float) tdi.BeginTime, (float) tdi.EndTime,
                                                                                (float) tdi.WaterLevel, (float) tdi.WaveHeightHm0,
                                                                                (float) tdi.WavePeriodTm10, (float) tdi.WaveDirection))
                                       .ToArray());

            MemoryBuffer1D<AsphaltWaveImpactTimeDependentGpuOutput, Stride1D.Dense> timeDependentOutputItemsForLocation =
                accelerator.Allocate1D<AsphaltWaveImpactTimeDependentGpuOutput>(timeDependentInputItems.Count);

            MemoryBuffer1D<float, Stride1D.Dense> widthFactorValues =
                accelerator.Allocate1D(locationDependentInput.WidthFactors.Select(widthFactor => (float) widthFactor.Item1).ToArray());

            MemoryBuffer1D<float, Stride1D.Dense> widthFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.WidthFactors.Select(widthFactor => (float) widthFactor.Item2).ToArray());

            MemoryBuffer1D<float, Stride1D.Dense> depthFactorValues =
                accelerator.Allocate1D(locationDependentInput.DepthFactors.Select(depthFactor => (float) depthFactor.Item1).ToArray());

            MemoryBuffer1D<float, Stride1D.Dense> depthFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.DepthFactors.Select(depthFactor => (float) depthFactor.Item2).ToArray());

            MemoryBuffer1D<float, Stride1D.Dense> impactFactorValues =
                accelerator.Allocate1D(locationDependentInput.ImpactFactors.Select(impactFactor => (float) impactFactor.Item1).ToArray());

            MemoryBuffer1D<float, Stride1D.Dense> impactFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.ImpactFactors.Select(impactFactor => (float) impactFactor.Item2).ToArray());

            Action<Index1D, ArrayView<TimeDependentGpuInput>, ArrayView<AsphaltWaveImpactTimeDependentGpuOutput>, AsphaltWaveImpactGpuInput,
                    ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>>
                loadedKernel =
                    accelerator.LoadAutoGroupedStreamKernel(
                        (Index1D index,
                         ArrayView<TimeDependentGpuInput> timeInput,
                         ArrayView<AsphaltWaveImpactTimeDependentGpuOutput> timeOutput,
                         AsphaltWaveImpactGpuInput locationInput,
                         ArrayView<float> wfValues,
                         ArrayView<float> wfProbabilities,
                         ArrayView<float> dfValues,
                         ArrayView<float> dfProbabilities,
                         ArrayView<float> ifValues,
                         ArrayView<float> ifProbabilities) =>
                        {
                            timeOutput[index] = CalculateTimeStepForLocation(
                                timeInput[index],
                                locationInput.LogFlexuralStrength,
                                locationInput.StiffnessRelation,
                                locationInput.ComputationalThickness,
                                locationInput.OuterSlope,
                                wfValues,
                                wfProbabilities,
                                dfValues,
                                dfProbabilities,
                                ifValues,
                                ifProbabilities,
                                locationInput.Z,
                                locationInput.FatigueAlpha,
                                locationInput.FatigueBeta,
                                locationInput.AverageNumberOfWavesCtm,
                                locationInput.DensityOfWater, locationInput.ImpactNumberC);
                        });

            loadedKernel((int) timeDependentOutputItemsForLocation.Length, timeDependentGpuInputItems.View,
                         timeDependentOutputItemsForLocation.View, input, widthFactorValues.View, widthFactorProbabilities.View,
                         depthFactorValues.View, depthFactorProbabilities.View, impactFactorValues.View, impactFactorProbabilities.View);

            accelerator.Synchronize();

            for (var i = 0; i < timeDependentOutputItemsForLocation.View.Length; i++)
            {
                AsphaltWaveImpactTimeDependentGpuOutput asphaltWaveImpactTimeDependentGpuOutput =
                    timeDependentOutputItemsForLocation.View[i];

                timeDependentOutputItemsPerLocation[locationDependentInput].Add(
                    new AsphaltWaveImpactTimeDependentOutput(
                        new AsphaltWaveImpactTimeDependentOutputConstructionProperties
                        {
                            IncrementDamage = asphaltWaveImpactTimeDependentGpuOutput.IncrementDamage,
                            MaximumPeakStress = asphaltWaveImpactTimeDependentGpuOutput.MaximumPeakStress,
                            AverageNumberOfWaves = asphaltWaveImpactTimeDependentGpuOutput.AverageNumberOfWaves
                        }));
            }

            accelerator.Dispose();
            context.Dispose();
        }

        private static AsphaltWaveImpactTimeDependentGpuOutput CalculateTimeStepForLocation(
            TimeDependentGpuInput timeDependentInput, float logFlexuralStrength, float stiffnessRelation, float computationalThickness,
            float outerSlope, ArrayView<float> wfValues, ArrayView<float> wfProbabilities, ArrayView<float> dfValues,
            ArrayView<float> dfProbabilities, ArrayView<float> ifValues, ArrayView<float> ifProbabilities,
            float z, float fatigueAlpha, float fatigueBeta,
            float averageNumberOfWavesCtm, float densityOfWater, float impactNumberC)
        {
            float incrementTime = timeDependentInput.EndTime - timeDependentInput.BeginTime;

            float averageNumberOfWaves = incrementTime / (averageNumberOfWavesCtm * timeDependentInput.WavePeriodTm10);

            float maximumPeakStress = 9.81f * densityOfWater * timeDependentInput.WaveHeightHm0 / maximumPeakStressPartial;

            var input = new AsphaltWaveImpactIncrementDamageGpuInput(
                logFlexuralStrength, averageNumberOfWaves, maximumPeakStress, stiffnessRelation, computationalThickness, outerSlope,
                wfValues,
                wfProbabilities,
                dfValues,
                dfProbabilities,
                ifValues,
                ifProbabilities, z, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                fatigueAlpha, fatigueBeta, impactNumberC);

            float incrementDamage = AsphaltWaveImpactGpuFunctions.IncrementDamage(input);

            return new AsphaltWaveImpactTimeDependentGpuOutput(incrementDamage, maximumPeakStress, averageNumberOfWaves);
        }
    }
}
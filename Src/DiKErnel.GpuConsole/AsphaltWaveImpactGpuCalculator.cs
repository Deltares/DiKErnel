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
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util;
using ILGPU;
using ILGPU.Runtime;
using ILGPU.Runtime.CPU;

namespace DiKErnel.GpuConsole
{
    internal static class AsphaltWaveImpactGpuCalculator
    {
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

            var input = new AsphaltWaveImpactGpuInput(logFlexuralStrength, stiffnessRelation, computationalThickness, outerSlope, z,
                                                      locationDependentInput.Fatigue.Alpha, locationDependentInput.Fatigue.Beta,
                                                      locationDependentInput.AverageNumberOfWavesCtm,
                                                      locationDependentInput.DensityOfWater, locationDependentInput.ImpactNumberC);

            var context = Context.CreateDefault();
            Accelerator accelerator = context.CreateCPUAccelerator(0);

            MemoryBuffer1D<TimeDependentGpuInput, Stride1D.Dense> timeDependentGpuInputItems =
                accelerator.Allocate1D(timeDependentInputItems
                                       .Select(tdi => new TimeDependentGpuInput(tdi.BeginTime, tdi.EndTime, tdi.WaterLevel,
                                                                                tdi.WaveHeightHm0, tdi.WavePeriodTm10, tdi.WaveDirection))
                                       .ToArray());

            MemoryBuffer1D<AsphaltWaveImpactTimeDependentGpuOutput, Stride1D.Dense> timeDependentOutputItemsForLocation =
                accelerator.Allocate1D<AsphaltWaveImpactTimeDependentGpuOutput>(timeDependentInputItems.Count);

            MemoryBuffer1D<double, Stride1D.Dense> widthFactorValues =
                accelerator.Allocate1D(locationDependentInput.WidthFactors.Select(widthFactor => widthFactor.Item1).ToArray());

            MemoryBuffer1D<double, Stride1D.Dense> widthFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.WidthFactors.Select(widthFactor => widthFactor.Item2).ToArray());

            MemoryBuffer1D<double, Stride1D.Dense> depthFactorValues =
                accelerator.Allocate1D(locationDependentInput.DepthFactors.Select(depthFactor => depthFactor.Item1).ToArray());

            MemoryBuffer1D<double, Stride1D.Dense> depthFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.DepthFactors.Select(depthFactor => depthFactor.Item2).ToArray());

            MemoryBuffer1D<double, Stride1D.Dense> impactFactorValues =
                accelerator.Allocate1D(locationDependentInput.ImpactFactors.Select(impactFactor => impactFactor.Item1).ToArray());

            MemoryBuffer1D<double, Stride1D.Dense> impactFactorProbabilities =
                accelerator.Allocate1D(locationDependentInput.ImpactFactors.Select(impactFactor => impactFactor.Item2).ToArray());

            Action<Index1D, ArrayView<TimeDependentGpuInput>, ArrayView<AsphaltWaveImpactTimeDependentGpuOutput>, AsphaltWaveImpactGpuInput,
                    ArrayView<double>, ArrayView<double>, ArrayView<double>, ArrayView<double>, ArrayView<double>, ArrayView<double>>
                loadedKernel =
                    accelerator.LoadAutoGroupedStreamKernel(
                        (Index1D index,
                         ArrayView<TimeDependentGpuInput> timeInput,
                         ArrayView<AsphaltWaveImpactTimeDependentGpuOutput> timeOutput,
                         AsphaltWaveImpactGpuInput locationInput,
                         ArrayView<double> wfValues,
                         ArrayView<double> wfProbabilities,
                         ArrayView<double> dfValues,
                         ArrayView<double> dfProbabilities,
                         ArrayView<double> ifValues,
                         ArrayView<double> ifProbabilities) =>
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

            accelerator.Dispose();
            context.Dispose();

            timeDependentOutputItemsPerLocation[locationDependentInput].AddRange(
                timeDependentOutputItemsForLocation.Select(tdo => new AsphaltWaveImpactTimeDependentOutput(
                                                               new AsphaltWaveImpactTimeDependentOutputConstructionProperties
                                                               {
                                                                   IncrementDamage = tdo.IncrementDamage,
                                                                   MaximumPeakStress = tdo.MaximumPeakStress,
                                                                   AverageNumberOfWaves = tdo.AverageNumberOfWaves
                                                               })));
        }

        private static AsphaltWaveImpactTimeDependentGpuOutput CalculateTimeStepForLocation(
            TimeDependentGpuInput timeDependentInput, double logFlexuralStrength, double stiffnessRelation, double computationalThickness,
            double outerSlope, ArrayView<double> wfValues, ArrayView<double> wfProbabilities, ArrayView<double> dfValues,
            ArrayView<double> dfProbabilities, ArrayView<double> ifValues, ArrayView<double> ifProbabilities,
            double z, double fatigueAlpha, double fatigueBeta,
            double averageNumberOfWavesCtm, double densityOfWater, double impactNumberC)
        {
            double incrementTime = RevetmentFunctions.IncrementTime(
                timeDependentInput.BeginTime, timeDependentInput.EndTime);

            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(
                incrementTime, timeDependentInput.WavePeriodTm10, averageNumberOfWavesCtm);

            double maximumPeakStress = AsphaltWaveImpactFunctions.MaximumPeakStress(
                timeDependentInput.WaveHeightHm0, NaturalConstants.GravitationalAcceleration, densityOfWater);

            var input = new AsphaltWaveImpactIncrementDamageGpuInput(
                logFlexuralStrength, averageNumberOfWaves, maximumPeakStress, stiffnessRelation, computationalThickness, outerSlope,
                wfValues,
                wfProbabilities,
                dfValues,
                dfProbabilities,
                ifValues,
                ifProbabilities, z, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                fatigueAlpha, fatigueBeta, impactNumberC);

            double incrementDamage = AsphaltWaveImpactGpuFunctions.IncrementDamage(input);

            return new AsphaltWaveImpactTimeDependentGpuOutput(incrementDamage, maximumPeakStress, averageNumberOfWaves);
        }
    }
}
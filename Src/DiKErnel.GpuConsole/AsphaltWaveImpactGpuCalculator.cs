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
using ILGPU.Runtime.CPU;
using ILGPU.Runtime.Cuda;

namespace DiKErnel.GpuConsole
{
    internal static class AsphaltWaveImpactGpuCalculator
    {
        private static readonly float maximumPeakStressPartial = MathF.Pow(10, 6);

        public static DataResult<CalculationOutput> Calculate(
            IProfileData profileData, IReadOnlyList<AsphaltWaveImpactLocationDependentInput> locationDependentInputItems,
            IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
            CalculationMode locationCalculationMode = CalculationMode.Sequential)
        {
            try
            {
                Dictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems, timeDependentOutputItemsPerLocation,
                                               profileData, locationCalculationMode);

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
            InitializeLocationDependentOutput(
                profileData, locationDependentInput, out double z, out double logFlexuralStrength, out double computationalThickness,
                out double stiffnessRelation, out double outerSlope);

            InitializeLocationDependentStructsAndArrays(
                timeDependentInputItems, locationDependentInput, logFlexuralStrength, stiffnessRelation, computationalThickness, outerSlope,
                z, out AsphaltWaveImpactGpuInput asphaltWaveImpactGpuInput, out TimeDependentGpuInput[] timeDependentGpuInputItems,
                out float[] widthFactorValues, out float[] widthFactorProbabilities, out float[] depthFactorValues,
                out float[] depthFactorProbabilities, out float[] impactFactorValues, out float[] impactFactorProbabilities);

            AsphaltWaveImpactTimeDependentGpuOutput[] timeDependentOutputItemsForLocation =
                CalculateWithGpu(timeDependentGpuInputItems, asphaltWaveImpactGpuInput, widthFactorValues, widthFactorProbabilities,
                                 depthFactorValues, depthFactorProbabilities, impactFactorValues, impactFactorProbabilities);

            foreach (AsphaltWaveImpactTimeDependentGpuOutput asphaltWaveImpactTimeDependentGpuOutput in timeDependentOutputItemsForLocation)
            {
                timeDependentOutputItemsPerLocation[locationDependentInput].Add(
                    new AsphaltWaveImpactTimeDependentOutput(new AsphaltWaveImpactTimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = asphaltWaveImpactTimeDependentGpuOutput.IncrementDamage,
                        MaximumPeakStress = asphaltWaveImpactTimeDependentGpuOutput.MaximumPeakStress,
                        AverageNumberOfWaves = asphaltWaveImpactTimeDependentGpuOutput.AverageNumberOfWaves
                    }));
            }
        }

        private static void InitializeLocationDependentOutput(
            IProfileData profileData, AsphaltWaveImpactLocationDependentInput locationDependentInput, out double z,
            out double logFlexuralStrength, out float computationalThickness, out double stiffnessRelation, out double outerSlope)
        {
            z = profileData.GetVerticalHeight(locationDependentInput.X);

            float subLayerThickness;
            float subLayerElasticModulus;

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

            logFlexuralStrength = AsphaltWaveImpactFunctions.LogFlexuralStrength(locationDependentInput.FlexuralStrength);

            computationalThickness = AsphaltWaveImpactFunctions.ComputationalThickness(
                locationDependentInput.UpperLayer.Thickness, subLayerThickness, locationDependentInput.UpperLayer.ElasticModulus,
                subLayerElasticModulus);

            stiffnessRelation = AsphaltWaveImpactFunctions.StiffnessRelation(
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

            outerSlope = AsphaltWaveImpactFunctions.OuterSlope(
                (float) profileSegment.StartPoint.X, (float) profileSegment.StartPoint.Z, (float) profileSegment.EndPoint.X,
                (float) profileSegment.EndPoint.Z);
        }

        private static void InitializeLocationDependentStructsAndArrays(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            AsphaltWaveImpactLocationDependentInput locationDependentInput, double logFlexuralStrength, double stiffnessRelation,
            double computationalThickness, double outerSlope, double z, out AsphaltWaveImpactGpuInput asphaltWaveImpactGpuInput,
            out TimeDependentGpuInput[] timeDependentGpuInputItems, out float[] widthFactorValues, out float[] widthFactorProbabilities,
            out float[] depthFactorValues, out float[] depthFactorProbabilities, out float[] impactFactorValues,
            out float[] impactFactorProbabilities)
        {
            asphaltWaveImpactGpuInput = new AsphaltWaveImpactGpuInput(
                (float) logFlexuralStrength, (float) stiffnessRelation, (float) computationalThickness, (float) outerSlope, (float) z,
                (float) locationDependentInput.Fatigue.Alpha, (float) locationDependentInput.Fatigue.Beta,
                (float) locationDependentInput.AverageNumberOfWavesCtm, (float) locationDependentInput.DensityOfWater,
                (float) locationDependentInput.ImpactNumberC);

            timeDependentGpuInputItems = timeDependentInputItems
                                         .Select(tdi => new TimeDependentGpuInput(
                                                     (float) tdi.BeginTime, (float) tdi.EndTime,
                                                     (float) tdi.WaterLevel, (float) tdi.WaveHeightHm0,
                                                     (float) tdi.WavePeriodTm10, (float) tdi.WaveDirection))
                                         .ToArray();

            widthFactorValues = locationDependentInput.WidthFactors
                                                      .Select(widthFactor => (float) widthFactor.Item1)
                                                      .ToArray();

            widthFactorProbabilities = locationDependentInput.WidthFactors
                                                             .Select(widthFactor => (float) widthFactor.Item2)
                                                             .ToArray();

            depthFactorValues = locationDependentInput.DepthFactors
                                                      .Select(depthFactor => (float) depthFactor.Item1)
                                                      .ToArray();

            depthFactorProbabilities = locationDependentInput.DepthFactors
                                                             .Select(depthFactor => (float) depthFactor.Item2)
                                                             .ToArray();

            impactFactorValues = locationDependentInput.ImpactFactors
                                                       .Select(impactFactor => (float) impactFactor.Item1)
                                                       .ToArray();

            impactFactorProbabilities = locationDependentInput.ImpactFactors
                                                              .Select(impactFactor => (float) impactFactor.Item2)
                                                              .ToArray();
        }

        private static AsphaltWaveImpactTimeDependentGpuOutput[] CalculateWithGpu(
            TimeDependentGpuInput[] timeDependentGpuInputItems, AsphaltWaveImpactGpuInput asphaltWaveImpactGpuInput,
            float[] widthFactorValues, float[] widthFactorProbabilities, float[] depthFactorValues, float[] depthFactorProbabilities,
            float[] impactFactorValues, float[] impactFactorProbabilities)
        {
            using var context = Context.Create(builder => builder.EnableAlgorithms().Cuda());
            using Accelerator accelerator = context.GetPreferredDevice(preferCPU: false).CreateAccelerator(context);

            accelerator.PrintInformation();

            MemoryBuffer1D<AsphaltWaveImpactTimeDependentGpuOutput, Stride1D.Dense> timeDependentOutputItemsForLocationMemoryBuffer =
                accelerator.Allocate1D<AsphaltWaveImpactTimeDependentGpuOutput>(timeDependentGpuInputItems.Length);

            Action<Index1D, ArrayView<TimeDependentGpuInput>, ArrayView<AsphaltWaveImpactTimeDependentGpuOutput>, AsphaltWaveImpactGpuInput,
                    ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>, ArrayView<float>>
                loadedKernel = accelerator.LoadAutoGroupedStreamKernel(
                    (Index1D index, ArrayView<TimeDependentGpuInput> timeDependentGpuInput,
                     ArrayView<AsphaltWaveImpactTimeDependentGpuOutput> timeDependentGpuOutput,
                     AsphaltWaveImpactGpuInput locationDependentGpuInput, ArrayView<float> widthFactorValuesArrayView,
                     ArrayView<float> widthFactorProbabilitiesArrayView, ArrayView<float> depthFactorValuesArrayView,
                     ArrayView<float> depthFactorProbabilitiesArrayView, ArrayView<float> impactFactorValuesArrayView,
                     ArrayView<float> impactFactorProbabilitiesArrayView) =>
                    {
                        timeDependentGpuOutput[index] = CalculateTimeStepForLocation(
                            timeDependentGpuInput[index], locationDependentGpuInput.LogFlexuralStrength,
                            locationDependentGpuInput.StiffnessRelation, locationDependentGpuInput.ComputationalThickness,
                            locationDependentGpuInput.OuterSlope, widthFactorValuesArrayView, widthFactorProbabilitiesArrayView,
                            depthFactorValuesArrayView, depthFactorProbabilitiesArrayView, impactFactorValuesArrayView,
                            impactFactorProbabilitiesArrayView, locationDependentGpuInput.Z, locationDependentGpuInput.FatigueAlpha,
                            locationDependentGpuInput.FatigueBeta, locationDependentGpuInput.AverageNumberOfWavesCtm,
                            locationDependentGpuInput.DensityOfWater, locationDependentGpuInput.ImpactNumberC);
                    });

            loadedKernel(timeDependentGpuInputItems.Length, accelerator.Allocate1D(timeDependentGpuInputItems).View,
                         timeDependentOutputItemsForLocationMemoryBuffer.View, asphaltWaveImpactGpuInput,
                         accelerator.Allocate1D(widthFactorValues).View, accelerator.Allocate1D(widthFactorProbabilities).View,
                         accelerator.Allocate1D(depthFactorValues).View, accelerator.Allocate1D(depthFactorProbabilities).View,
                         accelerator.Allocate1D(impactFactorValues).View, accelerator.Allocate1D(impactFactorProbabilities).View);

            accelerator.Synchronize();

            var timeDependentOutputItemsForLocation = new AsphaltWaveImpactTimeDependentGpuOutput[timeDependentGpuInputItems.Length];

            timeDependentOutputItemsForLocationMemoryBuffer.CopyToCPU(timeDependentOutputItemsForLocation);

            return timeDependentOutputItemsForLocation;
        }

        private static AsphaltWaveImpactTimeDependentGpuOutput[] CalculateWithCpu(
            TimeDependentGpuInput[] timeDependentGpuInputItems, AsphaltWaveImpactGpuInput asphaltWaveImpactGpuInput,
            float[] widthFactorValues, float[] widthFactorProbabilities, float[] depthFactorValues, float[] depthFactorProbabilities,
            float[] impactFactorValues, float[] impactFactorProbabilities)
        {
            using var context = Context.Create(builder => builder.CPU());
            using Accelerator accelerator = context.GetPreferredDevice(preferCPU: true).CreateAccelerator(context);

            accelerator.PrintInformation();

            var timeDependentOutputItemsForLocation = new AsphaltWaveImpactTimeDependentGpuOutput[timeDependentGpuInputItems.Length];

            Parallel.ForEach(timeDependentGpuInputItems,
                             (timeDependentGpuInput, state, index) =>
                             {
                                 timeDependentOutputItemsForLocation[index] = CalculateTimeStepForLocation(
                                     timeDependentGpuInput, asphaltWaveImpactGpuInput.LogFlexuralStrength,
                                     asphaltWaveImpactGpuInput.StiffnessRelation, asphaltWaveImpactGpuInput.ComputationalThickness,
                                     asphaltWaveImpactGpuInput.OuterSlope, accelerator.Allocate1D(widthFactorValues).View,
                                     accelerator.Allocate1D(widthFactorProbabilities).View, accelerator.Allocate1D(depthFactorValues).View,
                                     accelerator.Allocate1D(depthFactorProbabilities).View, accelerator.Allocate1D(impactFactorValues).View,
                                     accelerator.Allocate1D(impactFactorProbabilities).View, asphaltWaveImpactGpuInput.Z,
                                     asphaltWaveImpactGpuInput.FatigueAlpha, asphaltWaveImpactGpuInput.FatigueBeta,
                                     asphaltWaveImpactGpuInput.AverageNumberOfWavesCtm, asphaltWaveImpactGpuInput.DensityOfWater,
                                     asphaltWaveImpactGpuInput.ImpactNumberC);
                             });

            accelerator.Synchronize();

            return timeDependentOutputItemsForLocation;
        }

        private static AsphaltWaveImpactTimeDependentGpuOutput CalculateTimeStepForLocation(
            TimeDependentGpuInput timeDependentInput, float logFlexuralStrength, float stiffnessRelation, float computationalThickness,
            float outerSlope, ArrayView<float> widthFactorValues, ArrayView<float> widthFactorProbabilities,
            ArrayView<float> depthFactorValues, ArrayView<float> depthFactorProbabilities, ArrayView<float> impactFactorValues,
            ArrayView<float> impactFactorProbabilities, float z, float fatigueAlpha, float fatigueBeta, float averageNumberOfWavesCtm,
            float densityOfWater, float impactNumberC)
        {
            float incrementTime = timeDependentInput.EndTime - timeDependentInput.BeginTime;

            float averageNumberOfWaves = incrementTime / (averageNumberOfWavesCtm * timeDependentInput.WavePeriodTm10);

            float maximumPeakStress = 9.81f * densityOfWater * timeDependentInput.WaveHeightHm0 / maximumPeakStressPartial;

            var input = new AsphaltWaveImpactIncrementDamageGpuInput(
                logFlexuralStrength, averageNumberOfWaves, maximumPeakStress, stiffnessRelation, computationalThickness, outerSlope,
                widthFactorValues,
                widthFactorProbabilities,
                depthFactorValues,
                depthFactorProbabilities,
                impactFactorValues,
                impactFactorProbabilities, z, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                fatigueAlpha, fatigueBeta, impactNumberC);

            float incrementDamage = AsphaltWaveImpactGpuFunctions.IncrementDamage(input);

            return new AsphaltWaveImpactTimeDependentGpuOutput(incrementDamage, maximumPeakStress, averageNumberOfWaves);
        }
    }
}
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
    internal static class AsphaltWaveImpactCalculator
    {
        public static DataResult<CalculationOutput> Calculate(
            IProfileData profileData, IReadOnlyList<AsphaltWaveImpactLocationDependentInput> locationDependentInputItems,
            IReadOnlyList<ITimeDependentInput> timeDependentInputItems)
        {
            try
            {
                Dictionary<AsphaltWaveImpactLocationDependentInput, List<AsphaltWaveImpactTimeDependentOutput>>
                    timeDependentOutputItemsPerLocation =
                        locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<AsphaltWaveImpactTimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems, timeDependentOutputItemsPerLocation,
                                               profileData);

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
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<AsphaltWaveImpactTimeDependentOutput>>
                timeDependentOutputItemsPerLocation, IProfileData profileData)
        {
            foreach (AsphaltWaveImpactLocationDependentInput locationDependentInput in locationDependentInputItems)
            {
                CalculateTimeStepsForLocationOnGpu(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                   locationDependentInput);
            }
        }

        private static void CalculateTimeStepsForLocationOnCpu(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<AsphaltWaveImpactTimeDependentOutput>>
                timeDependentOutputItemsPerLocation, IProfileData profileData,
            AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            List<AsphaltWaveImpactTimeDependentOutput> timeDependentOutputItemsForLocation =
                timeDependentOutputItemsPerLocation[locationDependentInput];

            timeDependentOutputItemsForLocation.AddRange(new AsphaltWaveImpactTimeDependentOutput[timeDependentInputItems.Count]);

            TimeDependentInputStruct[] timeDependentInputStructs = timeDependentInputItems.Select(tdi => new TimeDependentInputStruct(
                                                                                                  tdi.BeginTime, tdi.EndTime,
                                                                                                  tdi.WaterLevel,
                                                                                                  tdi.WaveHeightHm0, tdi.WavePeriodTm10,
                                                                                                  tdi.WaveDirection))
                                                                                          .ToArray();

            CalculateLocationDependentOutput(profileData, locationDependentInput, out double z, out double logFlexuralStrength,
                                             out double computationalThickness, out double stiffnessRelation, out double outerSlope);

            Parallel.ForEach(timeDependentInputStructs,
                             (timeDependentInputStruct, state, index) =>
                             {
                                 timeDependentOutputItemsForLocation[(int) index] = CalculateTimeDependentOutput(
                                     timeDependentInputStruct, locationDependentInput.AverageNumberOfWavesCtm,
                                     locationDependentInput.DensityOfWater, logFlexuralStrength, stiffnessRelation, computationalThickness,
                                     outerSlope, locationDependentInput.WidthFactors, locationDependentInput.DepthFactors,
                                     locationDependentInput.ImpactFactors, z, locationDependentInput.Fatigue.Alpha,
                                     locationDependentInput.Fatigue.Beta, locationDependentInput.ImpactNumberC);
                             });
        }

        private static void CalculateTimeStepsForLocationOnGpu(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<AsphaltWaveImpactTimeDependentOutput>>
                timeDependentOutputItemsPerLocation, IProfileData profileData,
            AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            List<AsphaltWaveImpactTimeDependentOutput> timeDependentOutputItemsForLocation =
                timeDependentOutputItemsPerLocation[locationDependentInput];

            timeDependentOutputItemsForLocation.AddRange(new AsphaltWaveImpactTimeDependentOutput[timeDependentInputItems.Count]);

            CalculateLocationDependentOutput(profileData, locationDependentInput, out double z, out double logFlexuralStrength,
                                             out double computationalThickness, out double stiffnessRelation, out double outerSlope);

            var context = Context.CreateDefault();
            Accelerator accelerator = context.CreateCPUAccelerator(0);

            MemoryBuffer1D<TimeDependentInputStruct, Stride1D.Dense> timeDependentInputStructs = accelerator.Allocate1D(
                timeDependentInputItems.Select(tdi => new TimeDependentInputStruct(tdi.BeginTime, tdi.EndTime, tdi.WaterLevel,
                                                                                   tdi.WaveHeightHm0, tdi.WavePeriodTm10,
                                                                                   tdi.WaveDirection))
                                       .ToArray());

            MemoryBuffer1D<AsphaltWaveImpactTimeDependentOutputStruct, Stride1D.Dense> timeDependentOutputStructs =
                accelerator.Allocate1D<AsphaltWaveImpactTimeDependentOutputStruct>(timeDependentInputItems.Count);

            Action<Index1D, ArrayView<TimeDependentInputStruct>, ArrayView<AsphaltWaveImpactTimeDependentOutputStruct>> loadedKernel =
                accelerator.LoadAutoGroupedStreamKernel(
                    (Index1D i, ArrayView<TimeDependentInputStruct> inputStructs,
                     ArrayView<AsphaltWaveImpactTimeDependentOutputStruct> outputStructs) =>
                    {
                        outputStructs[i] = CalculateTimeDependentOutput(
                            inputStructs[i], locationDependentInput.AverageNumberOfWavesCtm, locationDependentInput.DensityOfWater,
                            logFlexuralStrength, stiffnessRelation, computationalThickness, outerSlope, locationDependentInput.WidthFactors,
                            locationDependentInput.DepthFactors, locationDependentInput.ImpactFactors, z,
                            locationDependentInput.Fatigue.Alpha, locationDependentInput.Fatigue.Beta,
                            locationDependentInput.ImpactNumberC);
                    });

            loadedKernel((int) timeDependentOutputStructs.Length, timeDependentInputStructs.View, timeDependentOutputStructs.View);

            accelerator.Synchronize();

            accelerator.Dispose();
            context.Dispose();
        }

        private static void CalculateLocationDependentOutput(IProfileData profileData,
                                                             AsphaltWaveImpactLocationDependentInput locationDependentInput,
                                                             out double z, out double logFlexuralStrength,
                                                             out double computationalThickness, out double stiffnessRelation,
                                                             out double outerSlope)
        {
            z = profileData.GetVerticalHeight(locationDependentInput.X);

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

            logFlexuralStrength = AsphaltWaveImpactFunctions.LogFlexuralStrength(locationDependentInput.FlexuralStrength);

            computationalThickness = AsphaltWaveImpactFunctions.ComputationalThickness(locationDependentInput.UpperLayer.Thickness,
                                                                                       subLayerThickness,
                                                                                       locationDependentInput.UpperLayer.ElasticModulus,
                                                                                       subLayerElasticModulus);

            stiffnessRelation = AsphaltWaveImpactFunctions.StiffnessRelation(computationalThickness, subLayerElasticModulus,
                                                                             locationDependentInput.SoilElasticity,
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

            outerSlope = AsphaltWaveImpactFunctions.OuterSlope(profileSegment.StartPoint.X, profileSegment.StartPoint.Z,
                                                               profileSegment.EndPoint.X, profileSegment.EndPoint.Z);
        }

        private static AsphaltWaveImpactTimeDependentOutputStruct CalculateTimeDependentOutput(
            TimeDependentInputStruct timeDependentInput, double averageNumberOfWavesCtm, double densityOfWater,
            double logFlexuralStrength, double stiffnessRelation, double computationalThickness, double outerSlope,
            IReadOnlyList<(double, double)> widthFactors, IReadOnlyList<(double, double)> depthFactors,
            IReadOnlyList<(double, double)> impactFactors, double z, double fatigueAlpha, double fatigueBeta, double impactNumberC)
        {
            double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime, timeDependentInput.EndTime);

            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                                  timeDependentInput.WavePeriodTm10,
                                                                                  averageNumberOfWavesCtm);

            double maximumPeakStress = AsphaltWaveImpactFunctions.MaximumPeakStress(timeDependentInput.WaveHeightHm0,
                                                                                    NaturalConstants.GravitationalAcceleration,
                                                                                    densityOfWater);

            var input = new AsphaltWaveImpactInput(logFlexuralStrength, averageNumberOfWaves, maximumPeakStress, stiffnessRelation,
                                                   computationalThickness, outerSlope, widthFactors, depthFactors, impactFactors, z,
                                                   timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0, fatigueAlpha,
                                                   fatigueBeta, impactNumberC);

            double incrementDamage = AsphaltWaveImpactFunctions.IncrementDamage(input);

            return new AsphaltWaveImpactTimeDependentOutputStruct(incrementDamage, maximumPeakStress, averageNumberOfWaves);
        }
    }

    internal struct TimeDependentInputStruct
    {
        public TimeDependentInputStruct(double beginTime, double endTime, double waterLevel, double waveHeightHm0,
                                        double wavePeriodTm10, double waveDirection)
        {
            BeginTime = beginTime;
            EndTime = endTime;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            WaveDirection = waveDirection;
        }

        public double BeginTime { get; }

        public double EndTime { get; }

        public double WaterLevel { get; }

        public double WaveHeightHm0 { get; }

        public double WavePeriodTm10 { get; }

        public double WaveDirection { get; }
    }

    internal struct AsphaltWaveImpactTimeDependentOutputStruct
    {
        public AsphaltWaveImpactTimeDependentOutputStruct(double incrementDamage, double maximumPeakStress, double averageNumberOfWaves)
        {
            IncrementDamage = incrementDamage;
            MaximumPeakStress = maximumPeakStress;
            AverageNumberOfWaves = averageNumberOfWaves;
        }

        public double IncrementDamage { get; }

        public double MaximumPeakStress { get; }

        public double AverageNumberOfWaves { get; }
    }
}
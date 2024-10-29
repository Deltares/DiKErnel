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
using DiKErnel.Util;

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
                locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                              locationDependentInput);
            }
        }

        private static void CalculateTimeStepsForLocation(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<AsphaltWaveImpactTimeDependentOutput>>
                timeDependentOutputItemsPerLocation, IProfileData profileData,
            AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            List<AsphaltWaveImpactTimeDependentOutput> timeDependentOutputItemsForLocation =
                timeDependentOutputItemsPerLocation[locationDependentInput];

            timeDependentOutputItemsForLocation.AddRange(new AsphaltWaveImpactTimeDependentOutput[timeDependentInputItems.Count]);

            Parallel.ForEach(timeDependentInputItems,
                             (timeDependentInput, state, index) =>
                             {
                                 timeDependentOutputItemsForLocation[(int) index] = CalculateTimeStepForLocation(
                                     timeDependentInput, locationDependentInput, profileData);
                             });
        }

        private static AsphaltWaveImpactTimeDependentOutput CalculateTimeStepForLocation(
            ITimeDependentInput timeDependentInput, AsphaltWaveImpactLocationDependentInput locationDependentInput,
            IProfileData profileData, double damageAtStartOfCalculation = double.NaN)
        {
            return (AsphaltWaveImpactTimeDependentOutput) locationDependentInput.Calculate(
                timeDependentInput, profileData, damageAtStartOfCalculation);
        }

        private static AsphaltWaveImpactTimeDependentOutput CalculateTimeDependentOutput(
            ITimeDependentInput timeDependentInput, IProfileData profileData, double averageNumberOfWavesCtm, double densityOfWater,
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

            return new AsphaltWaveImpactTimeDependentOutput(new AsphaltWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                MaximumPeakStress = maximumPeakStress,
                AverageNumberOfWaves = averageNumberOfWaves
            });
        }
    }
}
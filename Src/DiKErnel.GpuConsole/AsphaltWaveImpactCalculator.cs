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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Util;

namespace DiKErnel.GpuConsole
{
    internal static class AsphaltWaveImpactCalculator
    {
        public static DataResult<CalculationOutput> Calculate(IProfileData profileData,
                                                              IReadOnlyList<AsphaltWaveImpactLocationDependentInput> locationDependentInputItems,
                                                              IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                              CalculationMode locationCalculationMode = CalculationMode.Sequential,
                                                              CalculationMode timeStepCalculationMode = CalculationMode.Sequential)
        {
            try
            {
                if (locationDependentInputItems.Any(ldi => ldi.RequiresDamageAtStartOfCalculation) &&
                    timeStepCalculationMode != CalculationMode.Sequential)
                {
                    throw new InvalidOperationException("Trying to calculate time steps for one or more locations in parallel while this " +
                                                        "is not possible; output of one time step is input for the next time step...");
                }

                Dictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems,
                                               timeDependentOutputItemsPerLocation, profileData,
                                               locationCalculationMode, timeStepCalculationMode);

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
            IReadOnlyCollection<ILocationDependentInput> locationDependentInputItems,
            IReadOnlyDictionary<AsphaltWaveImpactLocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, CalculationMode locationCalculationMode, CalculationMode timeStepCalculationMode)
        {
            switch (locationCalculationMode)
            {
                case CalculationMode.Sequential:
                {
                    foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                    {
                        locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                        CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                      locationDependentInput, timeStepCalculationMode);
                    }

                    break;
                }
                case CalculationMode.Parallel:
                {
                    Parallel.ForEach(locationDependentInputItems,
                                     (locationDependentInput, state, index) =>
                                     {
                                         locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                                         CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation,
                                                                       profileData,
                                                                       locationDependentInput, timeStepCalculationMode);
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
            IProfileData profileData, ILocationDependentInput locationDependentInput, CalculationMode timeStepCalculationMode)
        {
            List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

            switch (timeStepCalculationMode)
            {
                case CalculationMode.Sequential:
                {
                    double currentDamage = locationDependentInput.InitialDamage;

                    foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                    {
                        TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(
                            timeDependentInput, locationDependentInput, profileData, currentDamage);

                        if (!double.IsNaN(timeDependentOutput.IncrementDamage))
                        {
                            currentDamage += timeDependentOutput.IncrementDamage;
                        }

                        timeDependentOutputItemsForLocation.Add(timeDependentOutput);
                    }

                    break;
                }
                case CalculationMode.Parallel:
                {
                    timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                    Parallel.ForEach(timeDependentInputItems,
                                     (timeDependentInput, state, index) =>
                                     {
                                         timeDependentOutputItemsForLocation[(int) index] = CalculateTimeStepForLocation(
                                             timeDependentInput, locationDependentInput, profileData);
                                     });

                    break;
                }
                default:
                    throw new ArgumentOutOfRangeException(nameof(timeStepCalculationMode), timeStepCalculationMode, null);
            }
        }

        private static TimeDependentOutput CalculateTimeStepForLocation(ITimeDependentInput timeDependentInput,
                                                                        ILocationDependentInput locationDependentInput,
                                                                        IProfileData profileData,
                                                                        double damageAtStartOfCalculation = double.NaN)
        {
            return locationDependentInput.Calculate(timeDependentInput, profileData, damageAtStartOfCalculation);
        }
    }
}
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
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.Core
{
    /// <summary>
    /// Class responsible for performing calculations.
    /// </summary>
    public static class Calculator
    {
        /// <summary>
        /// Performs a calculation.
        /// </summary>
        /// <param name="calculationInput">The input used for the calculation.</param>
        /// <param name="locationCalculationMode">The calculation mode while iterating multiple locations.</param>
        /// <param name="timeStepCalculationMode">The calculation mode while iterating the time steps of each location.</param>
        /// <returns>The result of the calculation.</returns>
        public static DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput,
                                                              CalculationMode locationCalculationMode = CalculationMode.FullyParallel,
                                                              CalculationMode timeStepCalculationMode = CalculationMode.FullyParallel)
        {
            try
            {
                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems = calculationInput.LocationDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems,
                                               timeDependentOutputItemsPerLocation, calculationInput.ProfileData,
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
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, CalculationMode locationCalculationMode, CalculationMode timeStepCalculationMode)
        {
            switch (locationCalculationMode)
            {
                case CalculationMode.FullySequential:
                {
                    foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                    {
                        locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                        CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                      locationDependentInput, timeStepCalculationMode);
                    }

                    break;
                }
                case CalculationMode.FullyParallel:
                {
                    Parallel.For(0, locationDependentInputItems.Count,
                                 i =>
                                 {
                                     ILocationDependentInput locationDependentInput = locationDependentInputItems.ElementAt(i);

                                     locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                                     CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation,
                                                                   profileData,
                                                                   locationDependentInput, timeStepCalculationMode);
                                 });

                    break;
                }
                case CalculationMode.ParallelChunks:
                {
                    OrderablePartitioner<Tuple<int, int>> rangePartitioner = Partitioner.Create(0, locationDependentInputItems.Count);

                    Parallel.ForEach(rangePartitioner, (range, loopState) =>
                    {
                        for (int i = range.Item1; i < range.Item2; i++)
                        {
                            ILocationDependentInput locationDependentInput = locationDependentInputItems.ElementAt(i);

                            locationDependentInput.InitializeDerivedLocationDependentInput(profileData);

                            CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                          locationDependentInput, timeStepCalculationMode);
                        }
                    });

                    break;
                }
                default:
                    throw new ArgumentOutOfRangeException(nameof(locationCalculationMode), locationCalculationMode, null);
            }
        }

        private static void CalculateTimeStepsForLocation(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, ILocationDependentInput locationDependentInput, CalculationMode timeStepCalculationMode)
        {
            List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

            switch (timeStepCalculationMode)
            {
                case CalculationMode.FullySequential:
                {
                    double currentDamage = locationDependentInput.InitialDamage;

                    foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                    {
                        TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(
                            timeDependentInput, locationDependentInput, profileData, currentDamage);

                        currentDamage += timeDependentOutput.IncrementDamage;

                        timeDependentOutputItemsForLocation.Add(timeDependentOutput);
                    }

                    break;
                }
                case CalculationMode.FullyParallel:
                {
                    timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                    Parallel.For(0, timeDependentInputItems.Count,
                                 i =>
                                 {
                                     timeDependentOutputItemsForLocation[i] = CalculateTimeStepForLocation(
                                         timeDependentInputItems.ElementAt(i), locationDependentInput, profileData);
                                 });

                    break;
                }
                case CalculationMode.ParallelChunks:
                {
                    timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                    OrderablePartitioner<Tuple<int, int>> rangePartitioner = Partitioner.Create(0, timeDependentInputItems.Count);

                    Parallel.ForEach(rangePartitioner, (range, loopState) =>
                    {
                        for (int i = range.Item1; i < range.Item2; i++)
                        {
                            timeDependentOutputItemsForLocation[i] = CalculateTimeStepForLocation(
                                timeDependentInputItems.ElementAt(i), locationDependentInput, profileData);
                        }
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
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
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.Core
{
    /// <summary>
    /// Class responsible for performing calculations.
    /// </summary>
    public class Calculator
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInput">The input used in the calculation.</param>
        /// <remarks>While creating the new instance, the calculation is directly started.</remarks>
        public Calculator(ICalculationInput calculationInput)
        {
            Result = Calculate(calculationInput);
        }

        /// <summary>
        /// Gets the state of the calculation.
        /// </summary>
        public CalculationState CalculationState { get; private set; } = CalculationState.Running;

        /// <summary>
        /// Gets the result of the calculation.
        /// </summary>
        public DataResult<CalculationOutput> Result { get; }

        private DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput)
        {
            try
            {
                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems = calculationInput.LocationDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems,
                                               timeDependentOutputItemsPerLocation, calculationInput.ProfileData);

                if (CalculationState == CalculationState.Cancelled)
                {
                    return new DataResult<CalculationOutput>(EventRegistry.Flush());
                }

                CalculationState = CalculationState.FinishedSuccessfully;

                List<LocationDependentOutput> locationDependentOutputItems =
                    locationDependentInputItems
                        .Select(ldi => ldi.GetLocationDependentOutput(timeDependentOutputItemsPerLocation[ldi]))
                        .ToList();

                return new DataResult<CalculationOutput>(new CalculationOutput(locationDependentOutputItems),
                                                         EventRegistry.Flush());
            }
            catch (Exception e)
            {
                CalculationState = CalculationState.FinishedInError;

                EventRegistry.Register(new Event("An unhandled error occurred while performing the calculation. See stack " +
                                                 $"trace for more information:{Environment.NewLine}{e.Message}", EventType.Error));

                return new DataResult<CalculationOutput>(EventRegistry.Flush());
            }
        }

        private void CalculateTimeStepsForLocations(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyCollection<ILocationDependentInput> locationDependentInputItems,
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData)
        {
            foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
            {
                foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                {
                    if (CalculationState == CalculationState.Cancelled)
                    {
                        break;
                    }

                    List<TimeDependentOutput> currentOutputItems = timeDependentOutputItemsPerLocation[locationDependentInput];

                    currentOutputItems.Add(CalculateTimeStepForLocation(timeDependentInput, locationDependentInput,
                                                                        currentOutputItems, profileData));
                }
            }
        }

        private static TimeDependentOutput CalculateTimeStepForLocation(ITimeDependentInput timeDependentInput,
                                                                        ILocationDependentInput locationDependentInput,
                                                                        IReadOnlyList<TimeDependentOutput> currentOutputItems,
                                                                        IProfileData profileData)
        {
            double initialDamage = currentOutputItems.Count == 0
                                       ? locationDependentInput.InitialDamage
                                       : currentOutputItems[currentOutputItems.Count - 1].Damage;

            return locationDependentInput.Calculate(initialDamage, timeDependentInput, profileData);
        }
    }
}
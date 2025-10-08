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
using DiKErnel.Util;

namespace DiKErnel.Core
{
    /// <summary>
    /// Class responsible for performing calculations.
    /// </summary>
    public class Calculator
    {
        private readonly CalculatorSettings calculatorSettings;
        private readonly Task<DataResult<CalculationOutput>> task;

        private double progress;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculatorSettings">The settings to use during the calculations (optional).</param>
        public Calculator(CalculatorSettings calculatorSettings = null)
        {
            this.calculatorSettings = calculatorSettings ?? new CalculatorSettings();
        }

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInput">The input used in the calculation.</param>
        /// <remarks>While creating the new instance, the thread that performs the
        /// calculation is directly started (and can be waited for to finish by calling
        /// <see cref="WaitForCompletion"/>).</remarks>
        public Calculator(ICalculationInput calculationInput)
        {
            task = new Task<DataResult<CalculationOutput>>(() => CalculateTimeStepsForLocations(calculationInput));

            task.Start();
        }

        /// <summary>
        /// Gets the state of the calculation.
        /// </summary>
        public CalculationState CalculationState { get; private set; } = CalculationState.Running;

        /// <summary>
        /// Gets the current progress of the calculation [%].
        /// </summary>
        /// <remarks>This method also returns the current progress when the calculation is
        /// cancelled.</remarks>
        public int Progress => (int) Math.Round(progress * 100);

        /// <summary>
        /// Gets the result of the calculation.
        /// </summary>
        /// <remarks>An actual result is returned when the calculation is finished
        /// successfully, cancelled or finished in error. When the calculation is still
        /// running, <c>null</c> is returned.</remarks>
        public DataResult<CalculationOutput> Result => CalculationState != CalculationState.Running ? task.Result : null;

        /// <summary>
        /// Performs a calculation.
        /// </summary>
        /// <param name="calculationInput">The input used for the calculation.</param>
        /// <returns>The result of the calculation.</returns>
        public DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput)
        {
            return CalculateTimeStepsForLocations(calculationInput);
        }

        /// <summary>
        /// Handle that enables a calling instance to wait for the calculation to complete.
        /// </summary>
        public void WaitForCompletion()
        {
            task.Wait();
        }

        private DataResult<CalculationOutput> CalculateTimeStepsForLocations(ICalculationInput calculationInput)
        {
            try
            {
                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems = calculationInput.LocationDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems,
                                               timeDependentOutputItemsPerLocation, calculationInput.ProfileData);

                if (ShouldCancel())
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
            double progressPerIteration = 1d / timeDependentInputItems.Count / locationDependentInputItems.Count;

            foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
            {
                if (ShouldCancel())
                {
                    break;
                }

                foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                {
                    if (ShouldCancel())
                    {
                        break;
                    }

                    List<TimeDependentOutput> currentOutputItems = timeDependentOutputItemsPerLocation[locationDependentInput];

                    currentOutputItems.Add(CalculateTimeStepForLocation(timeDependentInput, locationDependentInput,
                                                                        currentOutputItems, profileData));

                    progress += progressPerIteration;
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

        private bool ShouldCancel()
        {
            return calculatorSettings.ShouldCancel != null && calculatorSettings.ShouldCancel();
        }
    }
}
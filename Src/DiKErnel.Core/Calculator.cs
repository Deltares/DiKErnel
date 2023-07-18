// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
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
    /// Class responsible for performing calculations on a separate thread.
    /// </summary>
    public class Calculator
    {
        private readonly Task<DataResult<CalculationOutput>> task;

        private double progress;
        private CalculationState calculationState = CalculationState.Running;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInput">The input used in the calculation.</param>
        public Calculator(ICalculationInput calculationInput)
        {
            task = new Task<DataResult<CalculationOutput>>(() => Calculate(calculationInput, ref progress, ref calculationState));

            task.Start();
        }

        /// <summary>
        /// Gets the state of the calculation.
        /// </summary>
        public CalculationState CalculationState => calculationState;

        /// <summary>
        /// Gets the current progress of the calculation [%].
        /// </summary>
        /// <remarks>Also returns the current progress when the calculation is
        /// cancelled.</remarks>
        public int Progress => (int) Math.Round(progress * 100);

        /// <summary>
        /// Gets the result of the calculator.
        /// </summary>
        /// <remarks>The result of the operation is returned after being finished
        /// successfully, cancelled or finished in error. When the calculation is still
        /// running, <c>null</c> is returned.</remarks>
        public DataResult<CalculationOutput> Result => task.Result;

        /// <summary>
        /// Handle that enables a calling instance to wait for the calculation to complete.
        /// </summary>
        public void WaitForCompletion()
        {
            task.Wait();
        }

        /// <summary>
        /// Cancels the calculation.
        /// </summary>
        /// <remarks>A calculation can only be cancelled when it is actually still
        /// running.</remarks>
        public void Cancel()
        {
            if (CalculationState == CalculationState.Running)
            {
                calculationState = CalculationState.Cancelled;
            }
        }

        private static DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput, ref double progress,
                                                               ref CalculationState calculationState)
        {
            DataResult<CalculationOutput> result;

            try
            {
                IProfileData profileData = calculationInput.ProfileData;
                ITimeDependentInput[] timeDependentInputItems = calculationInput.TimeDependentInputItems.ToArray();
                ILocationDependentInput[] locationDependentInputItems = calculationInput.LocationDependentInputItems.ToArray();

                double progressPerCalculationStep = 1.0 / timeDependentInputItems.Length / locationDependentInputItems.Length;

                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                {
                    foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                    {
                        if (calculationState == CalculationState.Cancelled)
                        {
                            break;
                        }

                        List<TimeDependentOutput> currentOutputItems = timeDependentOutputPerLocation[locationDependentInput];

                        currentOutputItems.Add(CreateTimeDependentOutput(currentOutputItems, locationDependentInput,
                                                                         timeDependentInput, profileData));

                        progress += progressPerCalculationStep;
                    }
                }

                if (calculationState == CalculationState.Cancelled)
                {
                    result = new DataResult<CalculationOutput>(EventRegistry.Flush());
                }
                else
                {
                    IEnumerable<LocationDependentOutput> locationDependentOutputItems = locationDependentInputItems
                        .Select(ldi => ldi.GetLocationDependentOutput(timeDependentOutputPerLocation[ldi]));

                    result = new DataResult<CalculationOutput>(new CalculationOutput(locationDependentOutputItems),
                                                               EventRegistry.Flush());

                    calculationState = CalculationState.FinishedSuccessfully;
                }
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event("An unhandled error occurred while performing the calculation. See stack " +
                                                 "trace for more information:\n" + e.Message, EventType.Error));

                result = new DataResult<CalculationOutput>(EventRegistry.Flush());

                calculationState = CalculationState.FinishedInError;
            }

            return result;
        }

        private static TimeDependentOutput CreateTimeDependentOutput(IEnumerable<TimeDependentOutput> currentOutputItems,
                                                                     ILocationDependentInput locationDependentInput,
                                                                     ITimeDependentInput timeDependentInput,
                                                                     IProfileData profileData)
        {
            double initialDamage = currentOutputItems.LastOrDefault()?.Damage ?? locationDependentInput.InitialDamage;

            return locationDependentInput.Calculate(initialDamage, timeDependentInput, profileData);
        }
    }
}
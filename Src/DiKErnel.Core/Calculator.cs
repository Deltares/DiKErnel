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

namespace DiKErnel.Core
{
    /// <summary>
    /// Class responsible for performing calculations.
    /// </summary>
    public class Calculator
    {
        private readonly CalculatorSettings calculatorSettings;

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
        /// Gets the state of the calculation.
        /// </summary>
        public CalculationState CalculationState { get; private set; } = CalculationState.Running;

        /// <summary>
        /// Performs a calculation.
        /// </summary>
        /// <param name="calculationInput">The input used for the calculation.</param>
        /// <returns>The result of the calculation.</returns>
        public ICalculationResult Calculate(ICalculationInput calculationInput)
        {
            ReportProgress();

            return CalculateTimeStepsForLocations(calculationInput);
        }

        private ICalculationResult CalculateTimeStepsForLocations(ICalculationInput calculationInput)
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
                    return new CancellationResult();
                }

                CalculationState = CalculationState.FinishedSuccessfully;

                List<LocationDependentOutput> locationDependentOutputItems =
                    locationDependentInputItems
                        .Select(ldi => ldi.GetLocationDependentOutput(timeDependentOutputItemsPerLocation[ldi]))
                        .ToList();

                return new SuccessResult(new CalculationOutput(locationDependentOutputItems));
            }
            catch (Exception e)
            {
                CalculationState = CalculationState.FinishedInError;

                LogErrorMessage("An unhandled error occurred while performing the calculation. See stack trace for more information:" +
                                $"{Environment.NewLine}{e.Message}");

                return new FailureResult();
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
                    return;
                }

                foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                {
                    if (ShouldCancel())
                    {
                        return;
                    }

                    List<TimeDependentOutput> currentOutputItems = timeDependentOutputItemsPerLocation[locationDependentInput];

                    currentOutputItems.Add(CalculateTimeStepForLocation(timeDependentInput, locationDependentInput,
                                                                        currentOutputItems, profileData));

                    IncrementAndReportProgress(progressPerIteration);
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

        private void ReportProgress()
        {
            calculatorSettings.ProgressHandler?.Report((int) Math.Round(progress * 100));
        }

        private void IncrementAndReportProgress(double progressPerIteration)
        {
            progress += progressPerIteration;

            ReportProgress();
        }

        private void LogErrorMessage(string message)
        {
            calculatorSettings.LogHandler?.Error(message);
        }
    }
}
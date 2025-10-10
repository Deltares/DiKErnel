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
    public static class Calculator
    {
        /// <summary>
        /// Performs a calculation.
        /// </summary>
        /// <param name="calculationInput">The input used for the calculation.</param>
        /// <param name="calculatorSettings">The settings used for the calculation (optional).</param>
        /// <returns>The result of the calculation.</returns>
        public static ICalculationResult Calculate(ICalculationInput calculationInput, CalculatorSettings calculatorSettings = null)
        {
            try
            {
                var progress = 0.0;

                ReportProgress(progress, calculatorSettings);

                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems = calculationInput.LocationDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems, timeDependentOutputItemsPerLocation,
                                               calculationInput.ProfileData, ref progress, calculatorSettings);

                if (ShouldCancel(calculatorSettings))
                {
                    return new CancellationResult();
                }

                List<LocationDependentOutput> locationDependentOutputItems =
                    locationDependentInputItems
                        .Select(ldi => ldi.GetLocationDependentOutput(timeDependentOutputItemsPerLocation[ldi]))
                        .ToList();

                return new SuccessResult(new CalculationOutput(locationDependentOutputItems));
            }
            catch (Exception e)
            {
                LogErrorMessage("An unhandled error occurred while performing the calculation. See stack trace for more information:" +
                                $"{Environment.NewLine}{e.Message}", calculatorSettings);

                return new FailureResult();
            }
        }

        private static void CalculateTimeStepsForLocations(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyCollection<ILocationDependentInput> locationDependentInputItems,
            Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, ref double currentProgress, CalculatorSettings calculatorSettings)
        {
            double progressPerIteration = 1d / timeDependentInputItems.Count / locationDependentInputItems.Count;

            foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
            {
                List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

                double currentDamage = locationDependentInput.InitialDamage;

                foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                {
                    if (ShouldCancel(calculatorSettings))
                    {
                        return;
                    }

                    TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(
                        timeDependentInput, locationDependentInput, profileData, currentDamage);

                    currentDamage += timeDependentOutput.IncrementDamage;

                    timeDependentOutputItemsForLocation.Add(timeDependentOutput);

                    currentProgress += progressPerIteration;

                    ReportProgress(currentProgress, calculatorSettings);
                }
            }
        }

        private static TimeDependentOutput CalculateTimeStepForLocation(ITimeDependentInput timeDependentInput,
                                                                        ILocationDependentInput locationDependentInput,
                                                                        IProfileData profileData,
                                                                        double damageAtStartOfCalculation = double.NaN)
        {
            return locationDependentInput.Calculate(timeDependentInput, profileData, damageAtStartOfCalculation);
        }

        private static void ReportProgress(double progress, CalculatorSettings calculatorSettings)
        {
            var percentage = (int) Math.Round(progress * 100);

            calculatorSettings?.ProgressHandler?.Report(percentage);
        }

        private static bool ShouldCancel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.ShouldCancel != null && calculatorSettings.ShouldCancel();
        }

        private static void LogErrorMessage(string message, CalculatorSettings calculatorSettings)
        {
            calculatorSettings?.LogHandler?.Error(message);
        }
    }
}
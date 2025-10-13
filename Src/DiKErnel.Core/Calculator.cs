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
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems = calculationInput.LocationDependentInputItems;

                if (ShouldCalculateTimeStepsInParallel(calculatorSettings)
                    && locationDependentInputItems.Any(ldi => ldi.CalculateIsStateful))
                {
                    LogWarningMessage("The calculation is configured to run time steps in parallel but for on or more locations this is " +
                                      "not possible; the output of previous time steps is used as input for the next time step, so these " +
                                      "calculations are forced to be performed chronologically.", calculatorSettings);
                }

                var progress = 0.0;

                ReportProgress(progress, calculatorSettings);

                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                CalculateTimeStepsForLocations(timeDependentInputItems, locationDependentInputItems, timeDependentOutputItemsPerLocation,
                                               calculationInput.ProfileData, calculatorSettings, ref progress);

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
            finally
            {
                if (ShouldCalculateLocationsInParallel(calculatorSettings))
                {
                    ReportProgress(1, calculatorSettings);
                }
            }
        }

        private static void CalculateTimeStepsForLocations(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyCollection<ILocationDependentInput> locationDependentInputItems,
            Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation, IProfileData profileData,
            CalculatorSettings calculatorSettings, ref double currentProgress)
        {
            if (ShouldCalculateLocationsInParallel(calculatorSettings))
            {
                Parallel.ForEach(locationDependentInputItems,
                                 (locationDependentInput, state, index) =>
                                 {
                                     locationDependentInput.Initialize(profileData);

                                     CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation,
                                                                   profileData, locationDependentInput, calculatorSettings);
                                 });
            }
            else
            {
                double progressPerLocation = 1d / locationDependentInputItems.Count;

                foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                {
                    locationDependentInput.Initialize(profileData);

                    CalculateTimeStepsForLocation(timeDependentInputItems, timeDependentOutputItemsPerLocation, profileData,
                                                  locationDependentInput, calculatorSettings, ref currentProgress, progressPerLocation);

                    if (ShouldCalculateTimeStepsInParallel(calculatorSettings))
                    {
                        currentProgress += progressPerLocation;

                        ReportProgress(currentProgress, calculatorSettings);
                    }
                }
            }
        }

        private static void CalculateTimeStepsForLocation(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, ILocationDependentInput locationDependentInput, CalculatorSettings calculatorSettings)
        {
            List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

            if (ShouldCalculateTimeStepsInParallel(calculatorSettings) && !locationDependentInput.CalculateIsStateful)
            {
                timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                Parallel.ForEach(timeDependentInputItems,
                                 (timeDependentInput, state, index) =>
                                 {
                                     timeDependentOutputItemsForLocation[(int) index] = CalculateTimeStepForLocation(
                                         timeDependentInput, locationDependentInput, profileData);
                                 });
            }
            else
            {
                foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                {
                    if (ShouldCancel(calculatorSettings))
                    {
                        return;
                    }

                    TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(timeDependentInput, locationDependentInput,
                                                                                           profileData);

                    timeDependentOutputItemsForLocation.Add(timeDependentOutput);
                }
            }
        }

        private static void CalculateTimeStepsForLocation(
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems,
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IProfileData profileData, ILocationDependentInput locationDependentInput, CalculatorSettings calculatorSettings,
            ref double currentProgress, double progressPerLocation)
        {
            List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

            if (ShouldCalculateTimeStepsInParallel(calculatorSettings) && !locationDependentInput.CalculateIsStateful)
            {
                timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                Parallel.ForEach(timeDependentInputItems,
                                 (timeDependentInput, state, index) =>
                                 {
                                     timeDependentOutputItemsForLocation[(int) index] = CalculateTimeStepForLocation(
                                         timeDependentInput, locationDependentInput, profileData);
                                 });
            }
            else
            {
                double progressPerTimeStep = progressPerLocation / timeDependentInputItems.Count;

                foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                {
                    if (ShouldCancel(calculatorSettings))
                    {
                        return;
                    }

                    TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(timeDependentInput, locationDependentInput,
                                                                                           profileData);

                    timeDependentOutputItemsForLocation.Add(timeDependentOutput);

                    currentProgress += progressPerTimeStep;

                    ReportProgress(currentProgress, calculatorSettings);
                }
            }
        }

        private static TimeDependentOutput CalculateTimeStepForLocation(ITimeDependentInput timeDependentInput,
                                                                        ILocationDependentInput locationDependentInput,
                                                                        IProfileData profileData)
        {
            return locationDependentInput.Calculate(timeDependentInput, profileData);
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

        private static bool ShouldCalculateLocationsInParallel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.CalculateLocationsInParallel ?? false;
        }

        private static bool ShouldCalculateTimeStepsInParallel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.CalculateTimeStepsInParallel ?? false;
        }

        private static void LogWarningMessage(string message, CalculatorSettings calculatorSettings)
        {
            calculatorSettings?.LogHandler?.LogWarning(message);
        }

        private static void LogErrorMessage(string message, CalculatorSettings calculatorSettings)
        {
            calculatorSettings?.LogHandler?.LogError(message);
        }
    }
}
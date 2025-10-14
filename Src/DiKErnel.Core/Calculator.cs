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
                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
                Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation =
                    locationDependentInputItems.ToDictionary(ldi => ldi, ldi => new List<TimeDependentOutput>());

                if (CalculateTimeStepsInParallel(calculatorSettings) && locationDependentInputItems.Any(ldi => ldi.CalculateIsStateful))
                {
                    LogWarning("The calculation is configured to run time steps in parallel but for on or more locations this is " +
                               "not possible; the output of previous time steps is used as input for the next time step, so these " +
                               "calculations are forced to be performed chronologically.", calculatorSettings);
                }

                ProgressIncrementHandler progressIncrementHandler = calculatorSettings?.ProgressHandler != null
                                                                        ? new ProgressIncrementHandler(calculatorSettings.ProgressHandler,
                                                                            locationDependentInputItems.Count,
                                                                            timeDependentInputItems.Count)
                                                                        : null;

                progressIncrementHandler?.ReportCalculationStarted();

                CalculateTimeStepsForLocations(locationDependentInputItems, timeDependentOutputItemsPerLocation, timeDependentInputItems,
                                               calculationInput.ProfileData, calculatorSettings, progressIncrementHandler);

                if (ShouldCancel(calculatorSettings))
                {
                    return new CancellationResult();
                }

                if (CalculateLocationsInParallel(calculatorSettings))
                {
                    progressIncrementHandler?.ReportCalculationEnded();
                }

                return new SuccessResult(new CalculationOutput(locationDependentInputItems
                                                               .Select(ldi => ldi.GetLocationDependentOutput(timeDependentInputItems,
                                                                           timeDependentOutputItemsPerLocation[ldi]))
                                                               .ToList()));
            }
            catch (Exception e)
            {
                LogError("An unhandled error occurred while performing the calculation. See stack trace for more information:" +
                         $"{Environment.NewLine}{e.Message}", calculatorSettings);

                return new FailureResult();
            }
        }

        private static void CalculateTimeStepsForLocations(
            IReadOnlyCollection<ILocationDependentInput> locationDependentInputItems,
            Dictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems, IProfileData profileData,
            CalculatorSettings calculatorSettings, ProgressIncrementHandler progressIncrementHandler)
        {
            if (CalculateLocationsInParallel(calculatorSettings))
            {
                Parallel.ForEach(locationDependentInputItems,
                                 (locationDependentInput, state, index) =>
                                 {
                                     try
                                     {
                                         if (ShouldCancel(calculatorSettings))
                                         {
                                             state.Stop();
                                             return;
                                         }

                                         locationDependentInput.Initialize(profileData);

                                         CalculateTimeStepsForLocation(locationDependentInput, timeDependentOutputItemsPerLocation,
                                                                       timeDependentInputItems, profileData, calculatorSettings);
                                     }
                                     catch (Exception)
                                     {
                                         state.Stop();
                                         throw;
                                     }
                                 });
            }
            else
            {
                foreach (ILocationDependentInput locationDependentInput in locationDependentInputItems)
                {
                    if (ShouldCancel(calculatorSettings))
                    {
                        return;
                    }

                    locationDependentInput.Initialize(profileData);

                    CalculateTimeStepsForLocation(locationDependentInput, timeDependentOutputItemsPerLocation, timeDependentInputItems,
                                                  profileData, calculatorSettings, progressIncrementHandler);

                    if (!ShouldCancel(calculatorSettings)
                        && CalculateTimeStepsInParallel(calculatorSettings)
                        && !locationDependentInput.CalculateIsStateful)
                    {
                        progressIncrementHandler?.ReportLocationCalculated();
                    }
                }
            }
        }

        private static void CalculateTimeStepsForLocation(
            ILocationDependentInput locationDependentInput,
            IReadOnlyDictionary<ILocationDependentInput, List<TimeDependentOutput>> timeDependentOutputItemsPerLocation,
            IReadOnlyCollection<ITimeDependentInput> timeDependentInputItems, IProfileData profileData,
            CalculatorSettings calculatorSettings, ProgressIncrementHandler progressIncrementHandler = null)
        {
            List<TimeDependentOutput> timeDependentOutputItemsForLocation = timeDependentOutputItemsPerLocation[locationDependentInput];

            if (CalculateTimeStepsInParallel(calculatorSettings) && !locationDependentInput.CalculateIsStateful)
            {
                timeDependentOutputItemsForLocation.AddRange(new TimeDependentOutput[timeDependentInputItems.Count]);

                Parallel.ForEach(timeDependentInputItems,
                                 (timeDependentInput, state, index) =>
                                 {
                                     try
                                     {
                                         if (ShouldCancel(calculatorSettings))
                                         {
                                             state.Stop();
                                             return;
                                         }

                                         timeDependentOutputItemsForLocation[(int) index] = CalculateTimeStepForLocation(
                                             locationDependentInput, timeDependentInput, profileData);
                                     }
                                     catch (Exception)
                                     {
                                         state.Stop();
                                         throw;
                                     }
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

                    TimeDependentOutput timeDependentOutput = CalculateTimeStepForLocation(locationDependentInput, timeDependentInput,
                                                                                           profileData);

                    timeDependentOutputItemsForLocation.Add(timeDependentOutput);

                    progressIncrementHandler?.ReportTimeStepCalculated();
                }
            }
        }

        private static TimeDependentOutput CalculateTimeStepForLocation(ILocationDependentInput locationDependentInput,
                                                                        ITimeDependentInput timeDependentInput, IProfileData profileData)
        {
            return locationDependentInput.Calculate(timeDependentInput, profileData);
        }

        private static bool ShouldCancel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.ShouldCancel != null && calculatorSettings.ShouldCancel();
        }

        private static bool CalculateLocationsInParallel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.CalculateLocationsInParallel ?? false;
        }

        private static bool CalculateTimeStepsInParallel(CalculatorSettings calculatorSettings)
        {
            return calculatorSettings?.CalculateTimeStepsInParallel ?? false;
        }

        private static void LogWarning(string message, CalculatorSettings calculatorSettings)
        {
            calculatorSettings?.LogHandler?.LogWarning(message);
        }

        private static void LogError(string message, CalculatorSettings calculatorSettings)
        {
            calculatorSettings?.LogHandler?.LogError(message);
        }

        private class ProgressIncrementHandler
        {
            private readonly IProgress<int> progressHandler;
            private readonly double progressIncrementPerLocation;
            private readonly double progressIncrementPerTimeStep;

            private double progress;
            private int reportedProgress = -1;

            public ProgressIncrementHandler(IProgress<int> progressHandler, double numberOfLocations, double numberOfTimeSteps)
            {
                this.progressHandler = progressHandler;
                progressIncrementPerLocation = 1d / numberOfLocations;
                progressIncrementPerTimeStep = progressIncrementPerLocation / numberOfTimeSteps;
            }

            public void ReportCalculationStarted()
            {
                SetAndReportProgress(0);
            }

            public void ReportLocationCalculated()
            {
                SetAndReportProgress(progress + progressIncrementPerLocation);
            }

            public void ReportTimeStepCalculated()
            {
                SetAndReportProgress(progress + progressIncrementPerTimeStep);
            }

            public void ReportCalculationEnded()
            {
                SetAndReportProgress(1);
            }

            private void SetAndReportProgress(double progressToSet)
            {
                progress = progressToSet;

                var progressToReport = (int) Math.Round(progress * 100);

                if (progressToReport == reportedProgress)
                {
                    return;
                }

                progressHandler.Report(progressToReport);

                reportedProgress = progressToReport;
            }
        }
    }
}
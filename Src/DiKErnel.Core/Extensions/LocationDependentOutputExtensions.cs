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

using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;

namespace DiKErnel.Core.Extensions
{
    /// <summary>
    /// Extension methods for <see cref="LocationDependentOutput"/>.
    /// </summary>
    public static class LocationDependentOutputExtensions
    {
        /// <summary>
        /// Gets the calculated damages.
        /// </summary>
        /// <param name="locationDependentOutput">The location dependent output.</param>
        /// <param name="initialDamage">The initial damage.</param>
        /// <returns>The calculated damages for the location dependent output.</returns>
        public static IReadOnlyList<double> GetDamages(this LocationDependentOutput locationDependentOutput, double initialDamage)
        {
            var damages = new List<double>();

            double currentDamage = initialDamage;

            foreach (TimeDependentOutput timeDependentOutput in locationDependentOutput.TimeDependentOutputItems)
            {
                currentDamage += timeDependentOutput.IncrementDamage;

                damages.Add(currentDamage);
            }

            return damages;
        }

        /// <summary>
        /// Gets the calculated time of failure.
        /// </summary>
        /// <param name="locationDependentOutput">The location dependent output.</param>
        /// <param name="initialDamage">The initial damage.</param>
        /// <param name="failureNumber">The failure number.</param>
        /// <param name="timeDependentInputItems">The time dependent input items.</param>
        /// <returns>The calculated time of failure for the location dependent output, or <c>null</c> when:
        /// <list type="bullet">
        /// <item>the revetment at the location did not fail;</item>
        /// <item>one or more of the calculated damages equal <c>NaN</c>.</item>
        /// </list>
        /// </returns>
        public static double? GetTimeOfFailure(this LocationDependentOutput locationDependentOutput, double initialDamage,
                                               double failureNumber, IReadOnlyList<ITimeDependentInput> timeDependentInputItems)
        {
            IReadOnlyList<double> damages = locationDependentOutput.GetDamages(initialDamage);

            if (damages.Any(double.IsNaN))
            {
                return null;
            }

            double? timeOfFailure = null;

            for (var i = 0; i < timeDependentInputItems.Count; i++)
            {
                if (FailureRevetment(damages[i], initialDamage, failureNumber))
                {
                    ITimeDependentInput timeDependentInput = timeDependentInputItems[i];

                    double durationInTimeStepFailure = DurationInTimeStepFailure(
                        IncrementTime(timeDependentInput.BeginTime, timeDependentInput.EndTime),
                        locationDependentOutput.TimeDependentOutputItems[i].IncrementDamage, failureNumber, initialDamage);

                    timeOfFailure = TimeOfFailure(durationInTimeStepFailure, timeDependentInput.BeginTime);
                }
            }

            return timeOfFailure;
        }

        private static bool FailureRevetment(double damage, double initialDamage, double failureNumber)
        {
            return initialDamage < failureNumber && damage >= failureNumber;
        }

        private static double DurationInTimeStepFailure(double incrementTime, double incrementDamage, double failureNumber,
                                                        double initialDamage)
        {
            return (failureNumber - initialDamage) / incrementDamage * incrementTime;
        }

        private static double IncrementTime(double beginTime, double endTime)
        {
            return endTime - beginTime;
        }

        private static double TimeOfFailure(double durationInTimeStepFailure, double beginTime)
        {
            return durationInTimeStepFailure + beginTime;
        }
    }
}
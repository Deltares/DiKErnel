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
        /// Gets the time of failure.
        /// </summary>
        /// <param name="locationDependentOutput">The location dependent output.</param>
        /// <param name="initialDamage">The initial damage.</param>
        /// <param name="failureNumber">The failure number.</param>
        /// <param name="timeDependentInputItems">The time dependent input items.</param>
        /// <returns>The time of failure for the location dependent output, or <c>null</c> when:
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

            for (var i = 0; i < timeDependentInputItems.Count; i++)
            {
                if (initialDamage < failureNumber && damages[i] >= failureNumber)
                {
                    ITimeDependentInput timeDependentInput = timeDependentInputItems[i];

                    double incrementTime = timeDependentInput.EndTime - timeDependentInput.BeginTime;
                    double incrementDamage = locationDependentOutput.TimeDependentOutputItems[i].IncrementDamage;
                    double durationInTimeStepFailure = (failureNumber - initialDamage) / incrementDamage * incrementTime;

                    return timeDependentInput.BeginTime + durationInTimeStepFailure;
                }
            }

            return null;
        }
    }
}
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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Class containing all location dependent output of a location.
    /// </summary>
    public abstract class LocationDependentOutput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="timeDependentOutputItems">The time dependent output items of the
        /// location.</param>
        protected LocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            TimeDependentOutputItems = timeDependentOutputItems;
        }

        /// <summary>
        /// Gets the time dependent output items.
        /// </summary>
        public IReadOnlyList<TimeDependentOutput> TimeDependentOutputItems { get; }

        /// <summary>
        /// Gets the cumulative damages.
        /// </summary>
        /// <param name="initialDamage">The initial damage.</param>
        /// <returns>The cumulative damages for the location dependent output.</returns>
        public IReadOnlyList<double> GetDamages(double initialDamage)
        {
            var damages = new List<double>();

            double currentDamage = initialDamage;

            foreach (TimeDependentOutput timeDependentOutput in TimeDependentOutputItems)
            {
                currentDamage += timeDependentOutput.IncrementDamage;

                damages.Add(currentDamage);
            }

            return damages;
        }

        /// <summary>
        /// Gets the time of failure.
        /// </summary>
        /// <param name="initialDamage">The initial damage.</param>
        /// <param name="failureNumber">The failure number.</param>
        /// <param name="timeDependentInputItems">The time dependent input items.</param>
        /// <returns>The time of failure for the location dependent output, or <c>null</c> when:
        /// <list type="bullet">
        /// <item>the revetment at the location did not fail;</item>
        /// <item>one or more of the calculated damages equal <c>NaN</c>.</item>
        /// </list>
        /// </returns>
        public double? GetTimeOfFailure(double initialDamage, double failureNumber,
                                        IReadOnlyList<ITimeDependentInput> timeDependentInputItems)
        {
            IReadOnlyList<double> damages = GetDamages(initialDamage);

            if (damages.Any(double.IsNaN))
            {
                return null;
            }

            double damageBeginTime = initialDamage;

            for (var i = 0; i < timeDependentInputItems.Count; i++)
            {
                double damageEndTime = damages[i];

                if (damageBeginTime < failureNumber && damageEndTime >= failureNumber)
                {
                    ITimeDependentInput timeDependentInput = timeDependentInputItems[i];

                    double incrementTime = timeDependentInput.EndTime - timeDependentInput.BeginTime;
                    double incrementDamage = TimeDependentOutputItems[i].IncrementDamage;
                    double durationInTimeStepFailure = (failureNumber - damageBeginTime) / incrementDamage * incrementTime;

                    return timeDependentInput.BeginTime + durationInTimeStepFailure;
                }

                damageBeginTime = damageEndTime;
            }

            return null;
        }
    }
}
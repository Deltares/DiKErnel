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
        private List<double> cumulativeDamages;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="initialDamage">The initial damage of the location.</param>
        /// <param name="failureNumber">The failure number of the location.</param>
        /// <param name="timeDependentOutputItems">The time dependent output items of the
        /// location.</param>
        /// <remarks><paramref name="initialDamage"/> and <paramref name="failureNumber"/>
        /// are input parameters that are used to derive the final output results.</remarks>
        protected LocationDependentOutput(double initialDamage, double failureNumber,
                                          IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            TimeDependentOutputItems = timeDependentOutputItems;

            SetCumulativeDamages(initialDamage);
        }

        /// <summary>
        /// Gets the time dependent output items.
        /// </summary>
        public IReadOnlyList<TimeDependentOutput> TimeDependentOutputItems { get; }

        /// <summary>
        /// Gets the cumulative damages.
        /// </summary>
        public IReadOnlyList<double> CumulativeDamages => cumulativeDamages;

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
            if (cumulativeDamages.Any(double.IsNaN))
            {
                return null;
            }

            double damageAtStartOfCalculation = initialDamage;

            for (var i = 0; i < timeDependentInputItems.Count; i++)
            {
                double damageAtEndOfCalculation = cumulativeDamages[i];

                if (damageAtStartOfCalculation < failureNumber && damageAtEndOfCalculation >= failureNumber)
                {
                    return CalculateTimeOfFailure(failureNumber, timeDependentInputItems[i], TimeDependentOutputItems[i],
                                                  damageAtStartOfCalculation);
                }

                damageAtStartOfCalculation = damageAtEndOfCalculation;
            }

            return null;
        }

        /// <summary>
        /// Calculates the time of failure.
        /// </summary>
        /// <param name="failureNumber">The failure number.</param>
        /// <param name="timeDependentInput">The time dependent input.</param>
        /// <param name="timeDependentOutput">The time dependent output.</param>
        /// <param name="damageAtStartOfCalculation">The damage at the start of the calculation.</param>
        /// <returns>The time of failure.</returns>
        protected virtual double CalculateTimeOfFailure(double failureNumber, ITimeDependentInput timeDependentInput,
                                                        TimeDependentOutput timeDependentOutput,
                                                        double damageAtStartOfCalculation)
        {
            double incrementTime = timeDependentInput.EndTime - timeDependentInput.BeginTime;
            double incrementDamage = timeDependentOutput.IncrementDamage;
            double durationInTimeStepFailure = (failureNumber - damageAtStartOfCalculation) / incrementDamage * incrementTime;

            return timeDependentInput.BeginTime + durationInTimeStepFailure;
        }

        private void SetCumulativeDamages(double initialDamage)
        {
            cumulativeDamages = new List<double>();

            double currentDamage = initialDamage;

            foreach (TimeDependentOutput timeDependentOutput in TimeDependentOutputItems)
            {
                currentDamage += timeDependentOutput.IncrementDamage;

                cumulativeDamages.Add(currentDamage);
            }
        }
    }
}
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
using DiKErnel.FunctionLibrary.NaturalStoneWaveImpact;

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    /// <summary>
    /// Location dependent output of a natural stone wave impact calculation.
    /// </summary>
    public class NaturalStoneWaveImpactLocationDependentOutput : LocationDependentOutput
    {
        /// <inheritdoc/>
        /// <param name="z">The calculated z.</param>
        /// <param name="resistance">The calculated resistance.</param>
        public NaturalStoneWaveImpactLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems, double z, double resistance)
            : base(timeDependentOutputItems)
        {
            Z = z;
            Resistance = resistance;
        }

        /// <summary>
        /// Gets the calculated z.
        /// </summary>
        public double Z { get; }

        /// <summary>
        /// Gets the calculated resistance.
        /// </summary>
        public double Resistance { get; }

        public override double? GetTimeOfFailure(double initialDamage, double failureNumber,
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

                    var timeDependentOutput = (NaturalStoneWaveImpactTimeDependentOutput) TimeDependentOutputItems[i];

                    double referenceFailure = NaturalStoneWaveImpactFunctions.ReferenceFailure(
                        Resistance, timeDependentOutput.HydraulicLoad ?? double.NaN, timeDependentOutput.WaveAngleImpact ?? double.NaN,
                        failureNumber);

                    double referenceTimeFailure = NaturalStoneWaveImpactFunctions.ReferenceTimeFailure(
                        referenceFailure, timeDependentInput.WavePeriodTm10);

                    double durationInTimeStepFailure = NaturalStoneWaveImpactFunctions.DurationInTimeStepFailure(
                        referenceTimeFailure, timeDependentOutput.ReferenceTimeDegradation ?? double.NaN);

                    return timeDependentInput.BeginTime + durationInTimeStepFailure;
                }

                damageBeginTime = damageEndTime;
            }

            return null;
        }
    }
}
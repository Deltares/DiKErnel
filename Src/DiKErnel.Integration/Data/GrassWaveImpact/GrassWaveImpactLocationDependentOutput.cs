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
using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassWaveImpact
{
    /// <summary>
    /// Location dependent output of a grass wave impact calculation.
    /// </summary>
    public class GrassWaveImpactLocationDependentOutput : LocationDependentOutput
    {
        /// <inheritdoc/>
        /// <param name="z">The calculated z.</param>
        /// <param name="minimumWaveHeight">The calculated minimum wave height.</param>
        /// <param name="maximumWaveHeight">The calculated maximum wave height.</param>
        public GrassWaveImpactLocationDependentOutput(double initialDamage, double failureNumber,
                                                      IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                      IReadOnlyList<TimeDependentOutput> timeDependentOutputItems, double z,
                                                      double minimumWaveHeight, double maximumWaveHeight)
            : base(initialDamage, failureNumber, timeDependentInputItems, timeDependentOutputItems)
        {
            Z = z;
            MinimumWaveHeight = minimumWaveHeight;
            MaximumWaveHeight = maximumWaveHeight;
        }

        /// <summary>
        /// Gets the calculated z.
        /// </summary>
        public double Z { get; }

        /// <summary>
        /// Gets the calculated minimum wave height.
        /// </summary>
        public double MinimumWaveHeight { get; }

        /// <summary>
        /// Gets the calculated maximum wave height.
        /// </summary>
        public double MaximumWaveHeight { get; }
    }
}
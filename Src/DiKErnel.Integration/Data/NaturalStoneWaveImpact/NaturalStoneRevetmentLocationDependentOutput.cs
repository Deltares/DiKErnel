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

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    /// <summary>
    /// Location dependent output of a natural stone revetment location.
    /// </summary>
    public class NaturalStoneRevetmentLocationDependentOutput : LocationDependentOutput
    {
        /// <inheritdoc/>
        /// <param name="z">The calculated z.</param>
        /// <param name="resistance">The calculated resistance.</param>
        public NaturalStoneRevetmentLocationDependentOutput(
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
    }
}
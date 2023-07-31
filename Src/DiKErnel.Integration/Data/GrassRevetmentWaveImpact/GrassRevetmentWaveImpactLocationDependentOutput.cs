﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveImpact
{
    /// <summary>
    /// Location dependent output of a grass revetment wave impact location.
    /// </summary>
    public class GrassRevetmentWaveImpactLocationDependentOutput : LocationDependentOutput
    {
        /// <inheritdoc/>
        /// <param name="z">The calculated z.</param>
        public GrassRevetmentWaveImpactLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems, double z)
            : base(timeDependentOutputItems)
        {
            Z = z;
        }

        /// <summary>
        /// Gets the calculated z.
        /// </summary>
        public double Z { get; }
    }
}
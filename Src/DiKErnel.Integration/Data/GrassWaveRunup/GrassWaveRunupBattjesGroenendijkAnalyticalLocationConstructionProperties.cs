// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.Integration.Data.Grass;

namespace DiKErnel.Integration.Data.GrassWaveRunup
{
    /// <summary>
    /// Construction properties to construct a grass wave run-up Battjes-Groenendijk
    /// analytical location dependent input.
    /// </summary>
    public class GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties
        : GrassWaveRunupLocationConstructionProperties
    {
        /// <inheritdoc/>
        public GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(double x,
                                                                                        GrassTopLayerType topLayerType)
            : base(x, topLayerType) {}

        /// <summary>
        /// Gets or sets the Cu coefficient.
        /// </summary>
        public double? FrontVelocityCu { get; set; }
    }
}
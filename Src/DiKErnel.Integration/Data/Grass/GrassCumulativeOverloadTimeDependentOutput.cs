// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;

namespace DiKErnel.Integration.Data.Grass
{
    /// <summary>
    /// Time dependent output of a grass cumulative overload calculation.
    /// </summary>
    public class GrassCumulativeOverloadTimeDependentOutput : TimeDependentOutput
    {
        /// <inheritdoc/>
        public GrassCumulativeOverloadTimeDependentOutput(
            GrassCumulativeOverloadTimeDependentOutputConstructionProperties constructionProperties)
            : base(constructionProperties)
        {
            VerticalDistanceWaterLevelElevation = constructionProperties.VerticalDistanceWaterLevelElevation
                                                  ?? throw new InvalidTimeDependentOutputException(
                                                      nameof(constructionProperties.VerticalDistanceWaterLevelElevation));
            RepresentativeWaveRunup2P = constructionProperties.RepresentativeWaveRunup2P;
            CumulativeOverload = constructionProperties.CumulativeOverload;
            AverageNumberOfWaves = constructionProperties.AverageNumberOfWaves;
        }

        /// <summary>
        /// Gets the vertical distance water level elevation.
        /// </summary>
        public double VerticalDistanceWaterLevelElevation { get; }

        /// <summary>
        /// Gets the representative wave run-up 2P.
        /// </summary>
        public double? RepresentativeWaveRunup2P { get; }

        /// <summary>
        /// Gets the cumulative overload.
        /// </summary>
        public double? CumulativeOverload { get; }

        /// <summary>
        /// Gets the average number of waves.
        /// </summary>
        public double? AverageNumberOfWaves { get; }
    }
}
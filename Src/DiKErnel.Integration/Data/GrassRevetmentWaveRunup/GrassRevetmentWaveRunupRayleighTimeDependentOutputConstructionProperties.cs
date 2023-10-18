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

using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Construction properties to construct grass revetment wave run-up time dependent
    /// output for the Rayleigh protocol.
    /// </summary>
    public class GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
        : TimeDependentOutputConstructionProperties
    {
        /// <summary>
        /// Gets or sets the vertical distance water level elevation.
        /// </summary>
        public double? VerticalDistanceWaterLevelElevation { get; set; }

        /// <summary>
        /// Gets or sets the wave angle.
        /// </summary>
        public double? WaveAngle { get; set; }
        
        /// <summary>
        /// Gets or sets the wave angle impact.
        /// </summary>
        public double? WaveAngleImpact { get; set; }

        /// <summary>
        /// Gets or sets the representative wave run-up 2P.
        /// </summary>
        public double? RepresentativeWaveRunup2P { get; set; }

        /// <summary>
        /// Gets or sets the cumulative overload.
        /// </summary>
        public double? CumulativeOverload { get; set; }

        /// <summary>
        /// Gets or sets the average number of waves.
        /// </summary>
        public double? AverageNumberOfWaves { get; set; }
    }
}
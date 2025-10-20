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

namespace DiKErnel.FunctionLibrary.GrassWaveOvertopping
{
    /// <summary>
    /// Input for grass wave overtopping Rayleigh discrete cumulative overload calculations.
    /// </summary>
    public class GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput
        : GrassWaveOvertoppingRayleighCumulativeOverloadInput
    {
        /// <inheritdoc/>
        /// <param name="fixedNumberOfWaves">The fixed number of waves [-].</param>
        public GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput(double averageNumberOfWaves,
                                                                           double representativeWaveRunup2P,
                                                                           double verticalDistanceWaterLevelElevation,
                                                                           double criticalFrontVelocity,
                                                                           double increasedLoadTransitionAlphaM,
                                                                           double reducedStrengthTransitionAlphaS,
                                                                           double gravitationalAcceleration,
                                                                           double frontVelocityCwo,
                                                                           double accelerationAlphaA,
                                                                           int fixedNumberOfWaves)
            : base(averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                   criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                   gravitationalAcceleration, frontVelocityCwo, accelerationAlphaA)
        {
            FixedNumberOfWaves = fixedNumberOfWaves;
        }

        /// <summary>
        /// Gets the fixed number of waves [-].
        /// </summary>
        public int FixedNumberOfWaves { get; }
    }
}
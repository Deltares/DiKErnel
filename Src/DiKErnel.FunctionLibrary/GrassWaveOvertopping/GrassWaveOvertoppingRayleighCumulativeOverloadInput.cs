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

using DiKErnel.FunctionLibrary.Grass;

namespace DiKErnel.FunctionLibrary.GrassWaveOvertopping
{
    /// <summary>
    /// Input for grass wave overtopping Rayleigh cumulative overload calculations.
    /// </summary>
    public class GrassWaveOvertoppingRayleighCumulativeOverloadInput : GrassCumulativeOverloadInput
    {
        /// <inheritdoc/>
        /// <param name="frontVelocityCwo">The Cwo coefficient [-].</param>
        /// <param name="accelerationAlphaA">The AlphaA coefficient [-].</param>
        public GrassWaveOvertoppingRayleighCumulativeOverloadInput(double averageNumberOfWaves,
                                                                   double representativeWaveRunup2P,
                                                                   double verticalDistanceWaterLevelElevation,
                                                                   double criticalFrontVelocity,
                                                                   double increasedLoadTransitionAlphaM,
                                                                   double reducedStrengthTransitionAlphaS,
                                                                   double gravitationalAcceleration,
                                                                   double frontVelocityCwo,
                                                                   double accelerationAlphaA)
            : base(averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                   criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                   gravitationalAcceleration)
        {
            FrontVelocityCwo = frontVelocityCwo;
            AccelerationAlphaA = accelerationAlphaA;
        }

        /// <summary>
        /// Gets the Cwo coefficient [-].
        /// </summary>
        public double FrontVelocityCwo { get; }

        /// <summary>
        /// Gets the AlphaA coefficient [-].
        /// </summary>
        public double AccelerationAlphaA { get; }
    }
}
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

namespace DiKErnel.FunctionLibrary.GrassWaveRunup
{
    /// <summary>
    /// Input for grass wave run-up Battjes-Groenendijk analytical cumulative overload
    /// calculations.
    /// </summary>
    public class GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput : GrassWaveRunupCumulativeOverloadInput
    {
        /// <inheritdoc/>
        /// <param name="frontVelocityCu">The Cu coefficient [-].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="bottomForeshoreZ">The z coordinate at the bottom of the foreshore [m].</param>
        /// <param name="slopeForeshore">The slope of the foreshore [-].</param>
        /// <param name="k1">The K1 value [-].</param>
        /// <param name="k2">The K2 value [-].</param>
        public GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(double averageNumberOfWaves,
                                                                                 double representativeWaveRunup2P,
                                                                                 double verticalDistanceWaterLevelElevation,
                                                                                 double criticalFrontVelocity,
                                                                                 double increasedLoadTransitionAlphaM,
                                                                                 double reducedStrengthTransitionAlphaS,
                                                                                 double gravitationalAcceleration,
                                                                                 double frontVelocityCu,
                                                                                 double waterLevel,
                                                                                 double waveHeightHm0,
                                                                                 double bottomForeshoreZ,
                                                                                 double slopeForeshore,
                                                                                 double k1, double k2)
            : base(averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                   criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                   gravitationalAcceleration, frontVelocityCu)
        {
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            BottomForeshoreZ = bottomForeshoreZ;
            SlopeForeshore = slopeForeshore;
            K1 = k1;
            K2 = k2;
        }

        /// <summary>
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the z coordinate at the bottom of the foreshore [m].
        /// </summary>
        public double BottomForeshoreZ { get; }

        /// <summary>
        /// Gets the slope of the foreshore [-].
        /// </summary>
        public double SlopeForeshore { get; }

        /// <summary>
        /// Gets the K1 value [-].
        /// </summary>
        public double K1 { get; }

        /// <summary>
        /// Gets the K2 value [-].
        /// </summary>
        public double K2 { get; }
    }
}
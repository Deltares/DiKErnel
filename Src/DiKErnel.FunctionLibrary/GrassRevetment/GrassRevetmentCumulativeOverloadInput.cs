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

namespace DiKErnel.FunctionLibrary.GrassRevetment
{
    /// <summary>
    /// Input for a grass revetment cumulative overload calculation.
    /// </summary>
    public class GrassRevetmentCumulativeOverloadInput
    {
        /// <summary>
        /// Creates a new instance of <see cref="GrassRevetmentCumulativeOverloadInput"/>.
        /// </summary>
        /// <param name="averageNumberOfWaves">The average number of waves [-].</param>
        /// <param name="representativeWaveRunup2P">The representative wave run-up
        /// (2 percent) [m].</param>
        /// <param name="fixedNumberOfWaves">The fixed number of waves [-].</param>
        /// <param name="verticalDistanceWaterLevelElevation">The vertical distance of the
        /// water elevation [m].</param>
        /// <param name="criticalFrontVelocity">The critical front velocity [m/s].</param>
        /// <param name="increasedLoadTransitionAlphaM">The AlphaM value [-].</param>
        /// <param name="reducedStrengthTransitionAlphaS">The AlphaS value [-].</param>
        /// <param name="gravitationalAcceleration">The gravitational
        /// acceleration [m/s^2].</param>
        public GrassRevetmentCumulativeOverloadInput(double averageNumberOfWaves, double representativeWaveRunup2P,
                                                     int fixedNumberOfWaves, double verticalDistanceWaterLevelElevation,
                                                     double criticalFrontVelocity, double increasedLoadTransitionAlphaM,
                                                     double reducedStrengthTransitionAlphaS, double gravitationalAcceleration)
        {
            AverageNumberOfWaves = averageNumberOfWaves;
            RepresentativeWaveRunup2P = representativeWaveRunup2P;
            FixedNumberOfWaves = fixedNumberOfWaves;
            VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            GravitationalAcceleration = gravitationalAcceleration;
        }

        /// <summary>
        /// Gets the average number of waves [-].
        /// </summary>
        public double AverageNumberOfWaves { get; }

        /// <summary>
        /// Gets the representative wave run-up (2 percent) [m].
        /// </summary>
        public double RepresentativeWaveRunup2P { get; }

        /// <summary>
        /// Gets the fixed number of waves [-].
        /// </summary>
        public int FixedNumberOfWaves { get; }

        /// <summary>
        /// Gets the vertical distance of the water elevation [m].
        /// </summary>
        public double VerticalDistanceWaterLevelElevation { get; }

        /// <summary>
        /// Gets the critical front velocity [m/s].
        /// </summary>
        public double CriticalFrontVelocity { get; }

        /// <summary>
        /// Gets the AlphaM value [-].
        /// </summary>
        public double IncreasedLoadTransitionAlphaM { get; }

        /// <summary>
        /// Gets the AlphaS value [-].
        /// </summary>
        public double ReducedStrengthTransitionAlphaS { get; }

        /// <summary>
        /// Gets the gravitational acceleration [m/s^2].
        /// </summary>
        public double GravitationalAcceleration { get; }
    }
}
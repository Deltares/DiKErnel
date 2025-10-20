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

namespace DiKErnel.FunctionLibrary.Grass
{
    /// <summary>
    /// Input for grass cumulative overload calculations.
    /// </summary>
    public abstract class GrassCumulativeOverloadInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="averageNumberOfWaves">The average number of waves [-].</param>
        /// <param name="representativeWaveRunup2P">The representative wave run-up
        /// (2 percent) [m].</param>
        /// <param name="verticalDistanceWaterLevelElevation">The vertical distance of the
        /// water elevation [m].</param>
        /// <param name="criticalFrontVelocity">The critical front velocity [m/s].</param>
        /// <param name="increasedLoadTransitionAlphaM">The AlphaM value [-].</param>
        /// <param name="reducedStrengthTransitionAlphaS">The AlphaS value [-].</param>
        /// <param name="gravitationalAcceleration">The gravitational
        /// acceleration [m/s^2].</param>
        protected GrassCumulativeOverloadInput(double averageNumberOfWaves, double representativeWaveRunup2P,
                                               double verticalDistanceWaterLevelElevation, double criticalFrontVelocity,
                                               double increasedLoadTransitionAlphaM,
                                               double reducedStrengthTransitionAlphaS, double gravitationalAcceleration)
        {
            AverageNumberOfWaves = averageNumberOfWaves;
            RepresentativeWaveRunup2P = representativeWaveRunup2P;
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
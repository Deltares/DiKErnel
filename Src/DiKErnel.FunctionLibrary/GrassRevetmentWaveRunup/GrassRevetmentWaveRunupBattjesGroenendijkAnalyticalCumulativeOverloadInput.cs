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

namespace DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Input for a grass revetment wave run-up Battjes-Groenendijk analytical cumulative
    /// overload calculation.
    /// </summary>
    public class GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="averageNumberOfWaves">The average number of waves [-].</param>
        /// <param name="representativeWaveRunup2P">The representative wave run-up
        /// (2 percent) [m].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="verticalDistanceWaterLevelElevation">The vertical distance of the
        /// water elevation [m].</param>
        /// <param name="bottomForeshoreZ">The z coordinate at the bottom of the foreshore [m].</param>
        /// <param name="slopeForeshore">The slope of the foreshore [-].</param>
        /// <param name="criticalFrontVelocity">The critical front velocity [m/s].</param>
        /// <param name="frontVelocityCu">The Cu coefficient [-].</param>
        /// <param name="increasedLoadTransitionAlphaM">The AlphaM value [-].</param>
        /// <param name="reducedStrengthTransitionAlphaS">The AlphaS value [-].</param>
        /// <param name="gravitationalAcceleration">The gravitational
        /// acceleration [m/s^2].</param>
        /// <param name="k1">The K1 value [-].</param>
        /// <param name="k2">The K2 value [-].</param>
        public GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(double averageNumberOfWaves,
                                                                                          double representativeWaveRunup2P,
                                                                                          double waterLevel, double waveHeightHm0,
                                                                                          double verticalDistanceWaterLevelElevation,
                                                                                          double bottomForeshoreZ,
                                                                                          double slopeForeshore,
                                                                                          double criticalFrontVelocity,
                                                                                          double frontVelocityCu,
                                                                                          double increasedLoadTransitionAlphaM,
                                                                                          double reducedStrengthTransitionAlphaS,
                                                                                          double gravitationalAcceleration, double k1,
                                                                                          double k2)
        {
            AverageNumberOfWaves = averageNumberOfWaves;
            RepresentativeWaveRunup2P = representativeWaveRunup2P;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation;
            BottomForeshoreZ = bottomForeshoreZ;
            SlopeForeshore = slopeForeshore;
            CriticalFrontVelocity = criticalFrontVelocity;
            FrontVelocityCu = frontVelocityCu;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            GravitationalAcceleration = gravitationalAcceleration;
            K1 = k1;
            K2 = k2;
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
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the vertical distance of the water elevation [m].
        /// </summary>
        public double VerticalDistanceWaterLevelElevation { get; }

        /// <summary>
        /// Gets the z coordinate at the bottom of the foreshore [m].
        /// </summary>
        public double BottomForeshoreZ { get; }

        /// <summary>
        /// Gets the slope of the foreshore [-].
        /// </summary>
        public double SlopeForeshore { get; }

        /// <summary>
        /// Gets the critical front velocity [m/s].
        /// </summary>
        public double CriticalFrontVelocity { get; }

        /// <summary>
        /// Gets the Cu coefficient [-].
        /// </summary>
        public double FrontVelocityCu { get; }

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
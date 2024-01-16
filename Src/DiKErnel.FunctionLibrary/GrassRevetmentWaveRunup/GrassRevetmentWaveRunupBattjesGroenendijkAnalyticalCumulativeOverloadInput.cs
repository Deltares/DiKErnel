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
        /// <param name="averageNumberOfWaves"></param>
        /// <param name="increasedLoadTransitionAlphaM"></param>
        /// <param name="reducedStrengthTransitionAlphaS"></param>
        /// <param name="frontVelocityCu"></param>
        /// <param name="criticalFrontVelocity"></param>
        /// <param name="gravitationalAcceleration"></param>
        /// <param name="slopeForeshore"></param>
        /// <param name="representativeWaveRunup2P"></param>
        /// <param name="waveHeightHm0"></param>
        /// <param name="waterLevel"></param>
        /// <param name="bottomForeshoreZ"></param>
        /// <param name="verticalDistanceWaterLevelElevation"></param>
        /// <param name="k1"></param>
        /// <param name="k2"></param>
        public GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
            double averageNumberOfWaves, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double frontVelocityCu, double criticalFrontVelocity, double gravitationalAcceleration, double slopeForeshore,
            double representativeWaveRunup2P, double waveHeightHm0, double waterLevel, double bottomForeshoreZ,
            double verticalDistanceWaterLevelElevation, double k1, double k2)
        {
            AverageNumberOfWaves = averageNumberOfWaves;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            FrontVelocityCu = frontVelocityCu;
            CriticalFrontVelocity = criticalFrontVelocity;
            GravitationalAcceleration = gravitationalAcceleration;
            SlopeForeshore = slopeForeshore;
            RepresentativeWaveRunup2P = representativeWaveRunup2P;
            WaveHeightHm0 = waveHeightHm0;
            WaterLevel = waterLevel;
            BottomForeshoreZ = bottomForeshoreZ;
            VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation;
            K1 = k1;
            K2 = k2;
        }

        public double AverageNumberOfWaves { get; }
        
        public double IncreasedLoadTransitionAlphaM { get; }
        public double ReducedStrengthTransitionAlphaS { get; }
        public double FrontVelocityCu { get; }
        public double CriticalFrontVelocity { get; }
        public double GravitationalAcceleration { get; }
        public double SlopeForeshore { get; }
        public double RepresentativeWaveRunup2P { get; }
        public double WaveHeightHm0 { get; }
        public double WaterLevel { get; }
        public double BottomForeshoreZ { get; }
        public double VerticalDistanceWaterLevelElevation { get; }
        public double K1 { get; }
        public double K2 { get; }
    }
}
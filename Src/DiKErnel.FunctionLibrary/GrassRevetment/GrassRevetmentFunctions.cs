﻿// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// //
// // This file is part of DiKErnel.
// //
// // DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// // GNU Lesser General Public License as published by the Free Software Foundation, either
// // version 3 of the License, or (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// // without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// // See the GNU Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License along with this
// // program. If not, see <http://www.gnu.org/licenses/>.
// //
// // All names, logos, and references to "Deltares" are registered trademarks of Stichting
// // Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;

namespace DiKErnel.FunctionLibrary.GrassRevetment
{
    /// <summary>
    /// Class that holds all generic grass revetment calculation routines.
    /// </summary>
    public static class GrassRevetmentFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="cumulativeOverload">The cumulative overload [m^2/s^2].</param>
        /// <param name="criticalCumulativeOverload">The critical cumulative overload [m^2/s^2].</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(double cumulativeOverload, double criticalCumulativeOverload)
        {
            return cumulativeOverload / criticalCumulativeOverload;
        }
        
        internal static double CumulativeOverload(GrassRevetmentCumulativeOverloadInput input, Func<double, double> getFrontVelocityFunc) 
        {
            double cumulativeFrontVelocity = 0.0;

            for (var k = 1; k <= input.FixedNumberOfWaves; ++k)
            {
                double waveRunup = WaveRunup(input.RepresentativeWaveRunup2P, input.FixedNumberOfWaves, k);
                double frontVelocity = getFrontVelocityFunc(waveRunup);

                cumulativeFrontVelocity += Math.Max(0.0, input.IncreasedLoadTransitionAlphaM * Math.Pow(frontVelocity, 2.0)
                                                         - input.ReducedStrengthTransitionAlphaS 
                                                         * Math.Pow(input.CriticalFrontVelocity, 2.0));
            }

            return input.AverageNumberOfWaves / input.FixedNumberOfWaves * cumulativeFrontVelocity;
        }
        
        private static double WaveRunup(double representativeWaveRunup2P, int fixedNumberOfWaves, int waveNumber)
        {
            return representativeWaveRunup2P * Math.Sqrt(Math.Log(1.0 - waveNumber / (fixedNumberOfWaves + 1.0))
                                                         / Math.Log(0.02));
        }
    }
}
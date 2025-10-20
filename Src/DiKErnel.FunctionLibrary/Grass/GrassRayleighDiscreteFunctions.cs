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

using System;

namespace DiKErnel.FunctionLibrary.Grass
{
    /// <summary>
    /// Class that holds grass Rayleigh discrete calculation routines.
    /// </summary>
    public static class GrassRayleighDiscreteFunctions
    {
        private static readonly double waveRunupPartial = Math.Log(0.02);

        internal static double CumulativeOverload(GrassCumulativeOverloadInput input,
                                                  int fixedNumberOfWaves,
                                                  Func<double, double> getFrontVelocityFunc)
        {
            double cumulativeFrontVelocity = 0;

            double cumulativeFrontVelocityPartial = input.CriticalFrontVelocity * input.CriticalFrontVelocity;

            for (var k = 1; k <= fixedNumberOfWaves; k++)
            {
                double waveRunup = WaveRunup(input.RepresentativeWaveRunup2P, fixedNumberOfWaves, k);
                double frontVelocity = getFrontVelocityFunc(waveRunup);

                cumulativeFrontVelocity += Math.Max(0, input.IncreasedLoadTransitionAlphaM * frontVelocity * frontVelocity
                                                       - input.ReducedStrengthTransitionAlphaS
                                                       * cumulativeFrontVelocityPartial);
            }

            return input.AverageNumberOfWaves / fixedNumberOfWaves * cumulativeFrontVelocity;
        }

        private static double WaveRunup(double representativeWaveRunup2P, int fixedNumberOfWaves, int waveNumber)
        {
            return representativeWaveRunup2P * Math.Sqrt(Math.Log(1 - waveNumber / (fixedNumberOfWaves + 1d))
                                                         / waveRunupPartial);
        }
    }
}
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

using System;

namespace DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Class that holds all grass revetment wave run-up specific calculation routines.
    /// </summary>
    public static class GrassRevetmentWaveRunupFunctions
    {
        /// <summary>
        /// Calculates the representative wave run-up (2 percent).
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The representative wave run-up (2 percent) [m].</returns>
        public static double RepresentativeWaveRunup2P(GrassRevetmentWaveRunupRepresentative2PInput input)
        {
            return input.WaveHeightHm0
                   * Math.Min(input.RepresentativeWaveRunup2PAru * input.RepresentativeWaveRunup2PGammab
                                                                 * input.RepresentativeWaveRunup2PGammaf
                                                                 * input.WaveAngleImpact * input.SurfSimilarityParameter,
                              input.RepresentativeWaveRunup2PGammaf
                              * input.WaveAngleImpact
                              * (input.RepresentativeWaveRunup2PBru - input.RepresentativeWaveRunup2PCru
                                 / Math.Sqrt(input.SurfSimilarityParameter)));
        }

        /// <summary>
        /// Calculates the wave impact with respect to the wave angle.
        /// </summary>
        /// <param name="waveAngle">The wave angle [deg].</param>
        /// <param name="waveAngleImpactAbeta">The Abeta coefficient [-].</param>
        /// <param name="waveAngleImpactBetamax">The Betamax coefficient [-].</param>
        /// <returns>The wave impact with respect to the wave angle [-].</returns>
        public static double WaveAngleImpact(double waveAngle, double waveAngleImpactAbeta, double waveAngleImpactBetamax)
        {
            return 1 - waveAngleImpactAbeta * Math.Min(Math.Abs(waveAngle), waveAngleImpactBetamax);
        }
    }
}
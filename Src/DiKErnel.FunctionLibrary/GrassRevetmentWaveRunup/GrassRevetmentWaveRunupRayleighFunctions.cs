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
using DiKErnel.FunctionLibrary.GrassRevetment;

namespace DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Class that holds all grass revetment wave run-up specific calculation routines for the
    /// Rayleigh protocol.
    /// </summary>
    public static class GrassRevetmentWaveRunupRayleighFunctions
    {
        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassRevetmentWaveRunupRayleighCumulativeOverloadInput input)
        {
            Func<double, double> getFrontVelocityFunc = waveRunup => FrontVelocity(waveRunup,
                                                                                   input.VerticalDistanceWaterLevelElevation,
                                                                                   input.FrontVelocityCu,
                                                                                   input.GravitationalAcceleration);

            return GrassRevetmentFunctions.CumulativeOverload(input, getFrontVelocityFunc);
        }

        private static double FrontVelocity(double waveRunup, double verticalDistanceWaterLevelElevation, double frontVelocityCu,
                                            double gravitationalAcceleration)
        {
            return frontVelocityCu * Math.Sqrt(gravitationalAcceleration * waveRunup)
                                   * Math.Max(0.0, Math.Min(1.0, (waveRunup - verticalDistanceWaterLevelElevation)
                                                                 / (0.25 * waveRunup)));
        }
    }
}
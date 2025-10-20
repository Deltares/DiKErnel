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
using DiKErnel.FunctionLibrary.Grass;

namespace DiKErnel.FunctionLibrary.GrassWaveOvertopping
{
    /// <summary>
    /// Class that holds grass wave overtopping Rayleigh discrete calculation routines.
    /// </summary>
    public static class GrassWaveOvertoppingRayleighDiscreteFunctions
    {
        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input)
        {
            return GrassRayleighDiscreteFunctions.CumulativeOverload(
                input, input.FixedNumberOfWaves,
                waveRunup => FrontVelocity(waveRunup, input.VerticalDistanceWaterLevelElevation,
                                           input.AccelerationAlphaA, input.FrontVelocityCwo,
                                           input.GravitationalAcceleration));
        }

        private static double FrontVelocity(double waveRunup, double verticalDistanceWaterLevelElevation,
                                            double accelerationAlphaA, double frontVelocityCwo, double gravitationalAcceleration)
        {
            return frontVelocityCwo * accelerationAlphaA
                                    * Math.Sqrt(gravitationalAcceleration
                                                * Math.Max(0, waveRunup - verticalDistanceWaterLevelElevation));
        }
    }
}
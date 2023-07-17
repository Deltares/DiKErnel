// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using DiKErnel.External.Overtopping;
using DiKErnel.FunctionLibrary.GrassRevetment;

namespace DiKErnel.FunctionLibrary.GrassRevetmentOvertopping
{
    /// <summary>
    /// Class that holds all grass revetment overtopping specific calculation routines.
    /// </summary>
    public static class GrassRevetmentOvertoppingFunctions
    {
        /// <summary>
        /// Calculates the representative wave run-up (2 percent).
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The representative wave run-up (2 percent) [m].</returns>
        public static double RepresentativeWaveRunup2P(GrassRevetmentOvertoppingRepresentative2PInput input)
        {
            return OvertoppingAdapter.CalculateZ2(input.WaterLevel, input.WaveHeightHm0, input.WavePeriodTm10, input.WaveDirection,
                                                  input.XValuesProfile, input.ZValuesProfile, input.RoughnessCoefficients,
                                                  input.DikeHeight);
        }

        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassRevetmentOvertoppingCumulativeOverloadInput input)
        {
            Func<double, double> getFrontVelocityFunc = waveRunup => FrontVelocity(waveRunup,
                                                                                   input.VerticalDistanceWaterLevelElevation,
                                                                                   input.AccelerationAlphaA,
                                                                                   input.FrontVelocityCwo,
                                                                                   input.GravitationalAcceleration);

            return GrassRevetmentFunctions.CumulativeOverload(input, getFrontVelocityFunc);
        }

        private static double FrontVelocity(double waveRunup, double verticalDistanceWaterLevelElevation,
                                            double accelerationAlphaA, double frontVelocityCwo, double gravitationalAcceleration)
        {
            return frontVelocityCwo * accelerationAlphaA
                                    * Math.Sqrt(gravitationalAcceleration
                                                * Math.Max(0.0, waveRunup - verticalDistanceWaterLevelElevation));
        }
    }
}
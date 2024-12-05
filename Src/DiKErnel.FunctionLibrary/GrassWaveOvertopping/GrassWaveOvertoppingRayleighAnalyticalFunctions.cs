// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using MathNet.Numerics;

namespace DiKErnel.FunctionLibrary.GrassWaveOvertopping
{
    /// <summary>
    /// Class that holds grass wave overtopping Rayleigh analytical calculation routines.
    /// </summary>
    public static class GrassWaveOvertoppingRayleighAnalyticalFunctions
    {
        private static readonly double parameterRayleighPartial = 2 * Math.Log(0.02);
        private static readonly double genericPartial = Math.Sqrt(2);
        private static readonly double integralPart1Partial = Math.Sqrt(Math.PI / 2);

        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <param name="cumulativeOverloadPartial1">A part of the cumulative overload calculation that is not time dependent.</param>
        /// <param name="cumulativeOverloadPartial2">A part of the cumulative overload calculation that is not time dependent.</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassWaveOvertoppingRayleighCumulativeOverloadInput input,
                                                double cumulativeOverloadPartial1, double cumulativeOverloadPartial2)
        {
            double parameterRayleigh = ParameterRayleigh(input.RepresentativeWaveRunup2P);

            double parameterX0 = ParameterX0(input.VerticalDistanceWaterLevelElevation, parameterRayleigh,
                                             cumulativeOverloadPartial1, cumulativeOverloadPartial2);

            double sharedResult = Math.Exp(-parameterX0 * parameterX0);

            double integralPart1 = IntegralPart1(parameterRayleigh, cumulativeOverloadPartial1, sharedResult, parameterX0);

            double integralPart2 = IntegralPart2(input.VerticalDistanceWaterLevelElevation, cumulativeOverloadPartial1,
                                                 sharedResult);

            double integralPart3 = IntegralPart3(cumulativeOverloadPartial2, sharedResult);

            return input.AverageNumberOfWaves * Math.Max(integralPart1 + integralPart2 + integralPart3, 0);
        }

        private static double ParameterRayleigh(double representativeWaveRunup2P)
        {
            return Math.Sqrt(-representativeWaveRunup2P * representativeWaveRunup2P / parameterRayleighPartial);
        }

        private static double ParameterX0(double verticalDistanceWaterLevelElevation, double parameterRayleigh,
                                          double cumulativeOverloadPartial1, double cumulativeOverloadPartial2)
        {
            return LowerLimitWaveRunup(verticalDistanceWaterLevelElevation, cumulativeOverloadPartial1, cumulativeOverloadPartial2) /
                   (genericPartial * parameterRayleigh);
        }

        private static double LowerLimitWaveRunup(double verticalDistanceWaterLevelElevation, double cumulativeOverloadPartial1,
                                                  double cumulativeOverloadPartial2)
        {
            return verticalDistanceWaterLevelElevation + cumulativeOverloadPartial2 / cumulativeOverloadPartial1;
        }

        private static double IntegralPart1(double parameterRayleigh, double cumulativeOverloadPartial1, double sharedResult,
                                            double parameterX0)
        {
            return cumulativeOverloadPartial1 * parameterRayleigh *
                   (integralPart1Partial + genericPartial * parameterX0 * sharedResult -
                    integralPart1Partial * SpecialFunctions.Erf(parameterX0));
        }

        private static double IntegralPart2(double verticalDistanceWaterLevelElevation, double cumulativeOverloadPartial1,
                                            double sharedResult)
        {
            return -cumulativeOverloadPartial1 * verticalDistanceWaterLevelElevation * sharedResult;
        }

        private static double IntegralPart3(double cumulativeOverloadPartial2, double sharedResult)
        {
            return -cumulativeOverloadPartial2 * sharedResult;
        }
    }
}
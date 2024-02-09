﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input)
        {
            double sharedResult1 = input.IncreasedLoadTransitionAlphaM * Math.Pow(input.AccelerationAlphaA, 2) *
                                   Math.Pow(input.FrontVelocityCwo, 2) * input.GravitationalAcceleration;

            double sharedResult2 = input.ReducedStrengthTransitionAlphaS * Math.Pow(input.CriticalFrontVelocity, 2);

            double parameterX0 = ParameterX0(input, sharedResult1, sharedResult2);

            double sharedResult3 = Math.Exp(-Math.Pow(parameterX0, 2));

            double integralPart1 = IntegralPart1(input, sharedResult1, sharedResult3, parameterX0);
            double integralPart2 = IntegralPart2(input, sharedResult1, sharedResult3);
            double integralPart3 = IntegralPart3(input, sharedResult2, sharedResult3);

            return input.AverageNumberOfWaves * Math.Max(integralPart1 + integralPart2 + integralPart3, 0);
        }

        private static double ParameterX0(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input,
                                          double sharedResult1, double sharedResult2)
        {
            double parameterRayleigh = ParameterRayleigh(input.RepresentativeWaveRunup2P);

            return LowerLimitWaveRunup(input, sharedResult1, sharedResult2) / (Math.Sqrt(2) * parameterRayleigh);
        }

        private static double IntegralPart1(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input,
                                            double sharedResult1, double sharedResult3, double parameterX0)
        {
            double parameterRayleigh = ParameterRayleigh(input.RepresentativeWaveRunup2P);

            return sharedResult1 * parameterRayleigh *
                   (Math.Sqrt(Math.PI / 2) + Math.Sqrt(2) * parameterX0 * sharedResult3 -
                    Math.Sqrt(Math.PI / 2) * SpecialFunctions.Erf(parameterX0));
        }

        private static double ParameterRayleigh(double representativeWaveRunup2P)
        {
            return Math.Sqrt(-Math.Pow(representativeWaveRunup2P, 2) / (2 * Math.Log(0.02)));
        }

        private static double IntegralPart2(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input,
                                            double sharedResult1, double sharedResult3)
        {
            return -sharedResult1 * input.VerticalDistanceWaterLevelElevation * sharedResult3;
        }

        private static double IntegralPart3(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input,
                                            double sharedResult2, double sharedResult3)
        {
            return -sharedResult2 * sharedResult3;
        }

        private static double LowerLimitWaveRunup(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input,
                                                  double sharedResult1, double sharedResult2)
        {
            return input.VerticalDistanceWaterLevelElevation + sharedResult2 / sharedResult1;
        }
    }
}
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
            double integralPart1 = IntegralPart1(input);
            double integralPart2 = IntegralPart2();
            double integralPart3 = IntegralPart3();

            return input.AverageNumberOfWaves * Math.Max(integralPart1 + integralPart2 + integralPart3, 0);
        }

        private static double IntegralPart1(GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput input)
        {
            double parameterRayleigh = ParameterRayleigh(input.RepresentativeWaveRunup2P);

            return input.IncreasedLoadTransitionAlphaM * Math.Pow(input.AccelerationAlphaA, 2) *
                   Math.Pow(input.FrontVelocityCwo, 2) * input.GravitationalAcceleration * parameterRayleigh;
        }

        private static double ParameterRayleigh(double representativeWaveRunup2P)
        {
            return Math.Sqrt(-Math.Pow(representativeWaveRunup2P, 2) / (2 * Math.Log(0.02)));
        }

        private static double IntegralPart2()
        {
            return double.NaN;
        }

        private static double IntegralPart3()
        {
            return double.NaN;
        }
    }
}
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

using System.Linq;
using DiKErnel.External.Overtopping;

namespace DiKErnel.FunctionLibrary.Grass
{
    /// <summary>
    /// Class that holds grass cumulative overload calculation routines.
    /// </summary>
    public static class GrassCumulativeOverloadFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="cumulativeOverload">The cumulative overload [m^2/s^2].</param>
        /// <param name="criticalCumulativeOverload">The critical cumulative
        /// overload [m^2/s^2].</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(double cumulativeOverload, double criticalCumulativeOverload)
        {
            return cumulativeOverload / criticalCumulativeOverload;
        }

        /// <summary>
        /// Calculates the representative wave run-up (2 percent).
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The representative wave run-up (2 percent) [m].</returns>
        public static double RepresentativeWaveRunup2P(GrassRepresentative2PInput input)
        {
            return OvertoppingAdapter.CalculateZ2(input.WaterLevel, input.WaveHeightHm0, input.WavePeriodTm10, input.WaveDirection,
                                                  input.XValuesProfile.ToArray(), input.ZValuesProfile.ToArray(),
                                                  input.RoughnessCoefficients.ToArray(), input.DikeHeight, input.DikeOrientation);
        }
    }
}
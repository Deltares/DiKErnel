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

namespace DiKErnel.DomainLibrary.Defaults.GrassRevetment
{
    /// <summary>
    /// Class that contains default values for grass revetment cumulative overload
    /// calculations.
    /// </summary>
    public static class GrassRevetmentCumulativeOverloadDefaults
    {
        /// <summary>
        /// Gets the default value of the increased load transition alpha M [-].
        /// </summary>
        public static double IncreasedLoadTransitionAlphaM => 1;

        /// <summary>
        /// Gets the default value of the reduced strength transition alpha S [-].
        /// </summary>
        public static double ReducedStrengthTransitionAlphaS => 1;

        /// <summary>
        /// Gets the default value of the Ctm coefficient [-].
        /// </summary>
        public static double AverageNumberOfWavesCtm => 0.92;

        /// <summary>
        /// Gets the default value of the fixed number of waves [-].
        /// </summary>
        public static int FixedNumberOfWaves => 10000;
    }
}
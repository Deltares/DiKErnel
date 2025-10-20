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

namespace DiKErnel.FunctionLibrary
{
    /// <summary>
    /// Class that holds generic calculation routines.
    /// </summary>
    public static class GenericFunctions
    {
        /// <summary>
        /// Converts a degrees value into radians.
        /// </summary>
        /// <param name="degrees">The value to convert [deg].</param>
        /// <returns>The converted value [rad].</returns>
        public static double Radians(double degrees)
        {
            return degrees * (Math.PI / 180);
        }

        /// <summary>
        /// Converts a radians value into degrees.
        /// </summary>
        /// <param name="radians">The value to convert [rad].</param>
        /// <returns>The converted value [deg].</returns>
        public static double Degrees(double radians)
        {
            return radians / (Math.PI / 180);
        }
    }
}
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
using System.Globalization;

namespace DiKErnel.Util.Helpers
{
    /// <summary>
    /// Helper class to help with numerics.
    /// </summary>
    public static class NumericsHelper
    {
        private const double tolerance = 1e-16;

        /// <summary>
        /// Asserts whether first and second are equal.
        /// </summary>
        /// <param name="first">The first argument.</param>
        /// <param name="second">The second argument.</param>
        /// <returns>true when equal; false otherwise.</returns>
        public static bool AreEqual(double first, double second)
        {
            return Math.Abs(first - second) <= tolerance;
        }

        /// <summary>
        /// Converts the given value to a string.
        /// </summary>
        /// <param name="value">The value to convert.</param>
        /// <returns>The converted string.</returns>
        /// <remarks>Numbers are rounded to 6 decimal places. When fewer decimals are present,
        /// trailing zeros are not presented.</remarks>
        public static string ToString(double value)
        {
            return Math.Round(value, 6).ToString(CultureInfo.InvariantCulture).Replace("E", "e");
        }
    }
}
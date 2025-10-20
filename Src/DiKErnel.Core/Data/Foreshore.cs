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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Class containing a foreshore that is needed to perform a calculation.
    /// </summary>
    public class Foreshore
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="slope">The slope.</param>
        /// <param name="bottomZ">The z coordinate at the bottom.</param>
        public Foreshore(double slope, double bottomZ)
        {
            Slope = slope;
            BottomZ = bottomZ;
        }

        /// <summary>
        /// Gets the slope of the foreshore.
        /// </summary>
        public double Slope { get; }

        /// <summary>
        /// Gets the z coordinate at the bottom of the foreshore.
        /// </summary>
        public double BottomZ { get; }
    }
}
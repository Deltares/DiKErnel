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

namespace DiKErnel.External.Overtopping.Data
{
    /// <summary>
    /// The geometry for the overtopping kernel.
    /// </summary>
    internal struct Geometry
    {
        /// <summary>
        /// The normal of the dike [deg].
        /// </summary>
        public double Normal;

        /// <summary>
        /// The number of coordinates.
        /// </summary>
        public int NPoints;

        /// <summary>
        /// The x coordinates of the dike [m].
        /// </summary>
        public IntPtr XCoords;

        /// <summary>
        /// The y coordinates of the dike [m].
        /// </summary>
        public IntPtr YCoords;

        /// <summary>
        /// The roughness of the dike [-].
        /// </summary>
        public IntPtr Roughness;
    }
}
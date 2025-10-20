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

namespace DiKErnel.DomainLibrary.Defaults.GrassWaveImpact
{
    /// <summary>
    /// Interface that contains default value definitions for grass wave impact top layers.
    /// </summary>
    public interface IGrassWaveImpactTopLayerDefaults
    {
        /// <summary>
        /// Gets the default value of the Agwi coefficient [m].
        /// </summary>
        public double TimeLineAgwi { get; }

        /// <summary>
        /// Gets the default value of the Bgwi coefficient [s^-1].
        /// </summary>
        public double TimeLineBgwi { get; }

        /// <summary>
        /// Gets the default value of the Cgwi coefficient [m].
        /// </summary>
        public double TimeLineCgwi { get; }
    }
}
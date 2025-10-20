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

namespace DiKErnel.DomainLibrary.Defaults.NaturalStoneWaveImpact
{
    /// <summary>
    /// Interface that contains default value definitions for natural stone wave impact top
    /// layers.
    /// </summary>
    public interface INaturalStoneWaveImpactTopLayerDefaults
    {
        /// <summary>
        /// Gets the default value of the Xib coefficient [-].
        /// </summary>
        public double HydraulicLoadXib { get; }

        /// <summary>
        /// Gets the default value of the Ap coefficient [-].
        /// </summary>
        public double HydraulicLoadAp { get; }

        /// <summary>
        /// Gets the default value of the Bp coefficient [-].
        /// </summary>
        public double HydraulicLoadBp { get; }

        /// <summary>
        /// Gets the default value of the Cp coefficient [-].
        /// </summary>
        public double HydraulicLoadCp { get; }

        /// <summary>
        /// Gets the default value of the Np coefficient [-].
        /// </summary>
        public double HydraulicLoadNp { get; }

        /// <summary>
        /// Gets the default value of the As coefficient [-].
        /// </summary>
        public double HydraulicLoadAs { get; }

        /// <summary>
        /// Gets the default value of the Bs coefficient [-].
        /// </summary>
        public double HydraulicLoadBs { get; }

        /// <summary>
        /// Gets the default value of the Cs coefficient [-].
        /// </summary>
        public double HydraulicLoadCs { get; }

        /// <summary>
        /// Gets the default value of the Ns coefficient [-].
        /// </summary>
        public double HydraulicLoadNs { get; }
    }
}
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
    /// Class that contains default values for natural stone wave impact calculations with a
    /// nordic stone top layer.
    /// </summary>
    public class NaturalStoneWaveImpactNordicStoneTopLayerDefaults : INaturalStoneWaveImpactTopLayerDefaults
    {
        private static NaturalStoneWaveImpactNordicStoneTopLayerDefaults instance;

        private NaturalStoneWaveImpactNordicStoneTopLayerDefaults() {}

        /// <summary>
        /// Gets the (one and only) instance of this class.
        /// </summary> 
        public static NaturalStoneWaveImpactNordicStoneTopLayerDefaults Instance =>
            instance ??= new NaturalStoneWaveImpactNordicStoneTopLayerDefaults();

        public double HydraulicLoadXib => 2.9;

        public double HydraulicLoadAp => 4;

        public double HydraulicLoadBp => 0;

        public double HydraulicLoadCp => 0;

        public double HydraulicLoadNp => -0.9;

        public double HydraulicLoadAs => 0.8;

        public double HydraulicLoadBs => 0;

        public double HydraulicLoadCs => 0;

        public double HydraulicLoadNs => 0.6;
    }
}
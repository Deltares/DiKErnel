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

namespace DiKErnel.DomainLibrary.Defaults.NaturalStoneRevetment
{
    /// <summary>
    /// Class that contains default values for natural stone revetments with a nordic stone
    /// top layer.
    /// </summary>
    public class NaturalStoneRevetmentNordicStoneTopLayerDefaults : INaturalStoneRevetmentTopLayerDefaults
    {
        private static NaturalStoneRevetmentNordicStoneTopLayerDefaults instance;

        private NaturalStoneRevetmentNordicStoneTopLayerDefaults() {}

        /// <summary>
        /// Gets the (one and only) instance of this class.
        /// </summary> 
        public static NaturalStoneRevetmentNordicStoneTopLayerDefaults Instance =>
            instance ??= new NaturalStoneRevetmentNordicStoneTopLayerDefaults();

        public double HydraulicLoadXib => 2.9;

        public double HydraulicLoadAp => 4.0;

        public double HydraulicLoadBp => 0.0;

        public double HydraulicLoadCp => 0.0;

        public double HydraulicLoadNp => -0.9;

        public double HydraulicLoadAs => 0.8;

        public double HydraulicLoadBs => 0.0;

        public double HydraulicLoadCs => 0.0;

        public double HydraulicLoadNs => 0.6;
    }
}
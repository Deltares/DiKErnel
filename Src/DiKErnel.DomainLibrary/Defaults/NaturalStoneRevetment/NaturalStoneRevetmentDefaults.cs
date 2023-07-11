﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
    /// Class that contains default values for natural stone revetments.
    /// </summary>
    public class NaturalStoneRevetmentDefaults
    {
        /// <summary>
        /// Gets the default value of the Aus coefficient [-].
        /// </summary>
        public static double GetSlopeUpperLevelAus => 0.05;

        /// <summary>
        /// Gets the default value of the Als coefficient [-].
        /// </summary>
        public static double GetSlopeLowerLevelAls => 1.5;

        /// <summary>
        /// Gets the default value of the Aul coefficient [-].
        /// </summary>
        public static double GetUpperLimitLoadingAul => 0.1;

        /// <summary>
        /// Gets the default value of the Bul coefficient [-].
        /// </summary>
        public static double GetUpperLimitLoadingBul => 0.6;

        /// <summary>
        /// Gets the default value of the Cul coefficient [-].
        /// </summary>
        public static double GetUpperLimitLoadingCul => 4.0;

        /// <summary>
        /// Gets the default value of the All coefficient [-].
        /// </summary>
        public static double GetLowerLimitLoadingAll => 0.1;

        /// <summary>
        /// Gets the default value of the Bll coefficient [-].
        /// </summary>
        public static double GetLowerLimitLoadingBll => 0.2;

        /// <summary>
        /// Gets the default value of the Cll coefficient [-].
        /// </summary>
        public static double GetLowerLimitLoadingCll => 4.0;

        /// <summary>
        /// Gets the default value of the Asmax coefficient [-].
        /// </summary>
        public static double GetDistanceMaximumWaveElevationAsmax => 0.42;

        /// <summary>
        /// Gets the default value of the Bsmax coefficient [-].
        /// </summary>
        public static double GetDistanceMaximumWaveElevationBsmax => 0.9;

        /// <summary>
        /// Gets the default value of the Awi coefficient [-].
        /// </summary>
        public static double GetNormativeWidthOfWaveImpactAwi => 0.96;

        /// <summary>
        /// Gets the default value of the Bwi coefficient [-].
        /// </summary>
        public static double GetNormativeWidthOfWaveImpactBwi => 0.11;

        /// <summary>
        /// Gets the default value of the Betamax coefficient [deg].
        public static double GetWaveAngleImpactBetamax => 78.0;
    }
}
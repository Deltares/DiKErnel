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

namespace DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveImpact
{
    /// <summary>
    /// Class that contains default values for grass revetment wave impact.
    /// </summary>
    public static class GrassRevetmentWaveImpactDefaults
    {
        /// <summary>
        /// Gets the default value of the Temax coefficient [s].
        /// </summary>
        public static double MinimumWaveHeightTemax => 3600000.0;

        /// <summary>
        /// Gets the default value of the Temin coefficient [s].
        /// </summary>
        public static double MaximumWaveHeightTemin => 3.6;

        /// <summary>
        /// Gets the default value of the Nwa coefficient [-].
        /// </summary>
        public static double WaveAngleImpactNwa => 2.0 / 3.0;

        /// <summary>
        /// Gets the default value of the Qwa coefficient [-].
        /// </summary>
        public static double WaveAngleImpactQwa => 0.35;

        /// <summary>
        /// Gets the default value of the Rwa coefficient [-].
        /// </summary>
        public static double WaveAngleImpactRwa => 10.0;

        /// <summary>
        /// Gets the default value of the Aul coefficient [-].
        /// </summary>
        public static double UpperLimitLoadingAul => 0.0;

        /// <summary>
        /// Gets the default value of the All coefficient [-].
        /// </summary>
        public static double LowerLimitLoadingAll => 0.5;
    }
}
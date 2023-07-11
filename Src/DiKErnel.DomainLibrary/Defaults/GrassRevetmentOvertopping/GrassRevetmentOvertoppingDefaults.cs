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

namespace DiKErnel.DomainLibrary.Defaults.GrassRevetmentOvertopping
{
    /// <summary>
    /// Class that contains default values for grass revetment overtopping.
    /// </summary>
    public static class GrassRevetmentOvertoppingDefaults
    {
        /// <summary>
        /// Gets the default value of the Cwo coefficient [-].
        /// </summary>
        public static double GetFrontVelocityCwo => 1.45;

        /// <summary>
        /// Gets the default value of the alpha A coefficient for the crest [-].
        /// </summary>
        public static double GetAccelerationAlphaAForCrest => 1.0;

        /// <summary>
        /// Gets the default value of the alpha A coefficient for the inner slope [-].
        /// </summary>
        public static double GetAccelerationAlphaAForInnerSlope => 1.4;
    }
}
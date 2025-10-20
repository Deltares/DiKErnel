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

using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassWaveImpact
{
    /// <summary>
    /// Construction properties to construct grass wave impact time dependent output.
    /// </summary>
    public class GrassWaveImpactTimeDependentOutputConstructionProperties
        : TimeDependentOutputConstructionProperties
    {
        /// <summary>
        /// Gets or sets the loading revetment.
        /// </summary>
        public bool? LoadingRevetment { get; set; }

        /// <summary>
        /// Gets or sets the upper limit loading.
        /// </summary>
        public double? UpperLimitLoading { get; set; }

        /// <summary>
        /// Gets or sets the lower limit loading.
        /// </summary>
        public double? LowerLimitLoading { get; set; }

        /// <summary>
        /// Gets or sets the wave angle.
        /// </summary>
        public double? WaveAngle { get; set; }

        /// <summary>
        /// Gets or sets the wave angle impact.
        /// </summary>
        public double? WaveAngleImpact { get; set; }

        /// <summary>
        /// Gets or sets the wave height impact.
        /// </summary>
        public double? WaveHeightImpact { get; set; }
    }
}
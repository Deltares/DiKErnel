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

using DiKErnel.Integration.Data.Grass;

namespace DiKErnel.Integration.Data.GrassWaveImpact
{
    /// <summary>
    /// Construction properties to construct grass wave impact location dependent input.
    /// </summary>
    public class GrassWaveImpactLocationConstructionProperties : LocationConstructionProperties
    {
        /// <inheritdoc/>
        /// <param name="topLayerType">The type of the top layer.</param>
        public GrassWaveImpactLocationConstructionProperties(double x, GrassTopLayerType topLayerType)
            : base(x)
        {
            TopLayerType = topLayerType;
        }

        /// <summary>
        /// Gets the type of the top layer.
        /// </summary>
        public GrassTopLayerType TopLayerType { get; }

        /// <summary>
        /// Gets or sets the Agwi coefficient.
        /// </summary>
        public double? TimeLineAgwi { get; set; }

        /// <summary>
        /// Gets or sets the Bgwi coefficient.
        /// </summary>
        public double? TimeLineBgwi { get; set; }

        /// <summary>
        /// Gets or sets the Cgwi coefficient.
        /// </summary>
        public double? TimeLineCgwi { get; set; }

        /// <summary>
        /// Gets or sets the Temax coefficient.
        /// </summary>
        public double? MinimumWaveHeightTemax { get; set; }

        /// <summary>
        /// Gets or sets the Temin coefficient.
        /// </summary>
        public double? MaximumWaveHeightTemin { get; set; }

        /// <summary>
        /// Gets or sets the Nwa coefficient.
        /// </summary>
        public double? WaveAngleImpactNwa { get; set; }

        /// <summary>
        /// Gets or sets the Qwa coefficient.
        /// </summary>
        public double? WaveAngleImpactQwa { get; set; }

        /// <summary>
        /// Gets or sets the Rwa coefficient.
        /// </summary>
        public double? WaveAngleImpactRwa { get; set; }

        /// <summary>
        /// Gets or sets the Aul coefficient.
        /// </summary>
        public double? UpperLimitLoadingAul { get; set; }

        /// <summary>
        /// Gets or sets the All coefficient.
        /// </summary>
        public double? LowerLimitLoadingAll { get; set; }
    }
}
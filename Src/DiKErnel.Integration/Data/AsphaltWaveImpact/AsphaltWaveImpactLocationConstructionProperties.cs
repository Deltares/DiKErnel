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

using System.Collections.Generic;

namespace DiKErnel.Integration.Data.AsphaltWaveImpact
{
    /// <summary>
    /// Construction properties to construct asphalt wave impact location dependent input.
    /// </summary>
    public class AsphaltWaveImpactLocationConstructionProperties : LocationConstructionProperties
    {
        /// <inheritdoc/>
        /// <param name="topLayerType">The type of the top layer.</param>
        /// <param name="flexuralStrength">The flexural strength.</param>
        /// <param name="soilElasticity">The elasticity of the soil.</param>
        /// <param name="thicknessUpperLayer">The thickness of the upper layer.</param>
        /// <param name="elasticModulusUpperLayer">The elastic modulus of the upper
        /// layer.</param>
        public AsphaltWaveImpactLocationConstructionProperties(double x, AsphaltWaveImpactTopLayerType topLayerType,
                                                               double flexuralStrength, double soilElasticity,
                                                               double thicknessUpperLayer,
                                                               double elasticModulusUpperLayer)
            : base(x)
        {
            TopLayerType = topLayerType;
            FlexuralStrength = flexuralStrength;
            SoilElasticity = soilElasticity;
            ThicknessUpperLayer = thicknessUpperLayer;
            ElasticModulusUpperLayer = elasticModulusUpperLayer;
        }

        /// <summary>
        /// Gets the type of the top layer.
        /// </summary>
        public AsphaltWaveImpactTopLayerType TopLayerType { get; }

        /// <summary>
        /// Gets the flexural strength.
        /// </summary>
        public double FlexuralStrength { get; }

        /// <summary>
        /// Gets the soil elasticity.
        /// </summary>
        public double SoilElasticity { get; }

        /// <summary>
        /// Gets the thickness of the upper layer.
        /// </summary>
        public double ThicknessUpperLayer { get; }

        /// <summary>
        /// Gets the elastic modulus of the upper layer.
        /// </summary>
        public double ElasticModulusUpperLayer { get; }

        /// <summary>
        /// Gets or sets the density of water.
        /// </summary>
        public double? DensityOfWater { get; set; }

        /// <summary>
        /// Gets or sets the thickness of the sub layer.
        /// </summary>
        public double? ThicknessSubLayer { get; set; }

        /// <summary>
        /// Gets or sets the elastic modulus of the sub layer.
        /// </summary>
        public double? ElasticModulusSubLayer { get; set; }

        /// <summary>
        /// Gets or sets the Ctm coefficient.
        /// </summary>
        public double? AverageNumberOfWavesCtm { get; set; }

        /// <summary>
        /// Gets or sets the fatigue alpha coefficient.
        /// </summary>
        public double? FatigueAlpha { get; set; }

        /// <summary>
        /// Gets or sets the fatigue beta coefficient.
        /// </summary>
        public double? FatigueBeta { get; set; }

        /// <summary>
        /// Gets or sets the impact number C coefficient.
        /// </summary>
        public double? ImpactNumberC { get; set; }

        /// <summary>
        /// Gets or sets the Nu coefficient.
        /// </summary>
        public double? StiffnessRelationNu { get; set; }

        /// <summary>
        /// Gets or sets the width factors.
        /// </summary>
        public IReadOnlyList<(double, double)> WidthFactors { get; set; }

        /// <summary>
        /// Gets or sets the depth factors.
        /// </summary>
        public IReadOnlyList<(double, double)> DepthFactors { get; set; }

        /// <summary>
        /// Gets or sets the impact factors.
        /// </summary>
        public IReadOnlyList<(double, double)> ImpactFactors { get; set; }
    }
}
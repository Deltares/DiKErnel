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

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    /// <summary>
    /// Construction properties to construct natural stone wave impact location dependent
    /// input.
    /// </summary>
    public class NaturalStoneWaveImpactLocationConstructionProperties : LocationConstructionProperties
    {
        /// <inheritdoc/>
        /// <param name="topLayerType">The type of the top layer.</param>
        /// <param name="thicknessTopLayer">The thickness of the top layer.</param>
        /// <param name="relativeDensity">The relative density.</param>
        public NaturalStoneWaveImpactLocationConstructionProperties(double x,
                                                                    NaturalStoneWaveImpactTopLayerType topLayerType,
                                                                    double thicknessTopLayer, double relativeDensity)
            : base(x)
        {
            TopLayerType = topLayerType;
            ThicknessTopLayer = thicknessTopLayer;
            RelativeDensity = relativeDensity;
        }

        /// <summary>
        /// Gets the type of the top layer.
        /// </summary>
        public NaturalStoneWaveImpactTopLayerType TopLayerType { get; }

        /// <summary>
        /// Gets the thickness of the top layer.
        /// </summary>
        public double ThicknessTopLayer { get; }

        /// <summary>
        /// Gets the relative density.
        /// </summary>
        public double RelativeDensity { get; }

        /// <summary>
        /// Gets or sets the Ap coefficient.
        /// </summary>
        public double? HydraulicLoadAp { get; set; }

        /// <summary>
        /// Gets or sets the Bp coefficient.
        /// </summary>
        public double? HydraulicLoadBp { get; set; }

        /// <summary>
        /// Gets or sets the Cp coefficient.
        /// </summary>
        public double? HydraulicLoadCp { get; set; }

        /// <summary>
        /// Gets or sets the Np coefficient.
        /// </summary>
        public double? HydraulicLoadNp { get; set; }

        /// <summary>
        /// Gets or sets the As coefficient.
        /// </summary>
        public double? HydraulicLoadAs { get; set; }

        /// <summary>
        /// Gets or sets the Bs coefficient.
        /// </summary>
        public double? HydraulicLoadBs { get; set; }

        /// <summary>
        /// Gets or sets the Cs coefficient.
        /// </summary>
        public double? HydraulicLoadCs { get; set; }

        /// <summary>
        /// Gets or sets the Ns coefficient.
        /// </summary>
        public double? HydraulicLoadNs { get; set; }

        /// <summary>
        /// Gets or sets the Xib coefficient.
        /// </summary>
        public double? HydraulicLoadXib { get; set; }

        /// <summary>
        /// Gets or sets the Aus coefficient.
        /// </summary>
        public double? SlopeUpperLevelAus { get; set; }

        /// <summary>
        /// Gets or sets the Als coefficient.
        /// </summary>
        public double? SlopeLowerLevelAls { get; set; }

        /// <summary>
        /// Gets or sets the Aul coefficient.
        /// </summary>
        public double? UpperLimitLoadingAul { get; set; }

        /// <summary>
        /// Gets or sets the Bul coefficient.
        /// </summary>
        public double? UpperLimitLoadingBul { get; set; }

        /// <summary>
        /// Gets or sets the Cul coefficient.
        /// </summary>
        public double? UpperLimitLoadingCul { get; set; }

        /// <summary>
        /// Gets or sets the All coefficient.
        /// </summary>
        public double? LowerLimitLoadingAll { get; set; }

        /// <summary>
        /// Gets or sets the Bll coefficient.
        /// </summary>
        public double? LowerLimitLoadingBll { get; set; }

        /// <summary>
        /// Gets or sets the Cll coefficient.
        /// </summary>
        public double? LowerLimitLoadingCll { get; set; }

        /// <summary>
        /// Gets or sets the Asmax coefficient.
        /// </summary>
        public double? DistanceMaximumWaveElevationAsmax { get; set; }

        /// <summary>
        /// Gets or sets the Bsmax coefficient.
        /// </summary>
        public double? DistanceMaximumWaveElevationBsmax { get; set; }

        /// <summary>
        /// Gets or sets the Awi coefficient.
        /// </summary>
        public double? NormativeWidthOfWaveImpactAwi { get; set; }

        /// <summary>
        /// Gets or sets the Bwi coefficient.
        /// </summary>
        public double? NormativeWidthOfWaveImpactBwi { get; set; }

        /// <summary>
        /// Gets or sets the Betamax coefficient.
        /// </summary>
        public double? WaveAngleImpactBetamax { get; set; }
    }
}
// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.DomainLibrary.Defaults;
using DiKErnel.DomainLibrary.Defaults.NaturalStoneWaveImpact;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class NaturalStoneWaveImpactLocationDependentInputFactory
    {
        public static NaturalStoneWaveImpactLocationDependentInput CreateLocationDependentInput(
            NaturalStoneWaveImpactLocationConstructionProperties constructionProperties)
        {
            INaturalStoneRevetmentTopLayerDefaults topLayerDefaults =
                NaturalStoneWaveImpactDefaultsFactory.CreateTopLayerDefaults();

            var hydraulicLoads = new NaturalStoneWaveImpactHydraulicLoads(
                constructionProperties.HydraulicLoadAp ?? topLayerDefaults.HydraulicLoadAp,
                constructionProperties.HydraulicLoadBp ?? topLayerDefaults.HydraulicLoadBp,
                constructionProperties.HydraulicLoadCp ?? topLayerDefaults.HydraulicLoadCp,
                constructionProperties.HydraulicLoadNp ?? topLayerDefaults.HydraulicLoadNp,
                constructionProperties.HydraulicLoadAs ?? topLayerDefaults.HydraulicLoadAs,
                constructionProperties.HydraulicLoadBs ?? topLayerDefaults.HydraulicLoadBs,
                constructionProperties.HydraulicLoadCs ?? topLayerDefaults.HydraulicLoadCs,
                constructionProperties.HydraulicLoadNs ?? topLayerDefaults.HydraulicLoadNs,
                constructionProperties.HydraulicLoadXib ?? topLayerDefaults.HydraulicLoadXib);

            var slope = new NaturalStoneWaveImpactSlope(
                constructionProperties.SlopeUpperLevelAus ?? NaturalStoneRevetmentDefaults.SlopeUpperLevelAus,
                constructionProperties.SlopeLowerLevelAls ?? NaturalStoneRevetmentDefaults.SlopeLowerLevelAls);

            var upperLimitLoading = new NaturalStoneWaveImpactUpperLimitLoading(
                constructionProperties.UpperLimitLoadingAul ?? NaturalStoneRevetmentDefaults.UpperLimitLoadingAul,
                constructionProperties.UpperLimitLoadingBul ?? NaturalStoneRevetmentDefaults.UpperLimitLoadingBul,
                constructionProperties.UpperLimitLoadingCul ?? NaturalStoneRevetmentDefaults.UpperLimitLoadingCul);

            var lowerLimitLoading = new NaturalStoneWaveImpactLowerLimitLoading(
                constructionProperties.LowerLimitLoadingAll ?? NaturalStoneRevetmentDefaults.LowerLimitLoadingAll,
                constructionProperties.LowerLimitLoadingBll ?? NaturalStoneRevetmentDefaults.LowerLimitLoadingBll,
                constructionProperties.LowerLimitLoadingCll ?? NaturalStoneRevetmentDefaults.LowerLimitLoadingCll);

            var distanceMaximumWaveElevation = new NaturalStoneWaveImpactDistanceMaximumWaveElevation(
                constructionProperties.DistanceMaximumWaveElevationAsmax
                ?? NaturalStoneRevetmentDefaults.DistanceMaximumWaveElevationAsmax,
                constructionProperties.DistanceMaximumWaveElevationBsmax
                ?? NaturalStoneRevetmentDefaults.DistanceMaximumWaveElevationBsmax);

            var normativeWidthOfWaveImpact = new NaturalStoneWaveImpactNormativeWidthOfWaveImpact(
                constructionProperties.NormativeWidthOfWaveImpactAwi
                ?? NaturalStoneRevetmentDefaults.NormativeWidthOfWaveImpactAwi,
                constructionProperties.NormativeWidthOfWaveImpactBwi
                ?? NaturalStoneRevetmentDefaults.NormativeWidthOfWaveImpactBwi);

            var waveAngleImpact = new NaturalStoneWaveImpactWaveAngleImpact(
                constructionProperties.WaveAngleImpactBetamax ?? NaturalStoneRevetmentDefaults.WaveAngleImpactBetamax);

            return new NaturalStoneWaveImpactLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                constructionProperties.RelativeDensity,
                constructionProperties.ThicknessTopLayer,
                hydraulicLoads,
                slope,
                upperLimitLoading,
                lowerLimitLoading,
                distanceMaximumWaveElevation,
                normativeWidthOfWaveImpact,
                waveAngleImpact);
        }
    }
}
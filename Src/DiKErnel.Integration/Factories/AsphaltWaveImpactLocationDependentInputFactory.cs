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
using DiKErnel.DomainLibrary.Defaults.AsphaltWaveImpact;
using DiKErnel.Integration.Data.AsphaltWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class AsphaltWaveImpactLocationDependentInputFactory
    {
        public static AsphaltWaveImpactLocationDependentInput CreateLocationDependentInput(
            AsphaltWaveImpactLocationConstructionProperties constructionProperties)
        {
            IAsphaltWaveImpactTopLayerDefaults topLayerDefaults =
                AsphaltWaveImpactDefaultsFactory.CreateTopLayerDefaults();

            double elasticModulusUpperLayer = constructionProperties.ElasticModulusUpperLayer;
            var upperLayer = new AsphaltWaveImpactLayer((float) constructionProperties.ThicknessUpperLayer,
                                                        (float) elasticModulusUpperLayer);

            AsphaltWaveImpactLayer subLayer = null;
            double? thicknessSubLayer = constructionProperties.ThicknessSubLayer;
            double? elasticModulusSubLayer = constructionProperties.ElasticModulusSubLayer;

            if (thicknessSubLayer != null && elasticModulusSubLayer != null)
            {
                subLayer = new AsphaltWaveImpactLayer((float) thicknessSubLayer.Value, (float) elasticModulusSubLayer.Value);
            }

            var fatigue = new AsphaltWaveImpactFatigue(
                (float) (constructionProperties.FatigueAlpha ?? AsphaltWaveImpactDefaults.FatigueAlpha),
                (float) (constructionProperties.FatigueBeta ?? AsphaltWaveImpactDefaults.FatigueBeta));

            return new AsphaltWaveImpactLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                constructionProperties.FlexuralStrength,
                constructionProperties.DensityOfWater ?? AsphaltWaveImpactDefaults.DensityOfWater,
                constructionProperties.SoilElasticity,
                upperLayer,
                subLayer,
                constructionProperties.AverageNumberOfWavesCtm ?? AsphaltWaveImpactDefaults.AverageNumberOfWavesCtm,
                fatigue,
                constructionProperties.ImpactNumberC ?? AsphaltWaveImpactDefaults.ImpactNumberC,
                constructionProperties.StiffnessRelationNu ?? topLayerDefaults.StiffnessRelationNu,
                constructionProperties.WidthFactors ?? AsphaltWaveImpactDefaults.WidthFactors,
                constructionProperties.DepthFactors ?? AsphaltWaveImpactDefaults.DepthFactors,
                constructionProperties.ImpactFactors ?? AsphaltWaveImpactDefaults.ImpactFactors);
        }
    }
}
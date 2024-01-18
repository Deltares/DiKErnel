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
using DiKErnel.DomainLibrary.Defaults.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.AsphaltWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class AsphaltRevetmentWaveImpactLocationDependentInputFactory
    {
        public static AsphaltRevetmentWaveImpactLocationDependentInput CreateLocationDependentInput(
            AsphaltWaveImpactLocationConstructionProperties constructionProperties)
        {
            IAsphaltRevetmentWaveImpactTopLayerDefaults topLayerDefaults =
                AsphaltRevetmentWaveImpactDefaultsFactory.CreateTopLayerDefaults();

            double elasticModulusUpperLayer = constructionProperties.ElasticModulusUpperLayer;
            var upperLayer = new AsphaltRevetmentWaveImpactLayer(constructionProperties.ThicknessUpperLayer,
                                                                 elasticModulusUpperLayer);

            AsphaltRevetmentWaveImpactLayer subLayer = null;
            double? thicknessSubLayer = constructionProperties.ThicknessSubLayer;
            double? elasticModulusSubLayer = constructionProperties.ElasticModulusSubLayer;

            if (thicknessSubLayer != null && elasticModulusSubLayer != null)
            {
                subLayer = new AsphaltRevetmentWaveImpactLayer(thicknessSubLayer.Value, elasticModulusSubLayer.Value);
            }

            var fatigue = new AsphaltRevetmentWaveImpactFatigue(
                constructionProperties.FatigueAlpha ?? AsphaltRevetmentWaveImpactDefaults.FatigueAlpha,
                constructionProperties.FatigueBeta ?? AsphaltRevetmentWaveImpactDefaults.FatigueBeta);

            return new AsphaltRevetmentWaveImpactLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                constructionProperties.FlexuralStrength,
                constructionProperties.DensityOfWater ?? AsphaltRevetmentWaveImpactDefaults.DensityOfWater,
                constructionProperties.SoilElasticity,
                upperLayer,
                subLayer,
                constructionProperties.AverageNumberOfWavesCtm ?? AsphaltRevetmentWaveImpactDefaults.AverageNumberOfWavesCtm,
                fatigue,
                constructionProperties.ImpactNumberC ?? AsphaltRevetmentWaveImpactDefaults.ImpactNumberC,
                constructionProperties.StiffnessRelationNu ?? topLayerDefaults.StiffnessRelationNu,
                constructionProperties.WidthFactors ?? AsphaltRevetmentWaveImpactDefaults.WidthFactors,
                constructionProperties.DepthFactors ?? AsphaltRevetmentWaveImpactDefaults.DepthFactors,
                constructionProperties.ImpactFactors ?? AsphaltRevetmentWaveImpactDefaults.ImpactFactors);
        }
    }
}
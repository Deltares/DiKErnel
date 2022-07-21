// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include "AsphaltRevetmentWaveImpactLocationDependentInputFactory.h"

#include "AsphaltRevetmentWaveImpactDefaults.h"
#include "AsphaltRevetmentWaveImpactDefaultsFactory.h"
#include "DefaultsFactoryException.h"
#include "IAsphaltRevetmentWaveImpactTopLayerDefaults.h"
#include "LocationDependentInputFactoryException.h"
#include "LocationDependentInputFactoryHelper.h"
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<AsphaltRevetmentWaveImpactLocationDependentInput> AsphaltRevetmentWaveImpactLocationDependentInputFactory::
    CreateLocationDependentInput(
        const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IAsphaltRevetmentWaveImpactTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = AsphaltRevetmentWaveImpactDefaultsFactory::CreateTopLayerDefaults(
                constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            throw_with_nested(LocationDependentInputFactoryException("Could not create instance."));
        }

        const auto elasticModulusUpperLayer = constructionProperties.GetElasticModulusUpperLayer();
        auto upperLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(
            constructionProperties.GetThicknessUpperLayer(),
            elasticModulusUpperLayer);

        const auto thicknessSubLayer = constructionProperties.GetThicknessSubLayer();
        const auto elasticModulusSubLayer = constructionProperties.GetElasticModulusSubLayer();
        unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer = nullptr;
        if (thicknessSubLayer != nullptr && elasticModulusSubLayer != nullptr)
        {
            subLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(*thicknessSubLayer, *elasticModulusSubLayer);
        }

        auto fatigue = make_unique<AsphaltRevetmentWaveImpactFatigue>(
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFatigueAlpha(), topLayerDefaults->GetFatigueAlpha()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFatigueBeta(), topLayerDefaults->GetFatigueBeta()));

        return make_unique<AsphaltRevetmentWaveImpactLocationDependentInput>(
            constructionProperties.GetX(),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetFailureTension(),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetDensityOfWater(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetDensityOfWater()),
            constructionProperties.GetSoilElasticity(),
            move(upperLayer),
            move(subLayer),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetAverageNumberOfWavesCtm()),
            move(fatigue),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetImpactNumberC(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetImpactNumberC()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetStiffnessRelationNu(),
                                                          topLayerDefaults->GetStiffnessRelationNu()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWidthFactors(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetWidthFactors()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetDepthFactors(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetDepthFactors()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetImpactFactors(),
                                                          AsphaltRevetmentWaveImpactDefaults::GetImpactFactors()));
    }
}

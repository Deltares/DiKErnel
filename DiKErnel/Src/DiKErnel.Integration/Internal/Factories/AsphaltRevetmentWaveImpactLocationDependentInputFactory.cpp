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
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentCalculationInputBuilderException.h"
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
            ThrowWithMessage();
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
            GetValue(constructionProperties.GetFatigueAlpha(), topLayerDefaults->GetFatigueAlpha()),
            GetValue(constructionProperties.GetFatigueBeta(), topLayerDefaults->GetFatigueBeta()));

        return make_unique<AsphaltRevetmentWaveImpactLocationDependentInput>(
            constructionProperties.GetX(),
            GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetFailureTension(),
            GetValue(constructionProperties.GetDensityOfWater(), AsphaltRevetmentWaveImpactDefaults::GetDensityOfWater()),
            constructionProperties.GetSoilElasticity(),
            move(upperLayer),
            move(subLayer),
            GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), AsphaltRevetmentWaveImpactDefaults::GetAverageNumberOfWavesCtm()),
            move(fatigue),
            GetValue(constructionProperties.GetImpactNumberC(), AsphaltRevetmentWaveImpactDefaults::GetImpactNumberC()),
            GetValue(constructionProperties.GetStiffnessRelationNu(), topLayerDefaults->GetStiffnessRelationNu()),
            GetValue(constructionProperties.GetWidthFactors(), AsphaltRevetmentWaveImpactDefaults::GetWidthFactors()),
            GetValue(constructionProperties.GetDepthFactors(), AsphaltRevetmentWaveImpactDefaults::GetDepthFactors()),
            GetValue(constructionProperties.GetImpactFactors(), AsphaltRevetmentWaveImpactDefaults::GetImpactFactors()));
    }

    template <typename TValue>
    TValue AsphaltRevetmentWaveImpactLocationDependentInputFactory::GetValue(
        const TValue* ptrValue,
        const TValue defaultValue)
    {
        return ptrValue != nullptr
                   ? *ptrValue
                   : defaultValue;
    }

    void AsphaltRevetmentWaveImpactLocationDependentInputFactory::ThrowWithMessage()
    {
        throw_with_nested(RevetmentCalculationInputBuilderException("Could not create instance."));
    }
}

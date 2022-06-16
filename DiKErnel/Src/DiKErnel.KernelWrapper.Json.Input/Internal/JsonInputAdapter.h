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

#pragma once

#include <memory>

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"
#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"
#include "ICalculationInput.h"
#include "JsonInputAsphaltWaveImpactCalculationDefinitionData.h"
#include "JsonInputAsphaltWaveImpactLocationData.h"
#include "JsonInputData.h"
#include "JsonInputGrassWaveImpactCalculationDefinitionData.h"
#include "JsonInputGrassWaveImpactLocationData.h"
#include "JsonInputGrassWaveRunupCalculationDefinitionData.h"
#include "JsonInputGrassWaveRunupRayleighLocationData.h"
#include "JsonInputNaturalStoneCalculationDefinitionData.h"
#include "JsonInputNaturalStoneLocationData.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAdapter
    {
        public:
            static std::unique_ptr<Core::ICalculationInput> AdaptJsonInputData(
                const JsonInputData& jsonInputData);

        private:
            static std::unique_ptr<Core::CharacteristicPointType> ConvertCharacteristicPointType(
                const JsonInputCharacteristicPointType* jsonCharacteristicPointType);

            template<typename T>
            static const T* GetCalculationDefinition(
                const std::map<JsonInputCalculationType, std::reference_wrapper<JsonInputCalculationDefinitionData>>& calculationDefinitions,
                JsonInputCalculationType calculationType);

            static std::unique_ptr<Integration::AsphaltRevetmentWaveImpactLocationConstructionProperties>
            CreateAsphaltWaveImpactConstructionProperties(
                const JsonInputAsphaltWaveImpactLocationData& location,
                const JsonInputAsphaltWaveImpactCalculationDefinitionData* calculationDefinition);

            static Integration::AsphaltRevetmentTopLayerType ConvertTopLayerType(
                JsonInputAsphaltRevetmentTopLayerType topLayerType);

            static std::unique_ptr<Integration::GrassRevetmentWaveImpactLocationConstructionProperties> CreateGrassWaveImpactConstructionProperties(
                const JsonInputGrassWaveImpactLocationData& location,
                const JsonInputGrassWaveImpactCalculationDefinitionData* calculationDefinition);

            static std::unique_ptr<Integration::GrassRevetmentWaveRunupRayleighLocationConstructionProperties>
            CreateGrassWaveRunupRayleighConstructionProperties(
                const JsonInputGrassWaveRunupRayleighLocationData& location,
                const JsonInputGrassWaveRunupCalculationDefinitionData* calculationDefinition);

            static Integration::GrassRevetmentTopLayerType ConvertTopLayerType(
                JsonInputGrassRevetmentTopLayerType topLayerType);

            static std::unique_ptr<Integration::NaturalStoneRevetmentLocationConstructionProperties> CreateNaturalStoneConstructionProperties(
                const JsonInputNaturalStoneLocationData& location,
                const JsonInputNaturalStoneCalculationDefinitionData* calculationDefinition);

            static Integration::NaturalStoneRevetmentTopLayerType ConvertTopLayerType(
                JsonInputNaturalStoneRevetmentTopLayerType topLayerType);

            template <typename TValue>
            static std::unique_ptr<TValue> CreatePointerOfValue(
                const TValue* value);
    };
}

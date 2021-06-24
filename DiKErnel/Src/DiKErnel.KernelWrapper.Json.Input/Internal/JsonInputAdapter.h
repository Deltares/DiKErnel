// Copyright (C) Stichting Deltares 2020. All rights reserved.
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
#include "JsonInputAsphaltRevetmentWaveImpactLocationData.h"
#include "JsonInputData.h"
#include "JsonInputGrassRevetmentWaveImpactLocationData.h"
#include "JsonInputGrassRevetmentWaveRunupRayleighLocationData.h"
#include "JsonInputNaturalStoneRevetmentLocationData.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAdapter
    {
        public:
            static std::unique_ptr<Core::ICalculationInput> AdaptJsonInputData(
                const JsonInputData& jsonInputData);

        private:
            static std::unique_ptr<Core::CalculationLevelType> ConvertProcessType(
                const JsonInputProcessType* processType);

            static std::unique_ptr<Integration::AsphaltRevetmentWaveImpactLocationConstructionProperties>
            CreateAsphaltWaveImpactConstructionProperties(
                const JsonInputLocationData& location,
                const JsonInputAsphaltRevetmentWaveImpactLocationData& asphaltRevetmentWaveImpactLocationData);

            static Integration::AsphaltRevetmentTopLayerType ConvertTopLayerType(
                JsonInputAsphaltRevetmentTopLayerType topLayerType);

            static std::unique_ptr<Integration::GrassRevetmentWaveImpactLocationConstructionProperties> CreateGrassWaveImpactConstructionProperties(
                const JsonInputLocationData& location,
                const JsonInputGrassRevetmentWaveImpactLocationData& grassRevetmentWaveImpactLocationData);

            static std::unique_ptr<Integration::GrassRevetmentWaveRunupRayleighLocationConstructionProperties>
            CreateGrassWaveRunupRayleighConstructionProperties(
                const JsonInputLocationData& location,
                const JsonInputGrassRevetmentWaveRunupRayleighLocationData& grassRevetmentWaveRunupRayleighLocationData);

            static Integration::GrassRevetmentTopLayerType ConvertTopLayerType(
                JsonInputGrassRevetmentTopLayerType topLayerType);

            static std::unique_ptr<Integration::NaturalStoneRevetmentLocationConstructionProperties> CreateNaturalStoneConstructionProperties(
                const JsonInputLocationData& location,
                const JsonInputNaturalStoneRevetmentLocationData& naturalStoneRevetmentLocationData);

            static Integration::NaturalStoneRevetmentTopLayerType ConvertTopLayerType(
                JsonInputNaturalStoneRevetmentTopLayerType topLayerType);

            template <typename TValue>
            static std::unique_ptr<TValue> CreatePointerOfValue(
                const TValue* value);
    };
}

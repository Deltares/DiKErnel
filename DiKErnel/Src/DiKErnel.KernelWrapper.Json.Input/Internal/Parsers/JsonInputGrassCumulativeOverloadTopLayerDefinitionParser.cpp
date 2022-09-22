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

#include "JsonInputGrassCumulativeOverloadTopLayerDefinitionParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>
    JsonInputGrassCumulativeOverloadTopLayerDefinitionParser::Parse(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            for (const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS); const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>();

                topLayer->SetCriticalCumulativeOverload(
                    JsonInputParserHelper::ParseOptionalDouble(readTopLayer, JsonInputGrassRevetmentDefinitions::CRITICAL_CUMULATIVE_OVERLOAD));
                topLayer->SetCriticalFrontVelocity(
                    JsonInputParserHelper::ParseOptionalDouble(readTopLayer, JsonInputGrassRevetmentDefinitions::CRITICAL_FRONT_VELOCITY));

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }
}

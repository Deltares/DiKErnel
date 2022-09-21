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

#include "JsonInputGrassOvertoppingCalculationDefinitionParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassOvertoppingCalculationDefinitionData.h"
#include "JsonInputGrassOvertoppingCalculationProtocolType.h"
#include "JsonInputGrassOvertoppingDikesOvertoppingCalculationProtocolData.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputGrassOvertoppingCalculationDefinitionParser::JsonInputGrassOvertoppingCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputGrassOvertoppingCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputGrassOvertoppingCalculationDefinitionData>(
            move(failureNumber), ReadCalculationProtocolData(readCalculationMethod), ReadTopLayerDefinitionData(readCalculationMethod));

        if (readCalculationMethod.contains(JsonInputGrassOvertoppingDefinitions::ACCELERATION_ALPHA_A))
        {
            const auto& readAccelerationAlphaA = readCalculationMethod.at(JsonInputGrassOvertoppingDefinitions::ACCELERATION_ALPHA_A);

            calculationDefinition->SetAccelerationAlphaACrest(
                JsonInputParserHelper::ParseOptionalDouble(
                    readAccelerationAlphaA, JsonInputGrassOvertoppingDefinitions::ACCELERATION_ALPHA_A_CREST));

            calculationDefinition->SetAccelerationAlphaAInnerSlope(
                JsonInputParserHelper::ParseOptionalDouble(
                    readAccelerationAlphaA, JsonInputGrassOvertoppingDefinitions::ACCELERATION_ALPHA_A_INNER_SLOPE));
        }

        calculationDefinition->SetFixedNumberOfWaves(
            JsonInputParserHelper::ParseOptionalInteger(readCalculationMethod, JsonInputGrassRevetmentDefinitions::FIXED_NUMBER_OF_WAVES));

        calculationDefinition->SetFrontVelocity(
            JsonInputParserHelper::ParseOptionalDouble(readCalculationMethod, JsonInputGrassOvertoppingDefinitions::DIKE_HEIGHT));

        calculationDefinition->SetFactorCtm(
            JsonInputParserHelper::ParseOptionalDouble(readCalculationMethod, JsonInputDefinitions::FACTOR_CTM));

        return calculationDefinition;
    }

    unique_ptr<JsonInputGrassOvertoppingCalculationProtocolData> JsonInputGrassOvertoppingCalculationDefinitionParser::ReadCalculationProtocolData(
        const json& readCalculationMethod)
    {
        const auto& readCalculationProtocol = readCalculationMethod.at(JsonInputGrassRevetmentDefinitions::CALCULATION_PROTOCOL);

        if (const auto& calculationProtocolType = readCalculationProtocol.at(JsonInputGrassRevetmentDefinitions::CALCULATION_PROTOCOL_TYPE)
                                                                         .get<JsonInputGrassOvertoppingCalculationProtocolType>();
            calculationProtocolType == JsonInputGrassOvertoppingCalculationProtocolType::DikesOvertopping)
        {
            auto calculationProtocolData = make_unique<JsonInputGrassOvertoppingDikesOvertoppingCalculationProtocolData>();

            calculationProtocolData->SetDikeHeight(
                JsonInputParserHelper::ParseOptionalDouble(readCalculationProtocol, JsonInputGrassOvertoppingDefinitions::DIKE_HEIGHT));

            return calculationProtocolData;
        }

        return nullptr;
    }

    map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>
    JsonInputGrassOvertoppingCalculationDefinitionParser::ReadTopLayerDefinitionData(
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

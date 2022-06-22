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

#include "JsonInputGrassWaveRunupCalculationDefinitionParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassRevetmentDefinitions.h"
#include "JsonInputGrassRevetmentWaveRunupCalculationProtocolType.h"
#include "JsonInputGrassWaveRunupCalculationDefinitionData.h"
#include "JsonInputGrassWaveRunupDefinitions.h"
#include "JsonInputGrassWaveRunupRayleighCalculationProtocolData.h"
#include "JsonInputGrassWaveRunupRayleighDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputGrassRevetmentTopLayerType,
        {
            {
                JsonInputGrassRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputGrassRevetmentTopLayerType::ClosedSod, JsonInputGrassRevetmentDefinitions::TOP_LAYER_TYPE_CLOSED_SOD
            },
            {
                JsonInputGrassRevetmentTopLayerType::OpenSod, JsonInputGrassRevetmentDefinitions::TOP_LAYER_TYPE_OPEN_SOD
            }
        });

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputGrassRevetmentWaveRunupCalculationProtocolType,
        {
            {
                JsonInputGrassRevetmentWaveRunupCalculationProtocolType::Unknown, nullptr
            },
            {
                JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete,
                JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE_RAYLEIGH_DISCRETE
            }
        });

    JsonInputGrassWaveRunupCalculationDefinitionParser::JsonInputGrassWaveRunupCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputGrassWaveRunupCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputGrassWaveRunupCalculationDefinitionData>(
            move(failureNumber), forward<unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData>>(
                ReadCalculationProtocolData(readCalculationMethod)), ReadTopLayerDefinitionData(readCalculationMethod));

        calculationDefinition->SetAverageNumberOfWavesCtm(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputDefinitions::FACTOR_CTM)));

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P))
        {
            const auto& readRepresentativeWaveRunup2P = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P);

            calculationDefinition->SetRepresentativeWaveRunup2PAru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputDefinitions::A_COEFFICIENT)));

            calculationDefinition->SetRepresentativeWaveRunup2PBru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputDefinitions::B_COEFFICIENT)));

            calculationDefinition->SetRepresentativeWaveRunup2PCru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputDefinitions::C_COEFFICIENT)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactAbeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::A_BETA)));

            calculationDefinition->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::BETA_MAX)));
        }

        return calculationDefinition;
    }

    unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> JsonInputGrassWaveRunupCalculationDefinitionParser::ReadCalculationProtocolData(
        const json& readCalculationMethod)
    {
        const auto& readCalculationProtocol = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL);

        if (const auto& calculationProtocolType = readCalculationProtocol.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE)
                                                                         .get<JsonInputGrassRevetmentWaveRunupCalculationProtocolType>();
            calculationProtocolType == JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete)
        {
            auto calculationProtocolData = make_unique<JsonInputGrassWaveRunupRayleighCalculationProtocolData>();

            calculationProtocolData->SetFixedNumberOfWaves(
                forward<unique_ptr<int>>(JsonInputParserHelper::ParseOptionalInteger(
                    readCalculationProtocol, JsonInputGrassWaveRunupRayleighDefinitions::FIXED_NUMBER_OF_WAVES)));

            calculationProtocolData->SetFrontVelocityCu(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readCalculationProtocol, JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY)));

            return calculationProtocolData;
        }

        return nullptr;
    }

    map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>>
    JsonInputGrassWaveRunupCalculationDefinitionParser::ReadTopLayerDefinitionData(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS);

            for (const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputGrassWaveRunupTopLayerDefinitionData>();

                topLayer->SetCriticalCumulativeOverload(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readTopLayer, JsonInputGrassWaveRunupDefinitions::CRITICAL_CUMULATIVE_OVERLOAD)));
                topLayer->SetCriticalFrontVelocity(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readTopLayer, JsonInputGrassWaveRunupDefinitions::CRITICAL_FRONT_VELOCITY)));

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }
}

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

#include "JsonInputGrassWaveImpactCalculationDefinitionParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassWaveImpactCalculationDefinitionData.h"
#include "JsonInputGrassWaveImpactDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputGrassWaveImpactCalculationDefinitionParser::JsonInputGrassWaveImpactCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputGrassWaveImpactCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputGrassWaveImpactCalculationDefinitionData>(
            move(failureNumber), ReadTopLayerDefinitionData(readCalculationMethod));

        calculationDefinition->SetTemax(
            JsonInputParserHelper::ParseOptionalDouble(readCalculationMethod, JsonInputGrassWaveImpactDefinitions::TEMAX));

        calculationDefinition->SetTemin(
            JsonInputParserHelper::ParseOptionalDouble(readCalculationMethod, JsonInputGrassWaveImpactDefinitions::TEMIN));

        if (readCalculationMethod.contains(JsonInputDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactN(
                JsonInputParserHelper::ParseOptionalDouble(readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::N_COEFFICIENT));

            calculationDefinition->SetWaveAngleImpactQ(
                JsonInputParserHelper::ParseOptionalDouble(readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::Q_COEFFICIENT));

            calculationDefinition->SetWaveAngleImpactR(
                JsonInputParserHelper::ParseOptionalDouble(readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::R_COEFFICIENT));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::LOADING_AREA))
        {
            const auto& readLoadingArea = readCalculationMethod.at(JsonInputDefinitions::LOADING_AREA);

            if (readLoadingArea.contains(JsonInputDefinitions::UPPER_LIMIT))
            {
                const auto& readUpperLimitLoadingArea = readLoadingArea.at(JsonInputDefinitions::UPPER_LIMIT);

                calculationDefinition->SetUpperLimitLoading(
                    JsonInputParserHelper::ParseOptionalDouble(readUpperLimitLoadingArea, JsonInputDefinitions::A_COEFFICIENT));
            }

            if (readLoadingArea.contains(JsonInputDefinitions::LOWER_LIMIT))
            {
                const auto& readLowerLimitLoadingArea = readLoadingArea.at(JsonInputDefinitions::LOWER_LIMIT);

                calculationDefinition->SetLowerLimitLoading(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoadingArea, JsonInputDefinitions::A_COEFFICIENT));
            }
        }

        return calculationDefinition;
    }

    map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveImpactTopLayerDefinitionData>>
    JsonInputGrassWaveImpactCalculationDefinitionParser::ReadTopLayerDefinitionData(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveImpactTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            for (const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS); const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputGrassWaveImpactTopLayerDefinitionData>();

                if (readTopLayer.contains(JsonInputGrassWaveImpactDefinitions::TIME_LINE))
                {
                    const auto& readTimeLine = readTopLayer.at(JsonInputGrassWaveImpactDefinitions::TIME_LINE);

                    topLayer->SetTimeLineA(
                        JsonInputParserHelper::ParseOptionalDouble(readTimeLine, JsonInputDefinitions::A_COEFFICIENT));
                    topLayer->SetTimeLineB(
                        JsonInputParserHelper::ParseOptionalDouble(readTimeLine, JsonInputDefinitions::B_COEFFICIENT));
                    topLayer->SetTimeLineC(
                        JsonInputParserHelper::ParseOptionalDouble(readTimeLine, JsonInputDefinitions::C_COEFFICIENT));
                }

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }
}
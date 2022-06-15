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

#include "JsonInputAsphaltWaveImpactCalculationDefinitionParser.h"

#include "JsonInputAsphaltWaveImpactCalculationDefinitionData.h"
#include "JsonInputAsphaltWaveImpactDefinitions.h"
#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputAsphaltRevetmentTopLayerType,
        {
            {
                JsonInputAsphaltRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputAsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete,
                JsonInputAsphaltWaveImpactDefinitions::TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE
            }
        });

    JsonInputAsphaltWaveImpactCalculationDefinitionParser::JsonInputAsphaltWaveImpactCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputAsphaltWaveImpactCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputAsphaltWaveImpactCalculationDefinitionData>(
            move(failureNumber), ReadTopLayerDefinitionData(readCalculationMethod));

        calculationDefinition->SetDensityOfWater(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputAsphaltWaveImpactDefinitions::DENSITY_OF_WATER)));

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod.at(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES);

            calculationDefinition->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER))
        {
            const auto& readImpactNumber = readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER);

            calculationDefinition->SetImpactNumberC(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readImpactNumber, JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER_C)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS))
        {
            calculationDefinition->SetWidthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS))));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS))
        {
            calculationDefinition->SetDepthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS))));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS))
        {
            calculationDefinition->SetImpactFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS))));
        }

        return calculationDefinition;
    }

    map<JsonInputAsphaltRevetmentTopLayerType, unique_ptr<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>
    JsonInputAsphaltWaveImpactCalculationDefinitionParser::ReadTopLayerDefinitionData(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputAsphaltRevetmentTopLayerType, unique_ptr<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS);

            for (const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputAsphaltWaveImpactTopLayerDefinitionData>();

                if (readTopLayer.contains(JsonInputAsphaltWaveImpactDefinitions::FATIGUE))
                {
                    const auto& readFatigue = readTopLayer.at(JsonInputAsphaltWaveImpactDefinitions::FATIGUE);

                    topLayer->SetFatigueAlpha(
                        forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                            readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_ALPHA)));
                    topLayer->SetFatigueBeta(
                        forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                            readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_BETA)));
                }

                if (readTopLayer.contains(JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION))
                {
                    const auto& readStiffnessRelation = readTopLayer.at(JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION);

                    topLayer->SetStiffnessRelationNu(
                        forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                            readStiffnessRelation, JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION_NU)));
                }

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputAsphaltRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }

    unique_ptr<vector<pair<double, double>>> JsonInputAsphaltWaveImpactCalculationDefinitionParser::ParseFactorsTable(
        const json& factorsTable) const
    {
        auto readFactors = make_unique<vector<pair<double, double>>>();

        for (const auto& factor : factorsTable)
        {
            readFactors->push_back(factor.get<pair<double, double>>());
        }

        return readFactors;
    }
}
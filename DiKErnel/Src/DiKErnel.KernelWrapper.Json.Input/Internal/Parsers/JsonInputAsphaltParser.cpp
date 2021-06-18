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

#include "JsonInputAsphaltParser.h"

#include "JsonInputAsphaltRevetmentDefinitions.h"
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
                JsonInputAsphaltRevetmentTopLayerType::WAB, JsonInputAsphaltRevetmentDefinitions::TOP_LAYER_TYPE_WAD
            }
        });

    unique_ptr<JsonInputAsphaltRevetmentLocationData> JsonInputAsphaltParser::ParseRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputAsphaltRevetmentLocationData>(
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputAsphaltRevetmentTopLayerType>(),
            readRevetment[JsonInputAsphaltRevetmentDefinitions::FAILURE_TENSION],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::DENSITY_OF_WATER],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::SOIL_ELASTICITY],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::THICKNESS_UPPER_LAYER],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::ELASTIC_MODULUS_UPPER_LAYER]);

        locationData->SetThicknessSubLayer(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputAsphaltRevetmentDefinitions::THICKNESS_SUB_LAYER)));
        locationData->SetElasticModulusSubLayer(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputAsphaltRevetmentDefinitions::ELASTIC_MODULUS_SUB_LAYER)));

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod[JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES];

            locationData->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltRevetmentDefinitions::FATIGUE))
        {
            const auto& readFatigue = readCalculationMethod[JsonInputAsphaltRevetmentDefinitions::FATIGUE];

            locationData->SetFatigueAlpha(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltRevetmentDefinitions::FATIGUE_ALPHA)));
            locationData->SetFatigueBeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltRevetmentDefinitions::FATIGUE_BETA)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltRevetmentDefinitions::IMPACT_NUMBER))
        {
            const auto& readImpactNumber = readCalculationMethod[JsonInputAsphaltRevetmentDefinitions::IMPACT_NUMBER];

            locationData->SetImpactNumberC(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readImpactNumber, JsonInputAsphaltRevetmentDefinitions::IMPACT_NUMBER_C)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltRevetmentDefinitions::STIFFNESS_RELATION))
        {
            const auto& readStiffnessRelation = readCalculationMethod[JsonInputAsphaltRevetmentDefinitions::STIFFNESS_RELATION];

            locationData->SetStiffnessRelationNu(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readStiffnessRelation, JsonInputAsphaltRevetmentDefinitions::STIFFNESS_RELATION_NU)));
        }

        return locationData;
    }
}

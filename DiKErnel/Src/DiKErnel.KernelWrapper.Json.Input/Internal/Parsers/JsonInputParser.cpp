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

#include "JsonInputParser.h"

#include <fstream>

#include "JsonInputAsphaltWaveImpactCalculationDefinitionParser.h"
#include "JsonInputAsphaltWaveImpactParser.h"
#include "JsonInputCalculationDefinitionParser.h"
#include "JsonInputDefinitions.h"
#include "JsonInputGrassWaveImpactCalculationDefinitionParser.h"
#include "JsonInputGrassWaveImpactParser.h"
#include "JsonInputGrassWaveRunupCalculationDefinitionParser.h"
#include "JsonInputGrassWaveRunupParser.h"
#include "JsonInputNaturalStoneCalculationDefinitionParser.h"
#include "JsonInputNaturalStoneParser.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputCalculationType,
        {
            {
                JsonInputCalculationType::Unknown, nullptr
            },
            {
                JsonInputCalculationType::AsphaltWaveImpact, JsonInputDefinitions::CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT
            },
            {
                JsonInputCalculationType::GrassWaveImpact, JsonInputDefinitions::CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT
            },
            {
                JsonInputCalculationType::GrassWaveRunup, JsonInputDefinitions::CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP
            },
            {
                JsonInputCalculationType::NaturalStone, JsonInputDefinitions::CALCULATION_METHOD_TYPE_NATURAL_STONE
            },
        });

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputProcessType,
        {
            {
                JsonInputProcessType::Unknown, nullptr
            },
            {
                JsonInputProcessType::Failure, JsonInputDefinitions::PROCESS_TYPE_FAILURE
            },
            {
                JsonInputProcessType::Damage, JsonInputDefinitions::PROCESS_TYPE_DAMAGE
            },
            {
                JsonInputProcessType::Physics, JsonInputDefinitions::PROCESS_TYPE_PHYSICS
            }
        });

    unique_ptr<JsonInputData> JsonInputParser::GetJsonInputData(
        const string& filePath)
    {
        const auto json = ReadJson(filePath);

        const auto& readCalculationData = json.at(JsonInputDefinitions::CALCULATION_DATA);

        return make_unique<JsonInputData>(
            ParseProcessData(json),
            make_unique<JsonInputCalculationData>(
                ParseTime(readCalculationData),
                ParseHydraulicData(readCalculationData),
                ParseDikeProfileData(readCalculationData),
                ParseLocationData(readCalculationData),
                ParseCalculationDefinitionData(readCalculationData)
            )
        );
    }

    json JsonInputParser::ReadJson(
        const string& filePath)
    {
        ifstream ifs(filePath);
        return json::parse(ifs);
    }

    unique_ptr<JsonInputProcessData> JsonInputParser::ParseProcessData(
        const json& readJson)
    {
        unique_ptr<JsonInputProcessType> readProcessType = nullptr;

        if (readJson.contains(JsonInputDefinitions::PROCESS_DATA))
        {
            const auto& readProcessData = readJson.at(JsonInputDefinitions::PROCESS_DATA);
            readProcessType = make_unique<JsonInputProcessType>(readProcessData.at(JsonInputDefinitions::PROCESS_TYPE).get<JsonInputProcessType>());
        }

        auto processData = make_unique<JsonInputProcessData>();
        processData->SetProcessType(move(readProcessType));

        return processData;
    }

    vector<int> JsonInputParser::ParseTime(
        const json& readCalculationData)
    {
        return readCalculationData.at(JsonInputDefinitions::TIME).get<vector<int>>();
    }

    unique_ptr<JsonInputHydraulicData> JsonInputParser::ParseHydraulicData(
        const json& readCalculationData)
    {
        const auto& readHydraulicLoads = readCalculationData.at(JsonInputDefinitions::HYDRAULIC_LOADS);

        return make_unique<JsonInputHydraulicData>(
            readHydraulicLoads.at(JsonInputDefinitions::WATER_LEVELS).get<vector<double>>(),
            readHydraulicLoads.at(JsonInputDefinitions::WAVE_HEIGHTS_HM0).get<vector<double>>(),
            readHydraulicLoads.at(JsonInputDefinitions::WAVE_PERIODS_TM10).get<vector<double>>(),
            readHydraulicLoads.at(JsonInputDefinitions::WAVE_ANGLES).get<vector<double>>());
    }

    unique_ptr<JsonInputDikeProfileData> JsonInputParser::ParseDikeProfileData(
        const json& readCalculationData)
    {
        const auto& readDikeProfile = readCalculationData.at(JsonInputDefinitions::DIKE_PROFILE);

        auto characteristicPoints = vector<pair<JsonInputCharacteristicPointType, double>>();
        TryParseCharacteristicPoint(readDikeProfile, characteristicPoints, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_OUTER_TOE,
                                    JsonInputCharacteristicPointType::OuterToe);
        TryParseCharacteristicPoint(readDikeProfile, characteristicPoints, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_OUTER_CREST,
                                    JsonInputCharacteristicPointType::OuterCrest);
        TryParseCharacteristicPoint(readDikeProfile, characteristicPoints, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM,
                                    JsonInputCharacteristicPointType::NotchOuterBerm);
        TryParseCharacteristicPoint(readDikeProfile, characteristicPoints, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM,
                                    JsonInputCharacteristicPointType::CrestOuterBerm);

        return make_unique<JsonInputDikeProfileData>(
            readDikeProfile.at(JsonInputDefinitions::DIKE_PROFILE_POINT_X).get<vector<double>>(),
            readDikeProfile.at(JsonInputDefinitions::DIKE_PROFILE_POINT_Z).get<vector<double>>(),
            move(characteristicPoints));
    }

    void JsonInputParser::TryParseCharacteristicPoint(
        const json& readDikeProfile,
        vector<pair<JsonInputCharacteristicPointType, double>>& characteristicPoints,
        const string& characteristicPointDefinition,
        JsonInputCharacteristicPointType characteristicPointType)
    {
        if (readDikeProfile.contains(characteristicPointDefinition))
        {
            characteristicPoints.emplace_back(characteristicPointType, readDikeProfile.at(characteristicPointDefinition).get<double>());
        }
    }

    vector<unique_ptr<JsonInputLocationData>> JsonInputParser::ParseLocationData(
        const json& readCalculationData)
    {
        auto parsedLocations = vector<unique_ptr<JsonInputLocationData>>();

        const auto& readLocations = readCalculationData.at(JsonInputDefinitions::LOCATIONS);

        for (const auto& readLocation : readLocations)
        {
            const auto& calculationType = readLocation.at(JsonInputDefinitions::CALCULATION_METHOD_TYPE).get<JsonInputCalculationType>();

            unique_ptr<JsonInputLocationParser> parser = nullptr;

            if (calculationType == JsonInputCalculationType::AsphaltWaveImpact)
            {
                parser = CreateLocationParser<JsonInputAsphaltWaveImpactParser>(readLocation);
            }

            if (calculationType == JsonInputCalculationType::GrassWaveImpact)
            {
                parser = CreateLocationParser<JsonInputGrassWaveImpactParser>(readLocation);
            }

            if (calculationType == JsonInputCalculationType::GrassWaveRunup)
            {
                parser = CreateLocationParser<JsonInputGrassWaveRunupParser>(readLocation);
            }

            if (calculationType == JsonInputCalculationType::NaturalStone)
            {
                parser = CreateLocationParser<JsonInputNaturalStoneParser>(readLocation);
            }

            parsedLocations.push_back(forward<unique_ptr<JsonInputLocationData>>(parser->Parse()));
        }

        return parsedLocations;
    }

    map<JsonInputCalculationType, unique_ptr<JsonInputCalculationDefinitionData>> JsonInputParser::ParseCalculationDefinitionData(
        const json& readCalculationData)
    {
        auto parsedCalculationDefinitions = map<JsonInputCalculationType, unique_ptr<JsonInputCalculationDefinitionData>>();

        if (readCalculationData.contains(JsonInputDefinitions::CALCULATION_METHODS))
        {
            const auto& readCalculationDefinitions = readCalculationData.at(JsonInputDefinitions::CALCULATION_METHODS);

            for (const auto& readCalculationDefinition : readCalculationDefinitions)
            {
                const auto& calculationType = readCalculationDefinition.at(JsonInputDefinitions::CALCULATION_METHOD_TYPE)
                                                                       .get<JsonInputCalculationType>();

                unique_ptr<JsonInputCalculationDefinitionParser> parser = nullptr;

                if (calculationType == JsonInputCalculationType::AsphaltWaveImpact)
                {
                    parser = CreateCalculationDefinitionParser<JsonInputAsphaltWaveImpactCalculationDefinitionParser>(readCalculationDefinition);
                }

                if (calculationType == JsonInputCalculationType::GrassWaveImpact)
                {
                    parser = CreateCalculationDefinitionParser<JsonInputGrassWaveImpactCalculationDefinitionParser>(readCalculationDefinition);
                }

                if (calculationType == JsonInputCalculationType::GrassWaveRunup)
                {
                    parser = CreateCalculationDefinitionParser<JsonInputGrassWaveRunupCalculationDefinitionParser>(readCalculationDefinition);
                }

                if (calculationType == JsonInputCalculationType::NaturalStone)
                {
                    parser = CreateCalculationDefinitionParser<JsonInputNaturalStoneCalculationDefinitionParser>(readCalculationDefinition);
                }

                parsedCalculationDefinitions.insert(pair(calculationType,
                                                         forward<unique_ptr<JsonInputCalculationDefinitionData>>(parser->Parse())));
            }
        }

        return parsedCalculationDefinitions;
    }

    template <typename T>
    unique_ptr<T> JsonInputParser::CreateLocationParser(
        const json& readLocation)
    {
        return make_unique<T>(readLocation);
    }

    template <typename T>
    unique_ptr<T> JsonInputParser::CreateCalculationDefinitionParser(
        const json& readCalculationDefinition)
    {
        return make_unique<T>(readCalculationDefinition);
    }
}

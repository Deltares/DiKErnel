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

#include "JsonInputParser.h"

#include <fstream>

#include "JsonInputAsphaltWaveImpactParser.h"
#include "JsonInputDefinitions.h"
#include "JsonInputGrassWaveImpactParser.h"
#include "JsonInputGrassWaveRunupParser.h"
#include "JsonInputNaturalStoneParser.h"
#include "JsonInputParserHelper.h"

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

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonProcessType,
        {
            {
                JsonProcessType::Unknown, nullptr
            },
            {
                JsonProcessType::Failure, JsonInputDefinitions::PROCESS_TYPE_FAILURE
            },
            {
                JsonProcessType::Damage, JsonInputDefinitions::PROCESS_TYPE_DAMAGE
            },
            {
                JsonProcessType::Physics, JsonInputDefinitions::PROCESS_TYPE_PHYSICS
            }
        });

    unique_ptr<JsonInputData> JsonInputParser::GetJsonInputData(
        const string& filePath)
    {
        const auto json = ReadJson(filePath);

        const auto& readCalculationData = json[JsonInputDefinitions::CALCULATION_DATA];

        return make_unique<JsonInputData>(
            ParseProcessData(json),
            make_unique<JsonInputCalculationData>(
                ParseTime(readCalculationData),
                ParseHydraulicData(readCalculationData),
                ParseLocationData(readCalculationData)
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
        unique_ptr<JsonProcessType> readProcessType = nullptr;

        if (readJson.contains(JsonInputDefinitions::PROCESS_DATA))
        {
            const auto& readProcessData = readJson[JsonInputDefinitions::PROCESS_DATA];
            readProcessType = make_unique<JsonProcessType>(readProcessData[JsonInputDefinitions::PROCESS_TYPE].get<JsonProcessType>());
        }

        auto processData = make_unique<JsonInputProcessData>();
        processData->SetProcessType(move(readProcessType));

        return processData;
    }

    vector<int> JsonInputParser::ParseTime(
        const json& readCalculationData)
    {
        return readCalculationData[JsonInputDefinitions::TIME].get<vector<int>>();
    }

    unique_ptr<JsonInputHydraulicData> JsonInputParser::ParseHydraulicData(
        const json& readCalculationData)
    {
        const auto& readHydraulicLoads = readCalculationData[JsonInputDefinitions::HYDRAULIC_LOADS];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonInputDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP];

        vector<unique_ptr<JsonInputTimeDependentHydraulicData>> timeDependentHydraulicData;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            timeDependentHydraulicData.push_back(
                make_unique<JsonInputTimeDependentHydraulicData>(
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WATER_LEVEL].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_HEIGHT_HM0].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_PERIOD_TM10].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_ANGLE].get<double>()));
        }

        return make_unique<JsonInputHydraulicData>(
            move(timeDependentHydraulicData));
    }

    vector<unique_ptr<JsonInputLocationData>> JsonInputParser::ParseLocationData(
        const json& readCalculationData)
    {
        auto parsedLocations = vector<unique_ptr<JsonInputLocationData>>();

        const auto& readLocations = readCalculationData[JsonInputDefinitions::LOCATIONS];

        for (const auto& readLocation : readLocations)
        {
            unique_ptr<double> initialDamage = nullptr;
            unique_ptr<double> failureNumber = nullptr;

            if (readLocation.contains(JsonInputDefinitions::DAMAGE))
            {
                const auto& readDamageVariables = readLocation[JsonInputDefinitions::DAMAGE];

                initialDamage = JsonInputParserHelper::ParseOptionalDouble(readDamageVariables, JsonInputDefinitions::INITIAL_DAMAGE);
                failureNumber = JsonInputParserHelper::ParseOptionalDouble(readDamageVariables, JsonInputDefinitions::FAILURE_NUMBER);
            }

            const auto& readRevetment = readLocation[JsonInputDefinitions::REVETMENT];
            const auto& readCalculationMethod = readRevetment[JsonInputDefinitions::CALCULATION_METHOD][0];
            const auto& calculationType = readCalculationMethod[JsonInputDefinitions::CALCULATION_METHOD_TYPE].get<JsonInputCalculationType>();

            auto parsedLocation = make_unique<JsonInputLocationData>(
                readLocation[JsonInputDefinitions::NAME].get<string>(),
                make_unique<JsonInputDamageData>(move(initialDamage), move(failureNumber)),
                ParseRevetmentLocationData(readRevetment, readCalculationMethod, calculationType),
                ParseProfileSchematizationData(readLocation[JsonInputDefinitions::PROFILE_SCHEMATIZATION], calculationType));

            parsedLocations.emplace_back(move(parsedLocation));
        }

        return parsedLocations;
    }

    unique_ptr<IJsonInputRevetmentLocationData> JsonInputParser::ParseRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationMethod,
        const JsonInputCalculationType calculationType)
    {
        unique_ptr<IJsonInputRevetmentLocationData> revetmentLocationData;

        if (calculationType == JsonInputCalculationType::AsphaltWaveImpact)
        {
            revetmentLocationData = JsonInputAsphaltWaveImpactParser::ParseRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        if (calculationType == JsonInputCalculationType::GrassWaveImpact)
        {
            revetmentLocationData = JsonInputGrassWaveImpactParser::ParseRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        if (calculationType == JsonInputCalculationType::GrassWaveRunup)
        {
            revetmentLocationData = JsonInputGrassWaveRunupParser::ParseRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        if (calculationType == JsonInputCalculationType::NaturalStone)
        {
            revetmentLocationData = JsonInputNaturalStoneParser::ParseRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        return revetmentLocationData;
    }

    unique_ptr<JsonInputProfileSchematizationData> JsonInputParser::ParseProfileSchematizationData(
        const json& readProfileSchematization,
        const JsonInputCalculationType calculationType)
    {
        if (calculationType == JsonInputCalculationType::GrassWaveRunup)
        {
            return JsonInputGrassWaveRunupParser::ParseProfileSchematizationData(readProfileSchematization);
        }

        return make_unique<JsonInputProfileSchematizationData>(
            readProfileSchematization[JsonInputDefinitions::TAN_A].get<double>(),
            readProfileSchematization[JsonInputDefinitions::POSITION_Z].get<double>());
    }
}

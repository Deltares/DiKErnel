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

#include "JsonInputDefinitions.h"
#include "JsonInputNaturalStoneRevetmentLocationData.h"
#include "JsonInputParserHelper.h"
#include "NaturalStoneJsonInputDefinitions.h"
#include "NaturalStoneJsonInputParser.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(
        JsonInputParser::CalculationType,
        {
            {
                JsonInputParser::CalculationType::Unknown, nullptr
            },
            {
                JsonInputParser::CalculationType::NaturalStone, NaturalStoneJsonInputDefinitions::CALCULATION_METHOD_TYPE
            }
        });

    unique_ptr<JsonInputData> JsonInputParser::GetJsonInputData(
        const string& filePath)
    {
        const auto json = ReadJson(filePath);

        return make_unique<JsonInputData>(
            make_unique<JsonInputCalculationData>(
                GetTimes(json),
                GetHydraulicData(json),
                GetInputLocationData(json)
            )
        );
    }

    json JsonInputParser::ReadJson(
        const string& filePath)
    {
        ifstream ifs(filePath);
        return json::parse(ifs);
    }

    vector<int> JsonInputParser::GetTimes(
        const json& json)
    {
        return json[JsonInputDefinitions::CALCULATION_DATA][JsonInputDefinitions::TIME].get<vector<int>>();
    }

    unique_ptr<JsonInputHydraulicData> JsonInputParser::GetHydraulicData(
        const json& json)
    {
        const auto& readHydraulicLoads = json[JsonInputDefinitions::HYDRAULIC_LOADS];
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

    vector<unique_ptr<JsonInputLocationData>> JsonInputParser::GetInputLocationData(
        const json& json)
    {
        auto parsedLocations = vector<unique_ptr<JsonInputLocationData>>();

        const auto& readLocations = json[JsonInputDefinitions::LOCATIONS];

        for (const auto& readLocation : readLocations)
        {
            unique_ptr<double> initialDamage = nullptr;
            unique_ptr<double> failureNumber = nullptr;

            if (readLocation.contains(JsonInputDefinitions::DAMAGE))
            {
                const auto& readDamageVariables = readLocation[JsonInputDefinitions::DAMAGE];

                initialDamage = JsonInputParserHelper::ReadOptionalValue(readDamageVariables, JsonInputDefinitions::INITIAL_DAMAGE);
                failureNumber = JsonInputParserHelper::ReadOptionalValue(readDamageVariables, JsonInputDefinitions::FAILURE_NUMBER);
            }

            const auto& readProfileSchematization = readLocation[JsonInputDefinitions::PROFILE_SCHEMATIZATION];

            auto parsedLocation = make_unique<JsonInputLocationData>(
                readLocation[JsonInputDefinitions::NAME].get<string>(),
                make_unique<JsonInputDamageData>(move(initialDamage), move(failureNumber)),
                GetRevetmentLocationData(readLocation[JsonInputDefinitions::REVETMENT]),
                make_unique<JsonInputProfileSchematizationData>(
                    readProfileSchematization[JsonInputDefinitions::TAN_A].get<double>(),
                    readProfileSchematization[JsonInputDefinitions::POSITION_Z].get<double>()));

            parsedLocations.emplace_back(move(parsedLocation));
        }

        return parsedLocations;
    }

    unique_ptr<IJsonInputRevetmentLocationData> JsonInputParser::GetRevetmentLocationData(
        const basic_json<>::value_type& readRevetment)
    {
        const auto& readCalculationMethod = readRevetment[JsonInputDefinitions::CALCULATION_METHOD][0];

        unique_ptr<IJsonInputRevetmentLocationData> revetmentLocationData;

        if (readCalculationMethod[JsonInputDefinitions::CALCULATION_METHOD_TYPE].get<CalculationType>() == CalculationType::NaturalStone)
        {
            revetmentLocationData = NaturalStoneJsonInputParser::ReadRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        return revetmentLocationData;
    }
}

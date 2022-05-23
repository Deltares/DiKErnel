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

#include "JsonInputAsphaltWaveImpactParser.h"
#include "JsonInputCalculationType.h"
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

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputCharacteristicPointType,
        {
            {
                JsonInputCharacteristicPointType::Unknown, nullptr
            },
            {
                JsonInputCharacteristicPointType::OuterToe, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_OUTER_TOE
            },
            {
                JsonInputCharacteristicPointType::OuterCrest, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_OUTER_CREST
            },
            {
                JsonInputCharacteristicPointType::CrestOuterBerm, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM
            },
            {
                JsonInputCharacteristicPointType::NotchOuterBerm, JsonInputDefinitions::CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM
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
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads.at(JsonInputDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP);

        vector<unique_ptr<JsonInputTimeDependentHydraulicData>> timeDependentHydraulicData;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            timeDependentHydraulicData.push_back(
                make_unique<JsonInputTimeDependentHydraulicData>(
                    readBoundaryConditionsForTimeStep.at(JsonInputDefinitions::WATER_LEVEL).get<double>(),
                    readBoundaryConditionsForTimeStep.at(JsonInputDefinitions::WAVE_HEIGHT_HM0).get<double>(),
                    readBoundaryConditionsForTimeStep.at(JsonInputDefinitions::WAVE_PERIOD_TM10).get<double>(),
                    readBoundaryConditionsForTimeStep.at(JsonInputDefinitions::WAVE_ANGLE).get<double>()));
        }

        return make_unique<JsonInputHydraulicData>(
            move(timeDependentHydraulicData));
    }

    unique_ptr<JsonInputDikeProfileData> JsonInputParser::ParseDikeProfileData(
        const json& readCalculationData)
    {
        const auto& readDikeProfile = readCalculationData.at(JsonInputDefinitions::DIKE_PROFILE);

        vector<unique_ptr<JsonInputDikeProfilePoint>> dikeProfilePoints;

        for (const auto& readDikeProfilePoint : readDikeProfile)
        {
            auto dikeProfilePoint = make_unique<JsonInputDikeProfilePoint>(
                readDikeProfilePoint.at(JsonInputDefinitions::DIKE_PROFILE_POINT_X).get<double>(),
                readDikeProfilePoint.at(JsonInputDefinitions::DIKE_PROFILE_POINT_Z).get<double>());

            if (readDikeProfilePoint.contains(JsonInputDefinitions::CHARACTERISTIC_POINT))
            {
                auto readCharacteristicPointType = make_unique<JsonInputCharacteristicPointType>(
                    readDikeProfilePoint.at(JsonInputDefinitions::CHARACTERISTIC_POINT).get<JsonInputCharacteristicPointType>());

                dikeProfilePoint->SetCharacteristicPointType(move(readCharacteristicPointType));
            }

            dikeProfilePoints.push_back(move(dikeProfilePoint));
        }

        return make_unique<JsonInputDikeProfileData>(move(dikeProfilePoints));
    }

    vector<unique_ptr<JsonInputLocationData>> JsonInputParser::ParseLocationData(
        const json& readCalculationData)
    {
        auto parsedLocations = vector<unique_ptr<JsonInputLocationData>>();

        const auto& readLocations = readCalculationData.at(JsonInputDefinitions::LOCATIONS);

        for (const auto& readLocation : readLocations)
        {
            const auto& readRevetment = readLocation.at(JsonInputDefinitions::REVETMENT);
            const auto& readCalculationMethod = readRevetment.at(JsonInputDefinitions::CALCULATION_METHOD).at(0);
            const auto& calculationType = readCalculationMethod.at(JsonInputDefinitions::CALCULATION_METHOD_TYPE).get<JsonInputCalculationType>();

            unique_ptr<JsonInputLocationParser> parser = nullptr;

            if (calculationType == JsonInputCalculationType::AsphaltWaveImpact)
            {
                parser = CreateParser<JsonInputAsphaltWaveImpactParser>(readLocation, readRevetment, readCalculationMethod);
            }

            if (calculationType == JsonInputCalculationType::GrassWaveImpact)
            {
                parser = CreateParser<JsonInputGrassWaveImpactParser>(readLocation, readRevetment, readCalculationMethod);
            }

            if (calculationType == JsonInputCalculationType::GrassWaveRunup)
            {
                parser = CreateParser<JsonInputGrassWaveRunupParser>(readLocation, readRevetment, readCalculationMethod);
            }

            if (calculationType == JsonInputCalculationType::NaturalStone)
            {
                parser = CreateParser<JsonInputNaturalStoneParser>(readLocation, readRevetment, readCalculationMethod);
            }

            parsedLocations.push_back(forward<unique_ptr<JsonInputLocationData>>(parser->Parse()));
        }

        return parsedLocations;
    }

    template <typename T>
    unique_ptr<T> JsonInputParser::CreateParser(
        const json& readLocation,
        const json& readRevetment,
        const json& readCalculationMethod)
    {
        return make_unique<T>(readLocation, readRevetment, readCalculationMethod);
    }
}

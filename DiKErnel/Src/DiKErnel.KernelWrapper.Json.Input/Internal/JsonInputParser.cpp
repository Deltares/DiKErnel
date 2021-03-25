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
                JsonInputParser::CalculationType::NaturalStone, JsonInputDefinitions::CALCULATION_METHOD_TYPE_NATURAL_STONE
            }
        });

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputNaturalStoneRevetmentLocationData::TopLayerType,
        {
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::Unknown, nullptr
            },
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::NordicStone, JsonInputDefinitions::TOP_LAYER_TYPE_NORDIC_STONE
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
            const auto& readDamageVariables = readLocation[JsonInputDefinitions::DAMAGE];
            const auto& readProfileSchematization = readLocation[JsonInputDefinitions::PROFILE_SCHEMATIZATION];

            auto parsedLocation = make_unique<JsonInputLocationData>(
                readLocation[JsonInputDefinitions::NAME].get<string>(),
                make_unique<JsonInputDamageData>(
                    readDamageVariables[JsonInputDefinitions::INITIAL_DAMAGE].get<double>(),
                    ReadOptionalValue(readDamageVariables, JsonInputDefinitions::CRITICAL_DAMAGE)),
                GetRevetmentLocationData(readLocation[JsonInputDefinitions::REVETMENT]),
                make_unique<JsonInputProfileSchematizationData>(
                    readProfileSchematization[JsonInputDefinitions::TAN_A].get<double>(),
                    readProfileSchematization[JsonInputDefinitions::POSITION_Z].get<double>()));

            parsedLocations.emplace_back(move(parsedLocation));
        }

        return parsedLocations;
    }

    unique_ptr<JsonInputRevetmentLocationData> JsonInputParser::GetRevetmentLocationData(
        const basic_json<>::value_type& readRevetment)
    {
        const auto& readCalculationMethod = readRevetment[JsonInputDefinitions::CALCULATION_METHOD][0];

        unique_ptr<JsonInputRevetmentLocationData> revetmentLocationData;

        if (readCalculationMethod[JsonInputDefinitions::CALCULATION_METHOD_TYPE].get<CalculationType>() == CalculationType::NaturalStone)
        {
            revetmentLocationData = ReadNaturalStoneRevetmentLocationData(readRevetment, readCalculationMethod);
        }

        return revetmentLocationData;
    }

    unique_ptr<JsonInputNaturalStoneRevetmentLocationData> JsonInputParser::ReadNaturalStoneRevetmentLocationData(
        const basic_json<>::value_type& readRevetment,
        const basic_json<>::value_type& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputNaturalStoneRevetmentLocationData>(
            readRevetment[JsonInputDefinitions::RELATIVE_DENSITY],
            readRevetment[JsonInputDefinitions::THICKNESS_TOP_LAYER],
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputNaturalStoneRevetmentLocationData::TopLayerType>());

        if (readCalculationMethod.contains(JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE))
        {
            const auto& readHydraulicLoads = readCalculationMethod[JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE];

            locationData->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP)));
            locationData->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP)));
            locationData->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP)));
            locationData->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP)));
            locationData->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS)));
            locationData->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS)));
            locationData->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS)));
            locationData->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS)));
            locationData->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads, JsonInputDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE))
        {
            const auto& readUpperLimitLoading = readCalculationMethod[JsonInputDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE];

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL)));
            locationData->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL)));
            locationData->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE))
        {
            const auto& readLowerLimitLoading = readCalculationMethod[JsonInputDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE];

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    ReadOptionalValue(readLowerLimitLoading, JsonInputDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL)));
            locationData->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readLowerLimitLoading, JsonInputDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL)));
            locationData->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readLowerLimitLoading, JsonInputDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod[JsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE];

            locationData->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX)));
            locationData->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE))
        {
            const auto& readNormativeWidthOfWaveImpact =
                    readCalculationMethod[JsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE];

            locationData->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(ReadOptionalValue(readNormativeWidthOfWaveImpact,
                                                              JsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI)));
            locationData->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(ReadOptionalValue(readNormativeWidthOfWaveImpact,
                                                              JsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE))
        {
            const auto& readWaveAngleImpact = readCalculationMethod[JsonInputDefinitions::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE];

            locationData->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(ReadOptionalValue(readWaveAngleImpact,
                                                              JsonInputDefinitions::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETA_MAX)));
        }

        return locationData;
    }

    unique_ptr<double> JsonInputParser::ReadOptionalValue(
        const basic_json<>::value_type& object,
        const string& propertyName)
    {
        return object.contains(propertyName)
                   ? make_unique<double>(object[propertyName].get<double>())
                   : nullptr;
    }
}

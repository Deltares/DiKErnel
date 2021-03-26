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
#include "JsonInputNaturalStoneDefinitions.h"
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
                JsonInputParser::CalculationType::NaturalStone, JsonInputNaturalStoneDefinitions::CALCULATION_METHOD_TYPE
            }
        });

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputNaturalStoneRevetmentLocationData::TopLayerType,
        {
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::Unknown, nullptr
            },
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::NordicStone, JsonInputNaturalStoneDefinitions::TOP_LAYER_TYPE_NORDIC_STONE
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

                initialDamage = ReadOptionalValue(readDamageVariables, JsonInputDefinitions::INITIAL_DAMAGE);
                failureNumber = ReadOptionalValue(readDamageVariables, JsonInputDefinitions::FAILURE_NUMBER);
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

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD))
        {
            const auto& readHydraulicLoads = readCalculationMethod[JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD];

            locationData->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AP)));
            locationData->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BP)));
            locationData->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CP)));
            locationData->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NP)));
            locationData->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AS)));
            locationData->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BS)));
            locationData->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CS)));
            locationData->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NS)));
            locationData->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(ReadOptionalValue(readHydraulicLoads,
                                                              JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_XIB)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod[JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING];

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_AUL)));
            locationData->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_BUL)));
            locationData->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_CUL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod[JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING];

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    ReadOptionalValue(readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_ALL)));
            locationData->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_BLL)));
            locationData->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_CLL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod[
                JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION];

            locationData->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX)));
            locationData->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact =
                    readCalculationMethod[JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT];

            locationData->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI)));
            locationData->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod[JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT];

            locationData->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(ReadOptionalValue(
                    readWaveAngleImpact, JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT_BETA_MAX)));
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

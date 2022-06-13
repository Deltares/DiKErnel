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

#include "JsonInputNaturalStoneParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputNaturalStoneDefinitions.h"
#include "JsonInputNaturalStoneLocationData.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputNaturalStoneRevetmentTopLayerType,
        {
            {
                JsonInputNaturalStoneRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputNaturalStoneRevetmentTopLayerType::NordicStone, JsonInputNaturalStoneDefinitions::TOP_LAYER_TYPE_NORDIC_STONE
            }
        });

    JsonInputNaturalStoneParser::JsonInputNaturalStoneParser(
        const json& readLocation,
        const json& readRevetment,
        const json& readCalculationMethod)
        : JsonInputLocationParser(readLocation, readRevetment, readCalculationMethod) {}

    unique_ptr<JsonInputLocationData> JsonInputNaturalStoneParser::ParseLocationData(
        double x,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<double> initialDamage)
    {
        return make_unique<JsonInputNaturalStoneLocationData>(x, move(initialDamage), move(damageData), ParseRevetmentLocationData());
    }

    unique_ptr<JsonInputNaturalStoneRevetmentLocationData> JsonInputNaturalStoneParser::ParseRevetmentLocationData() const
    {
        const auto& readRevetment = GetReadRevetment();
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto locationData = make_unique<JsonInputNaturalStoneRevetmentLocationData>(
            readRevetment.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputNaturalStoneRevetmentTopLayerType>(),
            readRevetment.at(JsonInputNaturalStoneDefinitions::RELATIVE_DENSITY),
            readRevetment.at(JsonInputNaturalStoneDefinitions::THICKNESS_TOP_LAYER));

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD))
        {
            const auto& readHydraulicLoads = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD);

            locationData->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AP)));
            locationData->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BP)));
            locationData->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CP)));
            locationData->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NP)));
            locationData->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AS)));
            locationData->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BS)));
            locationData->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CS)));
            locationData->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NS)));
            locationData->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_XIB)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL))
        {
            const auto& readSlopeUpperLevel = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL);

            locationData->SetSlopeUpperLevelAus(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlopeUpperLevel, JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL_AUS)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL))
        {
            const auto& readSlopeLowerLevel = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL);

            locationData->SetSlopeLowerLevelAls(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlopeLowerLevel, JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL_ALS)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING);

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_AUL)));
            locationData->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_BUL)));
            locationData->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_CUL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING);

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_ALL)));
            locationData->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_BLL)));
            locationData->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_CLL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION);

            locationData->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX)));
            locationData->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT);

            locationData->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI)));
            locationData->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT);

            locationData->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }

        return locationData;
    }
}

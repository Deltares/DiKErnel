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

#include "NaturalStoneJsonInputParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"
#include "JsonInputNaturalStoneDefinitions.h"

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

    unique_ptr<JsonInputNaturalStoneRevetmentLocationData> NaturalStoneJsonInputParser::ParseRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputNaturalStoneRevetmentLocationData>(
            readRevetment[JsonInputNaturalStoneDefinitions::RELATIVE_DENSITY],
            readRevetment[JsonInputNaturalStoneDefinitions::THICKNESS_TOP_LAYER],
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputNaturalStoneRevetmentTopLayerType>());

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD))
        {
            const auto& readHydraulicLoads = readCalculationMethod[JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD];

            locationData->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AP)));
            locationData->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BP)));
            locationData->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CP)));
            locationData->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NP)));
            locationData->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AS)));
            locationData->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BS)));
            locationData->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CS)));
            locationData->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NS)));
            locationData->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_XIB)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod[JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING];

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_AUL)));
            locationData->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_BUL)));
            locationData->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_CUL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod[JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING];

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    JsonInputParserHelper::ParseOptionalValue(readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_ALL)));
            locationData->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_BLL)));
            locationData->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_CLL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod[
                JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION];

            locationData->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX)));
            locationData->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact =
                    readCalculationMethod[JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT];

            locationData->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI)));
            locationData->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod[JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT];

            locationData->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readWaveAngleImpact, JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }

        return locationData;
    }
}

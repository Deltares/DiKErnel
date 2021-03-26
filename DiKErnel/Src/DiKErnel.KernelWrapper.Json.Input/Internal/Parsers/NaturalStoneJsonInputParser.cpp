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
#include "NaturalStoneJsonInputDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputNaturalStoneRevetmentLocationData::TopLayerType,
        {
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::Unknown, nullptr
            },
            {
                JsonInputNaturalStoneRevetmentLocationData::TopLayerType::NordicStone, NaturalStoneJsonInputDefinitions::TOP_LAYER_TYPE_NORDIC_STONE
            }
        });

    unique_ptr<JsonInputNaturalStoneRevetmentLocationData> NaturalStoneJsonInputParser::ParseRevetmentLocationData(
        const basic_json<>::value_type& readRevetment,
        const basic_json<>::value_type& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputNaturalStoneRevetmentLocationData>(
            readRevetment[NaturalStoneJsonInputDefinitions::RELATIVE_DENSITY],
            readRevetment[NaturalStoneJsonInputDefinitions::THICKNESS_TOP_LAYER],
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputNaturalStoneRevetmentLocationData::TopLayerType>());

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD))
        {
            const auto& readHydraulicLoads = readCalculationMethod[NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD];

            locationData->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_AP)));
            locationData->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_BP)));
            locationData->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_CP)));
            locationData->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_NP)));
            locationData->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_AS)));
            locationData->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_BS)));
            locationData->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_CS)));
            locationData->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_NS)));
            locationData->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readHydraulicLoads, NaturalStoneJsonInputDefinitions::HYDRAULIC_LOAD_XIB)));
        }

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod[NaturalStoneJsonInputDefinitions::UPPER_LIMIT_LOADING];

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, NaturalStoneJsonInputDefinitions::UPPER_LIMIT_LOADING_AUL)));
            locationData->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, NaturalStoneJsonInputDefinitions::UPPER_LIMIT_LOADING_BUL)));
            locationData->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, NaturalStoneJsonInputDefinitions::UPPER_LIMIT_LOADING_CUL)));
        }

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod[NaturalStoneJsonInputDefinitions::LOWER_LIMIT_LOADING];

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    JsonInputParserHelper::ParseOptionalValue(readLowerLimitLoading, NaturalStoneJsonInputDefinitions::LOWER_LIMIT_LOADING_ALL)));
            locationData->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readLowerLimitLoading, NaturalStoneJsonInputDefinitions::LOWER_LIMIT_LOADING_BLL)));
            locationData->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readLowerLimitLoading, NaturalStoneJsonInputDefinitions::LOWER_LIMIT_LOADING_CLL)));
        }

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod[
                NaturalStoneJsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION];

            locationData->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readDistanceMaxWaveElevation, NaturalStoneJsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX)));
            locationData->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readDistanceMaxWaveElevation, NaturalStoneJsonInputDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX)));
        }

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact =
                    readCalculationMethod[NaturalStoneJsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT];

            locationData->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readNormativeWidthOfWaveImpact, NaturalStoneJsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI)));
            locationData->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readNormativeWidthOfWaveImpact, NaturalStoneJsonInputDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)));
        }

        if (readCalculationMethod.contains(NaturalStoneJsonInputDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod[NaturalStoneJsonInputDefinitions::WAVE_ANGLE_IMPACT];

            locationData->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readWaveAngleImpact, NaturalStoneJsonInputDefinitions::WAVE_ANGLE_IMPACT_BETA_MAX)));
        }

        return locationData;
    }
}

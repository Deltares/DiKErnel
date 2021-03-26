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

#include "GrassWaveImpactJsonInputParser.h"

#include "GrassWaveImpactJsonInputDefinitions.h"
#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType,
        {
            {
                JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType::Unknown, nullptr
            },
            {
                JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType::ClosedSod, GrassWaveImpactJsonInputDefinitions::TOP_LAYER_TYPE_CLOSED_SOD
            },
            {
                JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType::OpenSod, GrassWaveImpactJsonInputDefinitions::TOP_LAYER_TYPE_OPEN_SOD
            }
        });

    unique_ptr<JsonInputGrassWaveImpactRevetmentLocationData> GrassWaveImpactJsonInputParser::ParseRevetmentLocationData(
        const basic_json<>::value_type& readRevetment,
        const basic_json<>::value_type& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputGrassWaveImpactRevetmentLocationData>(
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType>());

        locationData->SetFailureTimeAgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                readCalculationMethod, GrassWaveImpactJsonInputDefinitions::FAILURE_TIME_AGWI)));
        locationData->SetFailureTimeBgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                readCalculationMethod, GrassWaveImpactJsonInputDefinitions::FAILURE_TIME_BGWI)));
        locationData->SetFailureTimeCgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                readCalculationMethod, GrassWaveImpactJsonInputDefinitions::FAILURE_TIME_CGWI)));

        if (readCalculationMethod.contains(GrassWaveImpactJsonInputDefinitions::MINIMUM_WAVE_HEIGHT))
        {
            const auto& readMinimumWaveHeight = readCalculationMethod[GrassWaveImpactJsonInputDefinitions::MINIMUM_WAVE_HEIGHT];

            locationData->SetMinimumWaveHeightTemax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readMinimumWaveHeight, GrassWaveImpactJsonInputDefinitions::MINIMUM_WAVE_HEIGHT_TEMAX)));
        }

        if (readCalculationMethod.contains(GrassWaveImpactJsonInputDefinitions::MAXIMUM_WAVE_HEIGHT))
        {
            const auto& readMaximumWaveHeight = readCalculationMethod[GrassWaveImpactJsonInputDefinitions::MAXIMUM_WAVE_HEIGHT];

            locationData->SetMaximumWaveHeightTemin(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readMaximumWaveHeight, GrassWaveImpactJsonInputDefinitions::MINIMUM_WAVE_HEIGHT_TEMAX)));
        }

        if (readCalculationMethod.contains(GrassWaveImpactJsonInputDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod[GrassWaveImpactJsonInputDefinitions::WAVE_ANGLE_IMPACT];

            locationData->SetWaveAngleImpactNwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readWaveAngleImpact, GrassWaveImpactJsonInputDefinitions::WAVE_ANGLE_IMPACT_NWA)));

            locationData->SetWaveAngleImpactQwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readWaveAngleImpact, GrassWaveImpactJsonInputDefinitions::WAVE_ANGLE_IMPACT_QWA)));

            locationData->SetWaveAngleImpactRwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readWaveAngleImpact, GrassWaveImpactJsonInputDefinitions::WAVE_ANGLE_IMPACT_RWA)));
        }

        if (readCalculationMethod.contains(GrassWaveImpactJsonInputDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod[GrassWaveImpactJsonInputDefinitions::UPPER_LIMIT_LOADING];

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalValue(
                    readUpperLimitLoading, GrassWaveImpactJsonInputDefinitions::UPPER_LIMIT_LOADING_AUL)));
        }

        if (readCalculationMethod.contains(GrassWaveImpactJsonInputDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod[GrassWaveImpactJsonInputDefinitions::LOWER_LIMIT_LOADING];

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    JsonInputParserHelper::ParseOptionalValue(
                        readLowerLimitLoading, GrassWaveImpactJsonInputDefinitions::LOWER_LIMIT_LOADING_ALL)));
        }

        return locationData;
    }
}

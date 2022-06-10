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

#include "JsonInputGrassWaveImpactParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassRevetmentDefinitions.h"
#include "JsonInputGrassWaveImpactDefinitions.h"
#include "JsonInputGrassWaveImpactLocationData.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputGrassRevetmentTopLayerType,
        {
            {
                JsonInputGrassRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputGrassRevetmentTopLayerType::ClosedSod, JsonInputGrassRevetmentDefinitions::TOP_LAYER_TYPE_CLOSED_SOD
            },
            {
                JsonInputGrassRevetmentTopLayerType::OpenSod, JsonInputGrassRevetmentDefinitions::TOP_LAYER_TYPE_OPEN_SOD
            }
        });

    JsonInputGrassWaveImpactParser::JsonInputGrassWaveImpactParser(
        const json& readLocation,
        const json& readRevetment,
        const json& readCalculationMethod)
        : JsonInputLocationParser(readLocation, readRevetment, readCalculationMethod) {}

    unique_ptr<JsonInputLocationData> JsonInputGrassWaveImpactParser::ParseLocationData(
        double x,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<double> initialDamage)
    {
        return make_unique<JsonInputGrassWaveImpactLocationData>(x, move(damageData), ParseRevetmentLocationData());
    }

    unique_ptr<JsonInputGrassRevetmentWaveImpactLocationData> JsonInputGrassWaveImpactParser::ParseRevetmentLocationData() const
    {
        const auto& readRevetment = GetReadRevetment();
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto locationData = make_unique<JsonInputGrassRevetmentWaveImpactLocationData>(
            readRevetment.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>());

        locationData->SetTimeLineAgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveImpactDefinitions::TIME_LINE_AGWI)));
        locationData->SetTimeLineBgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveImpactDefinitions::TIME_LINE_BGWI)));
        locationData->SetTimeLineCgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveImpactDefinitions::TIME_LINE_CGWI)));

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT))
        {
            const auto& readMinimumWaveHeight = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT);

            locationData->SetMinimumWaveHeightTemax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readMinimumWaveHeight, JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT_TEMAX)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT))
        {
            const auto& readMaximumWaveHeight = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT);

            locationData->SetMaximumWaveHeightTemin(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readMaximumWaveHeight, JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT_TEMIN)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT);

            locationData->SetWaveAngleImpactNwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_NWA)));

            locationData->SetWaveAngleImpactQwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_QWA)));

            locationData->SetWaveAngleImpactRwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_RWA)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING);

            locationData->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING_AUL)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING);

            locationData->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING_ALL)));
        }

        return locationData;
    }
}

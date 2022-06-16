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

#include "JsonInputGrassWaveImpactCalculationDefinitionParser.h"

#include "JsonInputGrassWaveImpactCalculationDefinitionData.h"
#include "JsonInputGrassWaveImpactDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputGrassWaveImpactCalculationDefinitionParser::JsonInputGrassWaveImpactCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputGrassWaveImpactCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputGrassWaveImpactCalculationDefinitionData>(
            move(failureNumber));

        calculationDefinition->SetTimeLineAgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputGrassWaveImpactDefinitions::TIME_LINE_AGWI)));
        calculationDefinition->SetTimeLineBgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputGrassWaveImpactDefinitions::TIME_LINE_BGWI)));
        calculationDefinition->SetTimeLineCgwi(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputGrassWaveImpactDefinitions::TIME_LINE_CGWI)));

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT))
        {
            const auto& readMinimumWaveHeight = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT);

            calculationDefinition->SetMinimumWaveHeightTemax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readMinimumWaveHeight, JsonInputGrassWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT_TEMAX)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT))
        {
            const auto& readMaximumWaveHeight = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT);

            calculationDefinition->SetMaximumWaveHeightTemin(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readMaximumWaveHeight, JsonInputGrassWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT_TEMIN)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactNwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_NWA)));

            calculationDefinition->SetWaveAngleImpactQwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_QWA)));

            calculationDefinition->SetWaveAngleImpactRwa(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveImpactDefinitions::WAVE_ANGLE_IMPACT_RWA)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING);

            calculationDefinition->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputGrassWaveImpactDefinitions::UPPER_LIMIT_LOADING_AUL)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod.at(JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING);

            calculationDefinition->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputGrassWaveImpactDefinitions::LOWER_LIMIT_LOADING_ALL)));
        }

        return calculationDefinition;
    }
}

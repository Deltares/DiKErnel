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

#include "JsonInputNaturalStoneCalculationDefinitionParser.h"

#include "JsonInputNaturalStoneCalculationDefinitionData.h"
#include "JsonInputNaturalStoneDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputNaturalStoneCalculationDefinitionParser::JsonInputNaturalStoneCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputNaturalStoneCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputNaturalStoneCalculationDefinitionData>(move(failureNumber));

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD))
        {
            const auto& readHydraulicLoads = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD);

            calculationDefinition->SetHydraulicLoadAp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AP)));
            calculationDefinition->SetHydraulicLoadBp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BP)));
            calculationDefinition->SetHydraulicLoadCp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CP)));
            calculationDefinition->SetHydraulicLoadNp(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NP)));
            calculationDefinition->SetHydraulicLoadAs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_AS)));
            calculationDefinition->SetHydraulicLoadBs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_BS)));
            calculationDefinition->SetHydraulicLoadCs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_CS)));
            calculationDefinition->SetHydraulicLoadNs(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_NS)));
            calculationDefinition->SetHydraulicLoadXib(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readHydraulicLoads, JsonInputNaturalStoneDefinitions::HYDRAULIC_LOAD_XIB)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL))
        {
            const auto& readSlopeUpperLevel = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL);

            calculationDefinition->SetSlopeUpperLevelAus(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlopeUpperLevel, JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL_AUS)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL))
        {
            const auto& readSlopeLowerLevel = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL);

            calculationDefinition->SetSlopeLowerLevelAls(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlopeLowerLevel, JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL_ALS)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING))
        {
            const auto& readUpperLimitLoading = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING);

            calculationDefinition->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_AUL)));
            calculationDefinition->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_BUL)));
            calculationDefinition->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readUpperLimitLoading, JsonInputNaturalStoneDefinitions::UPPER_LIMIT_LOADING_CUL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING))
        {
            const auto& readLowerLimitLoading = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING);

            calculationDefinition->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_ALL)));
            calculationDefinition->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_BLL)));
            calculationDefinition->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readLowerLimitLoading, JsonInputNaturalStoneDefinitions::LOWER_LIMIT_LOADING_CLL)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION);

            calculationDefinition->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX)));
            calculationDefinition->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT);

            calculationDefinition->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI)));
            calculationDefinition->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }

        return calculationDefinition;
    }
}

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

#include "JsonInputDefinitions.h"
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

        auto calculationDefinition = make_unique<JsonInputNaturalStoneCalculationDefinitionData>(
            move(failureNumber), ReadTopLayerDefinitionData(readCalculationMethod));

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::SLOPE))
        {
            const auto& readSlope = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::SLOPE);

            calculationDefinition->SetSlopeUpperLevel(
                JsonInputParserHelper::ParseOptionalDouble(readSlope, JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL));
            calculationDefinition->SetSlopeLowerLevel(
                JsonInputParserHelper::ParseOptionalDouble(readSlope, JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::LOADING_AREA))
        {
            const auto& readLoadingArea = readCalculationMethod.at(JsonInputDefinitions::LOADING_AREA);

            if (readLoadingArea.contains(JsonInputDefinitions::UPPER_LIMIT))
            {
                const auto& readUpperLimitLoading = readLoadingArea.at(JsonInputDefinitions::UPPER_LIMIT);

                calculationDefinition->SetUpperLimitLoadingA(
                    JsonInputParserHelper::ParseOptionalDouble(readUpperLimitLoading, JsonInputDefinitions::A_COEFFICIENT));
                calculationDefinition->SetUpperLimitLoadingB(
                    JsonInputParserHelper::ParseOptionalDouble(readUpperLimitLoading, JsonInputDefinitions::B_COEFFICIENT));
                calculationDefinition->SetUpperLimitLoadingC(
                    JsonInputParserHelper::ParseOptionalDouble(readUpperLimitLoading, JsonInputDefinitions::C_COEFFICIENT));
            }

            if (readLoadingArea.contains(JsonInputDefinitions::LOWER_LIMIT))
            {
                const auto& readLowerLimitLoading = readLoadingArea.at(JsonInputDefinitions::LOWER_LIMIT);

                calculationDefinition->SetLowerLimitLoadingA(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoading, JsonInputDefinitions::A_COEFFICIENT));
                calculationDefinition->SetLowerLimitLoadingB(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoading, JsonInputDefinitions::B_COEFFICIENT));
                calculationDefinition->SetLowerLimitLoadingC(
                    JsonInputParserHelper::ParseOptionalDouble(readLowerLimitLoading, JsonInputDefinitions::C_COEFFICIENT));
            }
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION);

            calculationDefinition->SetDistanceMaximumWaveElevationA(
                JsonInputParserHelper::ParseOptionalDouble(readDistanceMaxWaveElevation, JsonInputDefinitions::A_COEFFICIENT));
            calculationDefinition->SetDistanceMaximumWaveElevationB(
                JsonInputParserHelper::ParseOptionalDouble(readDistanceMaxWaveElevation, JsonInputDefinitions::B_COEFFICIENT));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT);

            calculationDefinition->SetNormativeWidthOfWaveImpactA(
                JsonInputParserHelper::ParseOptionalDouble(readNormativeWidthOfWaveImpact, JsonInputDefinitions::A_COEFFICIENT));
            calculationDefinition->SetNormativeWidthOfWaveImpactB(
                JsonInputParserHelper::ParseOptionalDouble(readNormativeWidthOfWaveImpact, JsonInputDefinitions::B_COEFFICIENT));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactBetaMax(
                JsonInputParserHelper::ParseOptionalDouble(readWaveAngleImpact, JsonInputDefinitions::BETA_MAX));
        }

        return calculationDefinition;
    }

    map<JsonInputNaturalStoneRevetmentTopLayerType, unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>
    JsonInputNaturalStoneCalculationDefinitionParser::ReadTopLayerDefinitionData(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputNaturalStoneRevetmentTopLayerType, unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            for (const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS); const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputNaturalStoneTopLayerDefinitionData>();

                ReadTopLayerStability(readTopLayer, *topLayer);

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputNaturalStoneRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }

    void JsonInputNaturalStoneCalculationDefinitionParser::ReadTopLayerStability(
        const json& readTopLayer,
        JsonInputNaturalStoneTopLayerDefinitionData& topLayer)
    {
        if (readTopLayer.contains(JsonInputNaturalStoneDefinitions::STABILITY))
        {
            const auto& readStability = readTopLayer.at(JsonInputNaturalStoneDefinitions::STABILITY);

            if (readStability.contains(JsonInputNaturalStoneDefinitions::STABILITY_PLUNGING))
            {
                const auto& readPlunging = readStability.at(JsonInputNaturalStoneDefinitions::STABILITY_PLUNGING);

                topLayer.SetStabilityPlungingA(
                    JsonInputParserHelper::ParseOptionalDouble(readPlunging, JsonInputDefinitions::A_COEFFICIENT));
                topLayer.SetStabilityPlungingB(
                    JsonInputParserHelper::ParseOptionalDouble(readPlunging, JsonInputDefinitions::B_COEFFICIENT));
                topLayer.SetStabilityPlungingC(
                    JsonInputParserHelper::ParseOptionalDouble(readPlunging, JsonInputDefinitions::C_COEFFICIENT));
                topLayer.SetStabilityPlungingN(
                    JsonInputParserHelper::ParseOptionalDouble(readPlunging, JsonInputNaturalStoneDefinitions::N_COEFFICIENT));
            }

            if (readStability.contains(JsonInputNaturalStoneDefinitions::STABILITY_SURGING))
            {
                const auto& readSurging = readStability.at(JsonInputNaturalStoneDefinitions::STABILITY_SURGING);

                topLayer.SetStabilitySurgingA(
                    JsonInputParserHelper::ParseOptionalDouble(readSurging, JsonInputDefinitions::A_COEFFICIENT));
                topLayer.SetStabilitySurgingB(
                    JsonInputParserHelper::ParseOptionalDouble(readSurging, JsonInputDefinitions::B_COEFFICIENT));
                topLayer.SetStabilitySurgingC(
                    JsonInputParserHelper::ParseOptionalDouble(readSurging, JsonInputDefinitions::C_COEFFICIENT));
                topLayer.SetStabilitySurgingN(
                    JsonInputParserHelper::ParseOptionalDouble(readSurging, JsonInputNaturalStoneDefinitions::N_COEFFICIENT));
            }

            topLayer.SetStabilityXib(
                JsonInputParserHelper::ParseOptionalDouble(readStability, JsonInputNaturalStoneDefinitions::XIB_COEFFICIENT));
        }
    }
}

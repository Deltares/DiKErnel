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

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputNaturalStoneRevetmentTopLayerType,
        {
            {
                JsonInputNaturalStoneRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputNaturalStoneRevetmentTopLayerType::NordicStone, JsonInputNaturalStoneDefinitions::TOP_LAYER_TYPE_NORDIC_STONE
            }
        });

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
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlope, JsonInputNaturalStoneDefinitions::SLOPE_UPPER_LEVEL)));
            calculationDefinition->SetSlopeLowerLevel(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readSlope, JsonInputNaturalStoneDefinitions::SLOPE_LOWER_LEVEL)));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::LOADING_AREA))
        {
            const auto& readLoadingArea = readCalculationMethod.at(JsonInputDefinitions::LOADING_AREA);

            if (readLoadingArea.contains(JsonInputDefinitions::UPPER_LIMIT))
            {
                const auto& readUpperLimitLoading = readLoadingArea.at(JsonInputDefinitions::UPPER_LIMIT);

                calculationDefinition->SetUpperLimitLoadingA(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readUpperLimitLoading, JsonInputDefinitions::A_COEFFICIENT)));
                calculationDefinition->SetUpperLimitLoadingB(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readUpperLimitLoading, JsonInputDefinitions::B_COEFFICIENT)));
                calculationDefinition->SetUpperLimitLoadingC(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readUpperLimitLoading, JsonInputDefinitions::C_COEFFICIENT)));
            }

            if (readLoadingArea.contains(JsonInputDefinitions::LOWER_LIMIT))
            {
                const auto& readLowerLimitLoading = readLoadingArea.at(JsonInputDefinitions::LOWER_LIMIT);

                calculationDefinition->SetLowerLimitLoadingA(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readLowerLimitLoading, JsonInputDefinitions::A_COEFFICIENT)));
                calculationDefinition->SetLowerLimitLoadingB(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readLowerLimitLoading, JsonInputDefinitions::B_COEFFICIENT)));
                calculationDefinition->SetLowerLimitLoadingC(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readLowerLimitLoading, JsonInputDefinitions::C_COEFFICIENT)));
            }
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION))
        {
            const auto& readDistanceMaxWaveElevation = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION);

            calculationDefinition->SetDistanceMaximumWaveElevationA(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputDefinitions::A_COEFFICIENT)));
            calculationDefinition->SetDistanceMaximumWaveElevationB(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readDistanceMaxWaveElevation, JsonInputDefinitions::B_COEFFICIENT)));
        }

        if (readCalculationMethod.contains(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
        {
            const auto& readNormativeWidthOfWaveImpact = readCalculationMethod.at(JsonInputNaturalStoneDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT);

            calculationDefinition->SetNormativeWidthOfWaveImpactA(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputDefinitions::A_COEFFICIENT)));
            calculationDefinition->SetNormativeWidthOfWaveImpactB(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readNormativeWidthOfWaveImpact, JsonInputDefinitions::B_COEFFICIENT)));
        }

        calculationDefinition->SetWaveAngleImpactBetaMax(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readCalculationMethod, JsonInputNaturalStoneDefinitions::WAVE_ANGLE_IMPACT_BETA_MAX)));

        return calculationDefinition;
    }

    map<JsonInputNaturalStoneRevetmentTopLayerType, unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>
    JsonInputNaturalStoneCalculationDefinitionParser::ReadTopLayerDefinitionData(
        const json& readCalculationMethod)
    {
        auto topLayers = map<JsonInputNaturalStoneRevetmentTopLayerType, unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>();

        if (readCalculationMethod.contains(JsonInputDefinitions::TOP_LAYERS))
        {
            const auto& readTopLayers = readCalculationMethod.at(JsonInputDefinitions::TOP_LAYERS);

            for (const auto& readTopLayer : readTopLayers)
            {
                auto topLayer = make_unique<JsonInputNaturalStoneTopLayerDefinitionData>();

                if (readTopLayer.contains(JsonInputNaturalStoneDefinitions::STABILITY))
                {
                    const auto& readStability = readTopLayer.at(JsonInputNaturalStoneDefinitions::STABILITY);

                    if (readStability.contains(JsonInputNaturalStoneDefinitions::STABILITY_PLUNGING))
                    {
                        const auto& readPlunging = readStability.at(JsonInputNaturalStoneDefinitions::STABILITY_PLUNGING);

                        topLayer->SetStabilityPlungingA(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readPlunging, JsonInputDefinitions::A_COEFFICIENT)));
                        topLayer->SetStabilityPlungingB(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readPlunging, JsonInputDefinitions::B_COEFFICIENT)));
                        topLayer->SetStabilityPlungingC(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readPlunging, JsonInputDefinitions::C_COEFFICIENT)));
                        topLayer->SetStabilityPlungingN(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readPlunging, JsonInputNaturalStoneDefinitions::N_COEFFICIENT)));
                    }

                    if (readStability.contains(JsonInputNaturalStoneDefinitions::STABILITY_SURGING))
                    {
                        const auto& readSurging = readStability.at(JsonInputNaturalStoneDefinitions::STABILITY_SURGING);

                        topLayer->SetStabilitySurgingA(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readSurging, JsonInputDefinitions::A_COEFFICIENT)));
                        topLayer->SetStabilitySurgingB(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readSurging, JsonInputDefinitions::B_COEFFICIENT)));
                        topLayer->SetStabilitySurgingC(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readSurging, JsonInputDefinitions::C_COEFFICIENT)));
                        topLayer->SetStabilitySurgingN(
                            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                                readSurging, JsonInputNaturalStoneDefinitions::N_COEFFICIENT)));
                    }

                    topLayer->SetStabilityXib(
                        forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                            readStability, JsonInputNaturalStoneDefinitions::XIB_COEFFICIENT)));
                }

                topLayers.insert(pair(readTopLayer.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputNaturalStoneRevetmentTopLayerType>(),
                                      move(topLayer)));
            }
        }

        return topLayers;
    }
}

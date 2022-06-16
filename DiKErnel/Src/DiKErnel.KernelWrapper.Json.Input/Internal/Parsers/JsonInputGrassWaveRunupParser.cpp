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

#include "JsonInputGrassWaveRunupParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassRevetmentDefinitions.h"
#include "JsonInputGrassWaveRunupDefinitions.h"
#include "JsonInputGrassWaveRunupLocationData.h"
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

    JsonInputGrassWaveRunupParser::JsonInputGrassWaveRunupParser(
        const json& readLocation,
        const json& readRevetment,
        const json& readCalculationMethod)
        : JsonInputLocationParser(readLocation, readRevetment, readCalculationMethod) {}

    unique_ptr<JsonInputLocationData> JsonInputGrassWaveRunupParser::ParseLocationData(
        double x,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<double> initialDamage)
    {
        const auto& readLocation = GetReadLocation();

        auto locationData = make_unique<JsonInputGrassWaveRunupLocationData>(
            x, move(initialDamage), readLocation.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>(),
            readLocation.at(JsonInputDefinitions::OUTER_SLOPE).get<double>());

        locationData->SetIncreasedLoadTransitionAlphaM(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readLocation, JsonInputGrassWaveRunupDefinitions::INCREASED_LOAD_TRANSITION_ALPHA_M)));
        locationData->SetReducedStrengthTransitionAlphaS(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readLocation, JsonInputGrassWaveRunupDefinitions::REDUCED_STRENGTH_TRANSITION_ALPHA_S)));

        locationData->SetRepresentativeWaveRunup2PGammab(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readLocation, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_B)));

        locationData->SetRepresentativeWaveRunup2PGammaf(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readLocation, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_F)));

        return locationData;
    }
}

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
#include "JsonInputGrassRevetmentWaveRunupCalculationProtocolType.h"
#include "JsonInputGrassWaveRunupDefinitions.h"
#include "JsonInputGrassWaveRunupRayleighDefinitions.h"
#include "JsonInputGrassWaveRunupRayleighLocationData.h"
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

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputGrassRevetmentWaveRunupCalculationProtocolType,
        {
            {
                JsonInputGrassRevetmentWaveRunupCalculationProtocolType::Unknown, nullptr
            },
            {
                JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete,
                JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE_RAYLEIGH_DISCRETE
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
        const auto& readCalculationMethod = GetReadCalculationMethod();
        const auto& readCalculationProtocol = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL);

        if (const auto& calculationProtocolType = readCalculationProtocol.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE)
                                                                         .get<JsonInputGrassRevetmentWaveRunupCalculationProtocolType>();
            calculationProtocolType != JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete)
        {
            return nullptr;
        }

        const auto& readLocation = GetReadLocation();

        auto locationData = make_unique<JsonInputGrassWaveRunupRayleighLocationData>(
            x, move(initialDamage), readLocation.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>(),
            readLocation.at(JsonInputDefinitions::OUTER_SLOPE).get<double>(), move(damageData),
            ParseRevetmentLocationData(readCalculationMethod, readCalculationProtocol));

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

    unique_ptr<JsonInputGrassWaveRunupRayleighCalculationDefinitionData> JsonInputGrassWaveRunupParser::ParseRevetmentLocationData(
        const json& readCalculationMethod,
        const json& readCalculationProtocol) const
    {
        const auto& readRevetment = GetReadRevetment();

        auto revetmentLocationData = ParseRayleighRevetmentLocationData(readCalculationProtocol);
        ParseGenericRevetmentLocationData(readRevetment, readCalculationMethod, *revetmentLocationData);

        return revetmentLocationData;
    }

    unique_ptr<JsonInputGrassWaveRunupRayleighCalculationDefinitionData> JsonInputGrassWaveRunupParser::ParseRayleighRevetmentLocationData(
        const json& readCalculationProtocol)
    {
        auto rayleighLocationData = make_unique<JsonInputGrassWaveRunupRayleighCalculationDefinitionData>();

        rayleighLocationData->SetFixedNumberOfWaves(
            forward<unique_ptr<int>>(JsonInputParserHelper::ParseOptionalInteger(
                readCalculationProtocol, JsonInputGrassWaveRunupRayleighDefinitions::FIXED_NUMBER_OF_WAVES)));

        if (readCalculationProtocol.contains(JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY))
        {
            const auto& readFrontVelocity = readCalculationProtocol.at(JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY);

            rayleighLocationData->SetFrontVelocityCu(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFrontVelocity, JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY_CU)));
        }

        return rayleighLocationData;
    }

    void JsonInputGrassWaveRunupParser::ParseGenericRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationMethod,
        JsonInputGrassWaveRunupCalculationDefinitionData& revetmentLocationData)
    {
        revetmentLocationData.SetCriticalCumulativeOverload(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::CRITICAL_CUMULATIVE_OVERLOAD)));
        revetmentLocationData.SetCriticalFrontVelocity(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::CRITICAL_FRONT_VELOCITY)));

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod.at(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES);

            revetmentLocationData.SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P))
        {
            const auto& readRepresentativeWaveRunup2P = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P);

            revetmentLocationData.SetRepresentativeWaveRunup2PAru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_ARU)));

            revetmentLocationData.SetRepresentativeWaveRunup2PBru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_BRU)));

            revetmentLocationData.SetRepresentativeWaveRunup2PCru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_CRU)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT);

            revetmentLocationData.SetWaveAngleImpactAbeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_ABETA)));

            revetmentLocationData.SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }
    }
}

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
        unique_ptr<JsonInputDamageData> damageData)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();
        const auto& readCalculationProtocol = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL);

        if (const auto& calculationProtocolType = readCalculationProtocol.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE)
                                                                         .get<JsonInputGrassRevetmentWaveRunupCalculationProtocolType>();
            calculationProtocolType != JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete)
        {
            return nullptr;
        }

        return make_unique<JsonInputGrassWaveRunupRayleighLocationData>(x, move(damageData),
                                                                        ParseRevetmentLocationData(readCalculationMethod, readCalculationProtocol),
                                                                        ParseProfileSchematizationData());
    }

    unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> JsonInputGrassWaveRunupParser::ParseRevetmentLocationData(
        const json& readCalculationMethod,
        const json& readCalculationProtocol) const
    {
        const auto& readRevetment = GetReadRevetment();

        auto locationData = ParseRayleighRevetmentLocationData(readRevetment, readCalculationProtocol);
        ParseGenericRevetmentLocationData(readRevetment, readCalculationMethod, *locationData);

        return locationData;
    }

    unique_ptr<JsonInputGrassRevetmentWaveRunupProfileSchematizationData> JsonInputGrassWaveRunupParser::ParseProfileSchematizationData() const
    {
        const auto& readProfileSchematization = GetReadLocation().at(JsonInputDefinitions::PROFILE_SCHEMATIZATION);

        auto profileSchematization = make_unique<JsonInputGrassRevetmentWaveRunupProfileSchematizationData>(
            readProfileSchematization.at(JsonInputDefinitions::OUTER_SLOPE).get<double>());

        profileSchematization->SetRepresentativeWaveRunup2PGammab(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readProfileSchematization, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_B)));

        profileSchematization->SetRepresentativeWaveRunup2PGammaf(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readProfileSchematization, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_F)));

        return profileSchematization;
    }

    unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> JsonInputGrassWaveRunupParser::ParseRayleighRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationProtocol)
    {
        auto rayleighLocationData = make_unique<JsonInputGrassRevetmentWaveRunupRayleighLocationData>(
            readRevetment.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputGrassRevetmentTopLayerType>());

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
        JsonInputGrassRevetmentWaveRunupLocationData& locationData)
    {
        locationData.SetCriticalCumulativeOverload(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::CRITICAL_CUMULATIVE_OVERLOAD)));
        locationData.SetCriticalFrontVelocity(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::CRITICAL_FRONT_VELOCITY)));
        locationData.SetIncreasedLoadTransitionAlphaM(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::INCREASED_LOAD_TRANSITION_ALPHA_M)));
        locationData.SetReducedStrengthTransitionAlphaS(
            forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                readRevetment, JsonInputGrassWaveRunupDefinitions::REDUCED_STRENGTH_TRANSITION_ALPHA_S)));

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod.at(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES);

            locationData.SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P))
        {
            const auto& readRepresentativeWaveRunup2P = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P);

            locationData.SetRepresentativeWaveRunup2PAru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_ARU)));

            locationData.SetRepresentativeWaveRunup2PBru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_BRU)));

            locationData.SetRepresentativeWaveRunup2PCru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_CRU)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT);

            locationData.SetWaveAngleImpactAbeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_ABETA)));

            locationData.SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }
    }
}

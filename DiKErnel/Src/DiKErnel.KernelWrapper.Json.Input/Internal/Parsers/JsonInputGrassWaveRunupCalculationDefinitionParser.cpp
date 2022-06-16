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

#include "JsonInputGrassWaveRunupCalculationDefinitionParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputGrassRevetmentWaveRunupCalculationProtocolType.h"
#include "JsonInputGrassWaveRunupCalculationDefinitionData.h"
#include "JsonInputGrassWaveRunupDefinitions.h"
#include "JsonInputGrassWaveRunupRayleighCalculationProtocolData.h"
#include "JsonInputGrassWaveRunupRayleighDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputGrassWaveRunupCalculationDefinitionParser::JsonInputGrassWaveRunupCalculationDefinitionParser(
        const json& readCalculationMethod)
        : JsonInputCalculationDefinitionParser(readCalculationMethod) { }

    unique_ptr<JsonInputCalculationDefinitionData> JsonInputGrassWaveRunupCalculationDefinitionParser::ParseCalculationDefinition(
        unique_ptr<double> failureNumber)
    {
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto calculationDefinition = make_unique<JsonInputGrassWaveRunupCalculationDefinitionData>(
            move(failureNumber), forward<unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData>>(
                ReadCalculationProtocolData(readCalculationMethod)));

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod.at(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES);

            calculationDefinition->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P))
        {
            const auto& readRepresentativeWaveRunup2P = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P);

            calculationDefinition->SetRepresentativeWaveRunup2PAru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_ARU)));

            calculationDefinition->SetRepresentativeWaveRunup2PBru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_BRU)));

            calculationDefinition->SetRepresentativeWaveRunup2PCru(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readRepresentativeWaveRunup2P, JsonInputGrassWaveRunupDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P_CRU)));
        }

        if (readCalculationMethod.contains(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT))
        {
            const auto& readWaveAngleImpact = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT);

            calculationDefinition->SetWaveAngleImpactAbeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_ABETA)));

            calculationDefinition->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readWaveAngleImpact, JsonInputGrassWaveRunupDefinitions::WAVE_ANGLE_IMPACT_BETAMAX)));
        }

        return calculationDefinition;
    }

    unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> ReadCalculationProtocolData(
        const json& readCalculationMethod)
    {
        const auto& readCalculationProtocol = readCalculationMethod.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL);

        if (const auto& calculationProtocolType = readCalculationProtocol.at(JsonInputGrassWaveRunupDefinitions::CALCULATION_PROTOCOL_TYPE)
                                                                         .get<JsonInputGrassRevetmentWaveRunupCalculationProtocolType>();
            calculationProtocolType == JsonInputGrassRevetmentWaveRunupCalculationProtocolType::RayleighDiscrete)
        {
            auto calculationProtocolData = make_unique<JsonInputGrassWaveRunupRayleighCalculationProtocolData>();

            calculationProtocolData->SetFixedNumberOfWaves(
                forward<unique_ptr<int>>(JsonInputParserHelper::ParseOptionalInteger(
                    readCalculationProtocol, JsonInputGrassWaveRunupRayleighDefinitions::FIXED_NUMBER_OF_WAVES)));

            if (readCalculationProtocol.contains(JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY))
            {
                const auto& readFrontVelocity = readCalculationProtocol.at(JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY);

                calculationProtocolData->SetFrontVelocityCu(
                    forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                        readFrontVelocity, JsonInputGrassWaveRunupRayleighDefinitions::FRONT_VELOCITY_CU)));
            }

            return calculationProtocolData;
        }

        return nullptr;
    }
}

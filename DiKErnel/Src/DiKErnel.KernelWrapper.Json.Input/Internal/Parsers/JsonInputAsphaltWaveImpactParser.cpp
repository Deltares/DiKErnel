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

#include "JsonInputAsphaltWaveImpactParser.h"

#include "JsonInputAsphaltWaveImpactDefinitions.h"
#include "JsonInputAsphaltWaveImpactLocationData.h"
#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    NLOHMANN_JSON_SERIALIZE_ENUM(JsonInputAsphaltRevetmentTopLayerType,
        {
            {
                JsonInputAsphaltRevetmentTopLayerType::Unknown, nullptr
            },
            {
                JsonInputAsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete,
                JsonInputAsphaltWaveImpactDefinitions::TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE
            }
        });

    JsonInputAsphaltWaveImpactParser::JsonInputAsphaltWaveImpactParser(
        const json& readLocation,
        const json& readRevetment,
        const json& readCalculationMethod)
        : JsonInputLocationParser(readLocation, readRevetment, readCalculationMethod) {}

    unique_ptr<JsonInputLocationData> JsonInputAsphaltWaveImpactParser::ParseLocationData(
        double x,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<double> initialDamage)
    {
        const auto& readLocation = GetReadLocation();

        const auto& readUpperLayer = readLocation.at(JsonInputAsphaltWaveImpactDefinitions::UPPER_LAYER);

        auto locationData = make_unique<JsonInputAsphaltWaveImpactLocationData>(
            x, move(initialDamage), readLocation.at(JsonInputDefinitions::TYPE_TOP_LAYER).get<JsonInputAsphaltRevetmentTopLayerType>(),
            readLocation.at(JsonInputAsphaltWaveImpactDefinitions::FAILURE_TENSION).get<double>(),
            readLocation.at(JsonInputAsphaltWaveImpactDefinitions::SOIL_ELASTICITY).get<double>(),
            readUpperLayer.at(JsonInputAsphaltWaveImpactDefinitions::THICKNESS).get<double>(),
            readUpperLayer.at(JsonInputAsphaltWaveImpactDefinitions::ELASTIC_MODULUS).get<double>(),
            readLocation.at(JsonInputDefinitions::OUTER_SLOPE).get<double>(),
            move(damageData), ParseRevetmentLocationData());

        if (readLocation.contains(JsonInputAsphaltWaveImpactDefinitions::SUB_LAYER))
        {
            const auto& readSubLayer = readLocation.at(JsonInputAsphaltWaveImpactDefinitions::SUB_LAYER);

            locationData->SetThicknessSubLayer(make_unique<double>(readSubLayer.at(JsonInputAsphaltWaveImpactDefinitions::THICKNESS)));
            locationData->SetElasticModulusSubLayer(make_unique<double>(readSubLayer.at(JsonInputAsphaltWaveImpactDefinitions::ELASTIC_MODULUS)));
        }

        return locationData;
    }

    unique_ptr<JsonInputAsphaltWaveImpactCalculationDefinitionData> JsonInputAsphaltWaveImpactParser::ParseRevetmentLocationData() const
    {
        const auto& readRevetment = GetReadRevetment();
        const auto& readCalculationMethod = GetReadCalculationMethod();

        auto revetmentLocationData = make_unique<JsonInputAsphaltWaveImpactCalculationDefinitionData>(nullptr,
            readRevetment.at(JsonInputAsphaltWaveImpactDefinitions::DENSITY_OF_WATER).get<double>());

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod.at(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES);

            revetmentLocationData->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::FATIGUE))
        {
            const auto& readFatigue = readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::FATIGUE);

            revetmentLocationData->SetFatigueAlpha(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_ALPHA)));
            revetmentLocationData->SetFatigueBeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_BETA)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER))
        {
            const auto& readImpactNumber = readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER);

            revetmentLocationData->SetImpactNumberC(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readImpactNumber, JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER_C)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION))
        {
            const auto& readStiffnessRelation = readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION);

            revetmentLocationData->SetStiffnessRelationNu(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readStiffnessRelation, JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION_NU)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS))
        {
            revetmentLocationData->SetWidthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS))));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS))
        {
            revetmentLocationData->SetDepthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS))));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS))
        {
            revetmentLocationData->SetImpactFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod.at(JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS))));
        }

        return revetmentLocationData;
    }

    unique_ptr<vector<pair<double, double>>> JsonInputAsphaltWaveImpactParser::ParseFactorsTable(
        const json& factorsTable) const
    {
        auto readFactors = make_unique<vector<pair<double, double>>>();

        for (const auto& factor : factorsTable)
        {
            readFactors->push_back(factor.get<pair<double, double>>());
        }

        return readFactors;
    }
}

// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "JsonInputAsphaltLocationData.h"
#include "JsonInputAsphaltWaveImpactDefinitions.h"
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
        string name,
        double x,
        unique_ptr<JsonInputDamageData> damageData)
    {
        return make_unique<JsonInputAsphaltLocationData>(move(name), x, move(damageData), ParseRevetmentLocationData(),
                                                         ParseProfileSchematizationData());
    }

    unique_ptr<JsonInputAsphaltRevetmentWaveImpactLocationData> JsonInputAsphaltWaveImpactParser::ParseRevetmentLocationData() const
    {
        const auto& readRevetment = GetReadRevetment();
        const auto& readCalculationMethod = GetReadCalculationMethod();

        const auto& readUpperLayer = readRevetment[JsonInputAsphaltWaveImpactDefinitions::UPPER_LAYER];

        auto locationData = make_unique<JsonInputAsphaltRevetmentWaveImpactLocationData>(
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputAsphaltRevetmentTopLayerType>(),
            readRevetment[JsonInputAsphaltWaveImpactDefinitions::FAILURE_TENSION],
            readRevetment[JsonInputAsphaltWaveImpactDefinitions::DENSITY_OF_WATER],
            readRevetment[JsonInputAsphaltWaveImpactDefinitions::SOIL_ELASTICITY],
            readUpperLayer[JsonInputAsphaltWaveImpactDefinitions::THICKNESS],
            readUpperLayer[JsonInputAsphaltWaveImpactDefinitions::ELASTIC_MODULUS]);

        if (readRevetment.contains(JsonInputAsphaltWaveImpactDefinitions::SUB_LAYER))
        {
            const auto& readSubLayer = readRevetment[JsonInputAsphaltWaveImpactDefinitions::SUB_LAYER];

            locationData->SetThicknessSubLayer(make_unique<double>(readSubLayer[JsonInputAsphaltWaveImpactDefinitions::THICKNESS]));
            locationData->SetElasticModulusSubLayer(make_unique<double>(readSubLayer[JsonInputAsphaltWaveImpactDefinitions::ELASTIC_MODULUS]));
        }

        if (readCalculationMethod.contains(JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES))
        {
            const auto& readAverageNumberWaveTimeStep = readCalculationMethod[JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES];

            locationData->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readAverageNumberWaveTimeStep, JsonInputDefinitions::AVERAGE_NUMBER_OF_WAVES_CTM)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::FATIGUE))
        {
            const auto& readFatigue = readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::FATIGUE];

            locationData->SetFatigueAlpha(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_ALPHA)));
            locationData->SetFatigueBeta(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readFatigue, JsonInputAsphaltWaveImpactDefinitions::FATIGUE_BETA)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER))
        {
            const auto& readImpactNumber = readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER];

            locationData->SetImpactNumberC(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readImpactNumber, JsonInputAsphaltWaveImpactDefinitions::IMPACT_NUMBER_C)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION))
        {
            const auto& readStiffnessRelation = readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION];

            locationData->SetStiffnessRelationNu(
                forward<unique_ptr<double>>(JsonInputParserHelper::ParseOptionalDouble(
                    readStiffnessRelation, JsonInputAsphaltWaveImpactDefinitions::STIFFNESS_RELATION_NU)));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS))
        {
            locationData->SetWidthFactors(
                forward<unique_ptr<vector<tuple<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::WIDTH_FACTORS])));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS))
        {
            locationData->SetDepthFactors(
                forward<unique_ptr<vector<tuple<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::DEPTH_FACTORS])));
        }

        if (readCalculationMethod.contains(JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS))
        {
            locationData->SetImpactFactors(
                forward<unique_ptr<vector<tuple<double, double>>>>(
                    ParseFactorsTable(readCalculationMethod[JsonInputAsphaltWaveImpactDefinitions::IMPACT_FACTORS])));
        }

        return locationData;
    }

    unique_ptr<JsonInputProfileSchematizationData> JsonInputAsphaltWaveImpactParser::ParseProfileSchematizationData() const
    {
        const auto& readProfileSchematization = GetReadLocation()[JsonInputDefinitions::PROFILE_SCHEMATIZATION];

        return make_unique<JsonInputProfileSchematizationData>(
            readProfileSchematization[JsonInputDefinitions::OUTER_SLOPE].get<double>());
    }

    unique_ptr<vector<tuple<double, double>>> JsonInputAsphaltWaveImpactParser::ParseFactorsTable(
        const json& factorsTable) const
    {
        auto readFactors = make_unique<vector<tuple<double, double>>>();

        for (const auto& factor : factorsTable)
        {
            readFactors->push_back(factor.get<tuple<double, double>>());
        }

        return readFactors;
    }
}

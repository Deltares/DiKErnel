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

#include "JsonInputAsphaltParser.h"

#include "JsonInputAsphaltRevetmentDefinitions.h"
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
                JsonInputAsphaltRevetmentTopLayerType::WAB, JsonInputAsphaltRevetmentDefinitions::TOP_LAYER_TYPE_WAD
            }
        });

    unique_ptr<JsonInputAsphaltRevetmentLocationData> JsonInputAsphaltParser::ParseRevetmentLocationData(
        const json& readRevetment,
        const json& readCalculationMethod)
    {
        auto locationData = make_unique<JsonInputAsphaltRevetmentLocationData>(
            readRevetment[JsonInputDefinitions::TYPE_TOP_LAYER].get<JsonInputAsphaltRevetmentTopLayerType>(),
            readRevetment[JsonInputAsphaltRevetmentDefinitions::FAILURE_TENSION],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::DENSITY_OF_WATER],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::SOIL_ELASTICITY],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::THICKNESS_UPPER_LAYER],
            readRevetment[JsonInputAsphaltRevetmentDefinitions::ELASTIC_MODULUS_UPPER_LAYER]);

        return locationData;
    }
}

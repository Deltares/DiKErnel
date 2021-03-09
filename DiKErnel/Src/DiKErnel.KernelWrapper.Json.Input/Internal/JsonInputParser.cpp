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

#include "JsonInputParser.h"

#include <fstream>

#include "JsonInputDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    unique_ptr<JsonInputData> JsonInputParser::GetJsonInputData(
        const string& filePath)
    {
        const auto json = ReadJson(filePath);

        return make_unique<JsonInputData>(
            make_unique<JsonInputCalculationData>(
                GetTimes(json),
                GetHydraulicData(json),
                vector<unique_ptr<JsonInputLocationData>>()
            )
        );
    }

    json JsonInputParser::ReadJson(
        const string& filePath)
    {
        ifstream ifs(filePath);
        return json::parse(ifs);
    }

    vector<int> JsonInputParser::GetTimes(
        const json& json)
    {
        return json[JsonInputDefinitions::CALCULATION_DATA][JsonInputDefinitions::TIME].get<vector<int>>();
    }

    unique_ptr<JsonInputHydraulicData> JsonInputParser::GetHydraulicData(
        const json& json)
    {
        const auto& readHydraulicLoads = json[JsonInputDefinitions::HYDRAULIC_LOADS];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonInputDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP];

        vector<unique_ptr<JsonInputTimeDependentHydraulicData>> timeDependentHydraulicData;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            timeDependentHydraulicData.push_back(
                make_unique<JsonInputTimeDependentHydraulicData>(
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WATER_LEVEL].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_HEIGHT_HM0].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_PERIOD_TM10].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonInputDefinitions::WAVE_ANGLE].get<double>()
                ));
        }

        return make_unique<JsonInputHydraulicData>(
            readHydraulicLoads[JsonInputDefinitions::MAXIMUM_WAVE_ANGLE].get<double>(),
            move(timeDependentHydraulicData));
    }
}

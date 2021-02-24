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

#include "nlohmann/json.hpp"

#include <fstream>

#include "InputComposer.h"
#include "InputData.h"
#include "JsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    unique_ptr<InputData> InputComposer::GetDomainParametersFromJson(
        const string& filePath)
    {
        const auto json = ParseJson(filePath);

        return make_unique<InputData>(
            ReadCalculationData(json),
            ReadHydraulicLoads(json),
            ReadLocations(json));
    }

    unique_ptr<CalculationData> InputComposer::ReadCalculationData(
        const nlohmann::json& json)
    {
        const auto& readCalculationData = json[JsonDefinitions::CALCULATION_DATA];

        return make_unique<CalculationData>(
            readCalculationData[JsonDefinitions::TIME].get<vector<int>>()
        );
    }

    unique_ptr<HydraulicLoads> InputComposer::ReadHydraulicLoads(
        const nlohmann::json& json)
    {
        const auto& readHydraulicLoads = json[JsonDefinitions::HYDRAULIC_LOADS];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP];

        vector<unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            boundaryConditionsPerTimeStep.push_back(
                make_unique<BoundaryConditionsPerTimeStep>(
                    readBoundaryConditionsForTimeStep[JsonDefinitions::WAVE_HEIGHT_HM0].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::WAVE_PERIOD_TM10].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::WAVE_ANGLE].get<double>()
                ));
        }

        return make_unique<HydraulicLoads>(
            readHydraulicLoads[JsonDefinitions::MAXIMUM_WAVE_ANGLE].get<int>(),
            move(boundaryConditionsPerTimeStep)
        );
    }

    vector<unique_ptr<CalculationLocation>> InputComposer::ReadLocations(
        const nlohmann::json& json)
    {
        vector<unique_ptr<CalculationLocation>> calculationLocations;

        const auto& readLocations = json[JsonDefinitions::LOCATIONS];

        for (const auto& readLocation : readLocations)
        {
            const auto& readRevetment = readLocation[JsonDefinitions::REVETMENT];
            const auto& readDamageVariables = readLocation[JsonDefinitions::DAMAGE];
            const auto& readProfileSchematization = readLocation[JsonDefinitions::PROFILE_SCHEMATIZATION];

            calculationLocations.push_back(make_unique<CalculationLocation>(
                readLocation[JsonDefinitions::NAME].get<string>(),
                make_unique<DamageVariables>(
                    readDamageVariables[JsonDefinitions::INITIAL_DAMAGE].get<double>(),
                    readDamageVariables[JsonDefinitions::CRITICAL_DAMAGE].get<double>()),
                    make_unique<Revetment>(
                    readRevetment[JsonDefinitions::TYPE_TOP_LAYER].get<string>(),
                    readRevetment[JsonDefinitions::RELATIVE_DENSITY].get<double>(),
                    readRevetment[JsonDefinitions::THICKNESS_TOP_LAYER].get<double>(),
                    readRevetment[JsonDefinitions::SIMILARITY_PARAMETER_THRESHOLD].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_PLUNGING_AP].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_PLUNGING_BP].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_PLUNGING_CP].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_PLUNGING_NP].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_SURGING_AS].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_SURGING_BS].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_SURGING_CS].get<double>(),
                    readRevetment[JsonDefinitions::COEFFICIENT_SURGING_NS].get<double>()),
                make_unique<ProfileSchematization>(
                    readProfileSchematization[JsonDefinitions::TAN_A].get<double>()
                )
            ));
        }

        return calculationLocations;
    }

    nlohmann::json InputComposer::ParseJson(
        const string& filePath)
    {
        ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

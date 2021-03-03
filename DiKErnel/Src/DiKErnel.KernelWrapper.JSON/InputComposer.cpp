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

#include "InputComposer.h"

#include <fstream>

#include "Defaults.h"
#include "InputData.h"
#include "InputJsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace DomainLibrary;
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
        const auto& readCalculationData = json[InputJsonDefinitions::CALCULATION_DATA];

        return make_unique<CalculationData>(
            readCalculationData[InputJsonDefinitions::TIME].get<vector<int>>()
        );
    }

    unique_ptr<HydraulicLoads> InputComposer::ReadHydraulicLoads(
        const nlohmann::json& json)
    {
        const auto& readHydraulicLoads = json[InputJsonDefinitions::HYDRAULIC_LOADS];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[InputJsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP];

        vector<unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            boundaryConditionsPerTimeStep.push_back(
                make_unique<BoundaryConditionsPerTimeStep>(
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WATER_LEVEL].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_HEIGHT_HM0].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_PERIOD_TM10].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_ANGLE].get<double>()
                ));
        }

        return make_unique<HydraulicLoads>(
            readHydraulicLoads[InputJsonDefinitions::MAXIMUM_WAVE_ANGLE].get<int>(),
            move(boundaryConditionsPerTimeStep)
        );
    }

    vector<unique_ptr<CalculationLocation>> InputComposer::ReadLocations(
        const nlohmann::json& json)
    {
        vector<unique_ptr<CalculationLocation>> calculationLocations;

        const auto& readLocations = json[InputJsonDefinitions::LOCATIONS];

        for (const auto& readLocation : readLocations)
        {
            const auto& readRevetment = readLocation[InputJsonDefinitions::REVETMENT];
            const auto& readDamageVariables = readLocation[InputJsonDefinitions::DAMAGE];
            const auto& readProfileSchematization = readLocation[InputJsonDefinitions::PROFILE_SCHEMATIZATION];

            calculationLocations.push_back(make_unique<CalculationLocation>(
                readLocation[InputJsonDefinitions::NAME].get<string>(),
                make_unique<DamageVariables>(
                    readDamageVariables[InputJsonDefinitions::INITIAL_DAMAGE].get<double>(),
                    GetCriticalDamage(readDamageVariables)),
                make_unique<Revetment>(
                    readRevetment[InputJsonDefinitions::TYPE_TOP_LAYER].get<string>(),
                    readRevetment[InputJsonDefinitions::RELATIVE_DENSITY].get<double>(),
                    readRevetment[InputJsonDefinitions::THICKNESS_TOP_LAYER].get<double>(),
                    readRevetment[InputJsonDefinitions::SIMILARITY_PARAMETER_THRESHOLD].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_PLUNGING_AP].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_PLUNGING_BP].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_PLUNGING_CP].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_PLUNGING_NP].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_SURGING_AS].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_SURGING_BS].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_SURGING_CS].get<double>(),
                    readRevetment[InputJsonDefinitions::COEFFICIENT_SURGING_NS].get<double>()),
                make_unique<ProfileSchematization>(
                    readProfileSchematization[InputJsonDefinitions::TAN_A].get<double>(),
                    readProfileSchematization[InputJsonDefinitions::POSITION_Z].get<double>()
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

    double InputComposer::GetCriticalDamage(
        const nlohmann::basic_json<>::value_type& readDamageVariables)
    {
        if (readDamageVariables.contains(InputJsonDefinitions::CRITICAL_DAMAGE))
        {
            return readDamageVariables[InputJsonDefinitions::CRITICAL_DAMAGE].get<double>();
        }

        return Defaults::CRITICAL_DAMAGE;
    }
}

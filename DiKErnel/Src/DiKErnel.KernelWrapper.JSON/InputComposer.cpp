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
        const auto& readCalculationData = json[JsonDefinitions::calculationData];

        return make_unique<CalculationData>(
            readCalculationData[JsonDefinitions::time].get<vector<int>>()
        );
    }

    unique_ptr<HydraulicLoads> InputComposer::ReadHydraulicLoads(
        const nlohmann::json& json)
    {
        const auto& readHydraulicLoads = json[JsonDefinitions::hydraulicLoads];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::boundaryConditionsPerTimeStep];

        vector<unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            boundaryConditionsPerTimeStep.push_back(
                make_unique<BoundaryConditionsPerTimeStep>(
                    readBoundaryConditionsForTimeStep[JsonDefinitions::waveHeightHm0].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::wavePeriodTm10].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::waveAngle].get<double>()
                ));
        }

        return make_unique<HydraulicLoads>(
            readHydraulicLoads[JsonDefinitions::maximumWaveAngle].get<int>(),
            move(boundaryConditionsPerTimeStep)
        );
    }

    vector<unique_ptr<CalculationLocation>> InputComposer::ReadLocations(
        const nlohmann::json& json)
    {
        vector<unique_ptr<CalculationLocation>> calculationLocations;

        const auto& readLocations = json[JsonDefinitions::locations];

        for (const auto& readLocation : readLocations)
        {
            const auto& readRevetment = readLocation[JsonDefinitions::revetment];
            const auto& readProfileSchematization = readLocation[JsonDefinitions::profileSchematisation];

            calculationLocations.push_back(make_unique<CalculationLocation>(
                readLocation[JsonDefinitions::name].get<string>(),
                make_unique<Revetment>(
                    readRevetment[JsonDefinitions::typeTopLayer].get<string>(),
                    readRevetment[JsonDefinitions::relativeDensity].get<double>(),
                    readRevetment[JsonDefinitions::thicknessTopLayer].get<double>(),
                    readRevetment[JsonDefinitions::initialDamage].get<double>(),
                    readRevetment[JsonDefinitions::similarityParameterThreshold].get<double>(),
                    readRevetment[JsonDefinitions::coefficientPlungingAp].get<double>(),
                    readRevetment[JsonDefinitions::coefficientPlungingBp].get<double>(),
                    readRevetment[JsonDefinitions::coefficientPlungingCp].get<double>(),
                    readRevetment[JsonDefinitions::coefficientPlungingNp].get<double>(),
                    readRevetment[JsonDefinitions::coefficientSurgingAs].get<double>(),
                    readRevetment[JsonDefinitions::coefficientSurgingBs].get<double>(),
                    readRevetment[JsonDefinitions::coefficientSurgingCs].get<double>(),
                    readRevetment[JsonDefinitions::coefficientSurgingNs].get<double>()),
                make_unique<ProfileSchematization>(
                    readProfileSchematization[JsonDefinitions::tanA].get<double>()
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

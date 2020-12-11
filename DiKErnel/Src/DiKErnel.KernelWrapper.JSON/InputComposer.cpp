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

#include "InputData.h"
#include "JsonDefinitions.h"
#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    InputData* InputComposer::GetDomainParametersFromJson(
        const std::string& filePath)
    {
        auto json = ParseJson(filePath);

        return new InputData(
            ReadCalculationData(&json),
            ReadHydraulicLoads(&json),
            ReadLocations(&json));
    }

    CalculationData* InputComposer::ReadCalculationData(
        nlohmann::json* json)
    {
        auto readCalculationData = (*json)[JsonDefinitions::calculationData];

        return new CalculationData(
            readCalculationData[JsonDefinitions::time].get<std::vector<int>>()
        );
    }

    HydraulicLoads* InputComposer::ReadHydraulicLoads(
        nlohmann::json* json)
    {
        auto readHydraulicLoads = (*json)[JsonDefinitions::hydraulicLoads];
        auto readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::boundaryConditionsPerTimeStep];

        std::vector<BoundaryConditionsPerTimeStep*> boundaryConditionsPerTimeStep;

        for (auto i = 0; i < readBoundaryConditionsPerTimeStep.size(); i++)
        {
            auto readBoundaryConditionsForTimestep = readBoundaryConditionsPerTimeStep[i];

            boundaryConditionsPerTimeStep.push_back(new BoundaryConditionsPerTimeStep(
                readBoundaryConditionsForTimestep[JsonDefinitions::waveHeightHm0].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::wavePeriodTm10].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::waveAngle].get<double>()
            ));
        }

        return new HydraulicLoads(
            readHydraulicLoads[JsonDefinitions::maximumWaveAngle].get<int>(),
            boundaryConditionsPerTimeStep
        );
    }

    std::vector<CalculationLocation*> InputComposer::ReadLocations(
        nlohmann::json* json)
    {
        std::vector<CalculationLocation*> calculationLocations;

        auto readLocations = (*json)[JsonDefinitions::locations];

        for (auto i = 0; i < readLocations.size(); i++)
        {
            auto readLocation = readLocations[i];
            auto readRevetment = readLocation[JsonDefinitions::revetment];
            auto readProfileSchematization = readLocation[JsonDefinitions::profileSchematisation];

            calculationLocations.push_back(new CalculationLocation(
                readLocation[JsonDefinitions::name].get<std::string>(),
                new Revetment(
                    readRevetment[JsonDefinitions::typeTopLayer].get<std::string>(),
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
                new ProfileSchematization(
                    readProfileSchematization[JsonDefinitions::tanA].get<double>()
                )
            ));
        }

        return calculationLocations;
    }

    nlohmann::json InputComposer::ParseJson(
        const std::string& filePath)
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

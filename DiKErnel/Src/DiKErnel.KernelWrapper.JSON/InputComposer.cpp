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

        auto* inputData(new InputData());

        inputData->calculationData = ReadCalculationData(&json);

        inputData->hydraulicLoads = ReadHydraulicLoads(&json);

        inputData->locations = ReadLocations(&json);

        return inputData;
    }

    CalculationData InputComposer::ReadCalculationData(
        nlohmann::json* json)
    {
        CalculationData calculationData;
        calculationData.time = (*json)[JsonDefinitions::calculationData][JsonDefinitions::time].get<std::vector<int>>();

        return calculationData;
    }

    HydraulicLoads InputComposer::ReadHydraulicLoads(
        nlohmann::json* json)
    {
        std::vector<BoundaryConditionsPerTimeStep> boundaryConditionsPerTimeStep;

        auto readHydraulicLoads = (*json)[JsonDefinitions::hydraulicLoads];
        auto readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::boundaryConditionsPerTimeStep];

        for (auto i = 0; i < readBoundaryConditionsPerTimeStep.size(); i++)
        {
            auto readBoundaryConditionsForTimestep = readBoundaryConditionsPerTimeStep[i];

            boundaryConditionsPerTimeStep.push_back(BoundaryConditionsPerTimeStep(
                readBoundaryConditionsForTimestep[JsonDefinitions::waveHeightHm0].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::wavePeriodTm10].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::waveAngle].get<double>()
            ));
        }

        return HydraulicLoads(
            readHydraulicLoads[JsonDefinitions::maximumWaveAngle].get<int>(),
            boundaryConditionsPerTimeStep
        );
    }

    std::vector<CalculationLocation> InputComposer::ReadLocations(
        nlohmann::json* json)
    {
        std::vector<CalculationLocation> calculationLocations;

        auto readLocations = (*json)[JsonDefinitions::locations];

        for (auto i = 0; i < readLocations.size(); i++)
        {
            auto readLocation = readLocations[i];
            auto readRevetment = readLocation[JsonDefinitions::revetment];
            auto readProfileSchematization = readLocation[JsonDefinitions::profileSchematisation];

            Revetment revetment;
            revetment.typeTopLayer = readRevetment[JsonDefinitions::typeTopLayer].get<std::string>();
            revetment.relativeDensity = readRevetment[JsonDefinitions::relativeDensity].get<double>();
            revetment.thicknessTopLayer = readRevetment[JsonDefinitions::thicknessTopLayer].get<double>();
            revetment.initialDamage = readRevetment[JsonDefinitions::initialDamage].get<double>();
            revetment.similarityParameterThreshold = readRevetment[JsonDefinitions::similarityParameterThreshold].get<double>();
            revetment.coefficientPlungingAp = readRevetment[JsonDefinitions::coefficientPlungingAp].get<double>();
            revetment.coefficientPlungingBp = readRevetment[JsonDefinitions::coefficientPlungingBp].get<double>();
            revetment.coefficientPlungingCp = readRevetment[JsonDefinitions::coefficientPlungingCp].get<double>();
            revetment.coefficientPlungingNp = readRevetment[JsonDefinitions::coefficientPlungingNp].get<double>();
            revetment.coefficientSurgingAs = readRevetment[JsonDefinitions::coefficientSurgingAs].get<double>();
            revetment.coefficientSurgingBs = readRevetment[JsonDefinitions::coefficientSurgingBs].get<double>();
            revetment.coefficientSurgingCs = readRevetment[JsonDefinitions::coefficientSurgingCs].get<double>();
            revetment.coefficientSurgingNs = readRevetment[JsonDefinitions::coefficientSurgingNs].get<double>();

            ProfileSchematization profileSchematization;
            profileSchematization.tanA = readProfileSchematization[JsonDefinitions::tanA].get<double>();

            calculationLocations.push_back(CalculationLocation(
                readLocation[JsonDefinitions::name].get<std::string>(),
                revetment,
                profileSchematization
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

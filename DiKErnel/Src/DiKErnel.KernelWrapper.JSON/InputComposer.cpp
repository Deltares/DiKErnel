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

#include <fstream>

#include "nlohmann/json.hpp"

#include "InputComposer.h"
#include "InputData.h"
#include "JsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    std::unique_ptr<InputData> InputComposer::GetDomainParametersFromJson(
        const std::string& filePath)
    {
        const auto json = ParseJson(filePath);

        return std::make_unique<InputData>(
            ReadCalculationData(json),
            ReadHydraulicLoads(json),
            ReadLocations(json));
    }

    std::unique_ptr<CalculationData> InputComposer::ReadCalculationData(
        const nlohmann::json& json)
    {
        auto readCalculationData = json[JsonDefinitions::calculationData];

        return std::make_unique<CalculationData>(
            readCalculationData[JsonDefinitions::time].get<std::vector<int>>()
        );
    }

    std::unique_ptr<HydraulicLoads> InputComposer::ReadHydraulicLoads(
        const nlohmann::json& json)
    {
        auto readHydraulicLoads = json[JsonDefinitions::hydraulicLoads];
        auto readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::boundaryConditionsPerTimeStep];

        std::vector<std::unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep;

        for (auto readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            boundaryConditionsPerTimeStep.push_back(
                std::make_unique<BoundaryConditionsPerTimeStep>(
                    readBoundaryConditionsForTimeStep[JsonDefinitions::waveHeightHm0].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::wavePeriodTm10].get<double>(),
                    readBoundaryConditionsForTimeStep[JsonDefinitions::waveAngle].get<double>()
                ));
        }

        return std::make_unique<HydraulicLoads>(
            readHydraulicLoads[JsonDefinitions::maximumWaveAngle].get<int>(),
            std::move(boundaryConditionsPerTimeStep)
        );
    }

    std::vector<std::unique_ptr<CalculationLocation>> InputComposer::ReadLocations(
        const nlohmann::json& json)
    {
        std::vector<std::unique_ptr<CalculationLocation>> calculationLocations;

        auto readLocations = json[JsonDefinitions::locations];

        for (auto readLocation : readLocations)
        {
            auto readRevetment = readLocation[JsonDefinitions::revetment];
            auto readProfileSchematization = readLocation[JsonDefinitions::profileSchematisation];

            calculationLocations.push_back(std::make_unique<CalculationLocation>(
                readLocation[JsonDefinitions::name].get<std::string>(),
                std::make_unique<Revetment>(
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
                std::make_unique<ProfileSchematization>(
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

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
        auto readHydraulicLoads = (*json)[JsonDefinitions::hydraulicLoads];

        HydraulicLoads hydraulicLoads;
        hydraulicLoads.waveAngleMaximum = readHydraulicLoads[JsonDefinitions::maximumWaveAngle].get<int>();

        auto readBoundaryConditionsPerTimeStep = readHydraulicLoads[JsonDefinitions::boundaryConditionsPerTimeStep];

        for (auto i = 0; i < readBoundaryConditionsPerTimeStep.size(); i++)
        {
            auto readBoundaryConditionsForTimestep = readBoundaryConditionsPerTimeStep[i];

            hydraulicLoads.boundaryConditionsPerTimeStep.push_back(BoundaryConditionsPerTimeStep(
                readBoundaryConditionsForTimestep[JsonDefinitions::waveHeightHm0].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::wavePeriodTm10].get<double>(),
                readBoundaryConditionsForTimestep[JsonDefinitions::waveAngle].get<double>()
            ));
        }

        return hydraulicLoads;
    }

    std::vector<CalculationLocation> InputComposer::ReadLocations(
        nlohmann::json* json)
    {
        std::vector<CalculationLocation> calculationLocations;

        const auto arraySize = (*json)[JsonDefinitions::locations].size();

        for (auto i = 0; i < arraySize; i++)
        {
            CalculationLocation location;
            calculationLocations.push_back(location);

            calculationLocations.at(i).name = (*json)[JsonDefinitions::locations][i][JsonDefinitions::name].get<std::string>();

            calculationLocations.at(i).revetment.typeTopLayer = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::typeTopLayer].get<std::string>();
            calculationLocations.at(i).revetment.relativeDensity = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::relativeDensity].get<double>();
            calculationLocations.at(i).revetment.thicknessTopLayer = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::thicknessTopLayer].get<double>();
            calculationLocations.at(i).revetment.initialDamage = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::initialDamage].get<double>();
            calculationLocations.at(i).revetment.similarityParameterThreshold =
                    (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment][JsonDefinitions::similarityParameterThreshold].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingAp = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientPlungingAp].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingBp = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientPlungingBp].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingCp = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientPlungingCp].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingNp = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientPlungingNp].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingAs = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientSurgingAs].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingBs = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientSurgingBs].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingCs = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientSurgingCs].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingNs = (*json)[JsonDefinitions::locations][i][JsonDefinitions::revetment]
                    [JsonDefinitions::coefficientSurgingNs].get<double>();
            calculationLocations.at(i).profileSchematization.tanA = (*json)[JsonDefinitions::locations][i][JsonDefinitions::profileSchematisation]
                    [JsonDefinitions::tanA].get<double>();
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

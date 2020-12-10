#include "InputComposer.h"

#include <fstream>

#include "InputData.h"
#include "JsonDefinitions.h"
#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    InputData InputComposer::GetDomainParametersFromJson(
        const std::string& filePath)
    {
        auto json = ParseJson(filePath);

        InputData inputData;

        inputData.calculationData = ReadCalculationData(&json);

        inputData.hydraulicLoads = ReadHydraulicLoads(&json);

        inputData.locations = ReadLocations(&json);

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
        HydraulicLoads hydraulicLoads;

        hydraulicLoads.waveAngleMaximum = (*json)[JsonDefinitions::hydraulicLoads][JsonDefinitions::maximumWaveAngle].get<int>();

        const auto arraySize = (*json)[JsonDefinitions::hydraulicLoads][JsonDefinitions::boundaryConditionsPerTimeStep].size();

        for (auto i = 0; i < arraySize; i++)
        {
            BoundaryConditionsPerTimeStep boundaryConditionsPerTimeStep;
            hydraulicLoads.boundaryConditionsPerTimeStep.push_back(boundaryConditionsPerTimeStep);
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveHeightHm0 =
                (*json)[JsonDefinitions::hydraulicLoads][JsonDefinitions::boundaryConditionsPerTimeStep][i][JsonDefinitions::waveHeightHm0]
                    .get<double>();
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).wavePeriodTm10 =
                (*json)[JsonDefinitions::hydraulicLoads][JsonDefinitions::boundaryConditionsPerTimeStep][i][JsonDefinitions::wavePeriodTm10]
                    .get<double>();
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveAngle =
                (*json)[JsonDefinitions::hydraulicLoads][JsonDefinitions::boundaryConditionsPerTimeStep][i][JsonDefinitions::waveAngle]
                    .get<double>();
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

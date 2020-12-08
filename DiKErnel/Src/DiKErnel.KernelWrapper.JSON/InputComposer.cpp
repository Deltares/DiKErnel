#include "InputComposer.h"

#include <fstream>

#include "InputData.h"
#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    void InputComposer::GetDomainParametersFromJson(const std::string filePath) const
    {
        auto json = ParseJson(filePath);

        InputData inputData;

        ReadCalculationData(json, inputData);

        ReadHydraulicLoads(json, inputData);

        ReadLocations(json, inputData);
    }

    void InputComposer::ReadCalculationData(nlohmann::json json, InputData& inputData)
    {
        inputData.calculationData.time = json["Rekendata"]["Tijd"].get<std::vector<int>>();
    }

    void InputComposer::ReadHydraulicLoads(nlohmann::json json, InputData& inputData)
    {
        inputData.hydraulicLoads.waveAngleMaximum = json["HydraulischeBelastingen"]["GolfhoekMaximum"].get<int>();

        const auto arraySize = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"].size();

        for (auto i = 0; i < arraySize; i++)
        {
            BoundaryConditionsPerTimeStep boundaryConditionsPerTimeStep;
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep.push_back(boundaryConditionsPerTimeStep);
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveHeightHm0 = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfhoogteHm0"].get<double>();
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep.at(i).wavePeriodTm10 = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfperiodeTm10"].get<double>();
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveAngle = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["Golfhoek"].get<double>();
        }
    }

    void InputComposer::ReadLocations(nlohmann::json json, InputData& inputData)
    {
        for (auto i = 0; i < json["Locaties"].size(); i++)
        {
            CalculationLocation location;
            inputData.locations.push_back(location);

            inputData.locations.at(i).name = json["Locaties"][i]["Naam"].get<std::string>();

            inputData.locations.at(i).revetment.typeTopLayer = json["Locaties"][i]["Bekleding"]["TypeToplaag"].get<std::string>();
            inputData.locations.at(i).revetment.relativeDensity = json["Locaties"][i]["Bekleding"]["RelatieveDichtheid"].get<double>();
            inputData.locations.at(i).revetment.thicknessTopLayer = json["Locaties"][i]["Bekleding"]["DikteToplaag"].get<double>();
            inputData.locations.at(i).revetment.initialDamage = json["Locaties"][i]["Bekleding"]["BeginSchade"].get<double>();
            inputData.locations.at(i).revetment.similarityParameterThreshold = json["Locaties"][i]["Bekleding"]["BrekerIndexGrenswaarde"].get<double>();
            inputData.locations.at(i).revetment.coefficientPlungingAp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingAp"].get<double>();
            inputData.locations.at(i).revetment.coefficientPlungingBp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingBp"].get<double>();
            inputData.locations.at(i).revetment.coefficientPlungingCp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingCp"].get<double>();
            inputData.locations.at(i).revetment.coefficientPlungingNp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingNp"].get<double>();
            inputData.locations.at(i).revetment.coefficientSurgingAs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingAs"].get<double>();
            inputData.locations.at(i).revetment.coefficientSurgingBs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingBs"].get<double>();
            inputData.locations.at(i).revetment.coefficientSurgingCs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingCs"].get<double>();
            inputData.locations.at(i).revetment.coefficientSurgingNs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingNs"].get<double>();

            inputData.locations.at(i).profileSchematization.tanA = json["Locaties"][i]["Profielschematisatie"]["TanA"].get<double>();
        }
    }

    nlohmann::json InputComposer::ParseJson(const std::string filePath) const
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

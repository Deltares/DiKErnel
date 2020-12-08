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

        inputData.calculationData = ReadCalculationData(json);

        inputData.hydraulicLoads = ReadHydraulicLoads(json);

        inputData.locations = ReadLocations(json);
    }

    CalculationData InputComposer::ReadCalculationData(nlohmann::json json)
    {
        CalculationData calculationData;
        calculationData.time = json["Rekendata"]["Tijd"].get<std::vector<int>>();

        return calculationData;
    }

    HydraulicLoads InputComposer::ReadHydraulicLoads(nlohmann::json json)
    {
        HydraulicLoads hydraulicLoads;

        hydraulicLoads.waveAngleMaximum = json["HydraulischeBelastingen"]["GolfhoekMaximum"].get<int>();

        const auto arraySize = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"].size();

        for (auto i = 0; i < arraySize; i++)
        {
            BoundaryConditionsPerTimeStep boundaryConditionsPerTimeStep;
            hydraulicLoads.boundaryConditionsPerTimeStep.push_back(boundaryConditionsPerTimeStep);
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveHeightHm0 =
                    json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfhoogteHm0"].get<double>();
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).wavePeriodTm10 =
                    json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfperiodeTm10"].get<double>();
            hydraulicLoads.boundaryConditionsPerTimeStep.at(i).waveAngle =
                    json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["Golfhoek"].get<double>();
        }

        return hydraulicLoads;
    }

    std::vector<CalculationLocation> InputComposer::ReadLocations(nlohmann::json json)
    {
        std::vector<CalculationLocation> calculationLocations;

        for (auto i = 0; i < json["Locaties"].size(); i++)
        {
            CalculationLocation location;
            calculationLocations.push_back(location);

            calculationLocations.at(i).name = json["Locaties"][i]["Naam"].get<std::string>();

            calculationLocations.at(i).revetment.typeTopLayer = json["Locaties"][i]["Bekleding"]["TypeToplaag"].get<std::string>();
            calculationLocations.at(i).revetment.relativeDensity = json["Locaties"][i]["Bekleding"]["RelatieveDichtheid"].get<double>();
            calculationLocations.at(i).revetment.thicknessTopLayer = json["Locaties"][i]["Bekleding"]["DikteToplaag"].get<double>();
            calculationLocations.at(i).revetment.initialDamage = json["Locaties"][i]["Bekleding"]["BeginSchade"].get<double>();
            calculationLocations.at(i).revetment.similarityParameterThreshold =
                    json["Locaties"][i]["Bekleding"]["BrekerIndexGrenswaarde"].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingAp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingAp"].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingBp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingBp"].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingCp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingCp"].get<double>();
            calculationLocations.at(i).revetment.coefficientPlungingNp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingNp"].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingAs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingAs"].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingBs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingBs"].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingCs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingCs"].get<double>();
            calculationLocations.at(i).revetment.coefficientSurgingNs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingNs"].get<double>();

            calculationLocations.at(i).profileSchematization.tanA = json["Locaties"][i]["Profielschematisatie"]["TanA"].get<double>();
        }

        return calculationLocations;
    }

    nlohmann::json InputComposer::ParseJson(const std::string filePath) const
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

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

        // CalculationData
        inputData.calculationData.time = json["RekenData"]["Tijd"].get<std::vector<int>>();

        // HydraulicLoads
        inputData.hydraulicLoads.waveAngleMaximum = json["HydraulischeBelastingen"]["GolfhoekMaximum"].get<int>();

        for (auto i = 0; i < json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"].size(); i++)
        {
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep[i].waveHeightHm0 = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfhoogteHm0"].get<double>();
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep[i].wavePeriodTm10 = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["GolfperiodeTm10"].get<double>();
            inputData.hydraulicLoads.boundaryConditionsPerTimeStep[i].waveAngle = json["HydraulischeBelastingen"]["RandvoorwaardenPerTijdstap"][i]["Golfhoek"].get<double>();
        }

        // Locations
        for (auto i = 0; i < json["Locaties"].size(); i++)
        {
            inputData.locations[i].name = json["Locaties"][i]["Naam"].get<std::string>();

            inputData.locations[i].revetment.typeTopLayer = json["Locaties"][i]["Bekleding"]["TypeToplaag"].get<std::string>();
            inputData.locations[i].revetment.relativeDensity = json["Locaties"][i]["Bekleding"]["RelatieveDichtheid"].get<double>();
            inputData.locations[i].revetment.thicknessTopLayer = json["Locaties"][i]["Bekleding"]["DikteToplaag"].get<double>();
            inputData.locations[i].revetment.initialDamage = json["Locaties"][i]["Bekleding"]["BeginSchade"].get<double>();
            inputData.locations[i].revetment.similarityParameterThreshold = json["Locaties"][i]["Bekleding"]["BrekerIndexGrenswaarde"].get<double>();
            inputData.locations[i].revetment.coefficientPlungingAp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingAp"].get<double>();
            inputData.locations[i].revetment.coefficientPlungingBp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingBp"].get<double>();
            inputData.locations[i].revetment.coefficientPlungingCp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingCp"].get<double>();
            inputData.locations[i].revetment.coefficientPlungingNp = json["Locaties"][i]["Bekleding"]["CoefficientPlungingNp"].get<double>();
            inputData.locations[i].revetment.coefficientSurgingAs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingAs"].get<double>();
            inputData.locations[i].revetment.coefficientSurgingBs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingBs"].get<double>();
            inputData.locations[i].revetment.coefficientSurgingCs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingCs"].get<double>();
            inputData.locations[i].revetment.coefficientSurgingNs = json["Locaties"][i]["Bekleding"]["CoefficientSurgingNs"].get<double>();

            inputData.locations[i].profileSchematization.tanA = json["Locaties"][i]["Profielschematisatie"]["TanA"].get<double>();
        }
    }

    nlohmann::json InputComposer::ParseJson(const std::string filePath) const
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

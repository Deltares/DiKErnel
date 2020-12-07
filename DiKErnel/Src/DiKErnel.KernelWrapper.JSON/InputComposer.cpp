#include "InputComposer.h"

#include <fstream>


#include "InputData.h"
#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    std::vector<int> InputComposer::GetDomainParametersFromJson(const std::string filePath) const
    {
        auto json = ParseJson(filePath);

        InputData inputData;

        inputData.calculationData.time = json["RekenData"]["Tijd"].get<std::vector<int>>();

    }

    nlohmann::json InputComposer::ParseJson(const std::string filePath) const
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}

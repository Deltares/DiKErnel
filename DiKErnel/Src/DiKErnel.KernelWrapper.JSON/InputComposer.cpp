#include "InputComposer.h"

#include <fstream>

#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    InputComposer::InputComposer()
    {
        created = true;
    }

    std::vector<int> InputComposer::GetDomainParametersFromJson(const std::string filePath) const
    {
        auto json = ParseJson(filePath);

        return json["Domeinparameters"]["Tijd"].get<std::vector<int>>();
    }

    nlohmann::json InputComposer::ParseJson(const std::string filePath) const
    {
        std::ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }
}
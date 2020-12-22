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

#include <nlohmann/json.hpp>

#include <fstream>
#include <iomanip>

#include "OutputComposer.h"
#include "JsonDefinitions.h"
#include "OutputData.h"
#include "RevetmentOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    void OutputComposer::WriteParametersToJson(
        const std::string& filePath,
        const OutputData& outputData)
    {
        nlohmann::json json;

        json[JsonDefinitions::locations] = nlohmann::json::array();

        for (const auto& calculationLocationOutput : outputData.GetCalculationLocationsOutput())
        {
            json[JsonDefinitions::locations].push_back(
                nlohmann::json::object(
                    {
                        {
                            JsonDefinitions::name,
                            calculationLocationOutput.get().GetName()
                        },
                        {
                            JsonDefinitions::revetment,
                            {
                                {
                                    JsonDefinitions::damage,
                                    calculationLocationOutput.get().GetRevetmentOutput().GetDamage()
                                }
                            }
                        }
                    }));
        }

        std::ofstream outfile(filePath, std::ios::trunc);
        outfile << std::setw(4) << json << std::endl;
    }
}

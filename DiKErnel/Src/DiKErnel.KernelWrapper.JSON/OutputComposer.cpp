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

#include "OutputComposer.h"

#include <filesystem>
#include <ostream>
#include <nlohmann/json.hpp>

#include <iostream>

#include "JsonDefinitions.h"
#include "OutputData.h"
#include "RevetmentOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    std::string OutputComposer::WriteParametersToJson(
        std::filesystem::path filePath,
        OutputData outputData)
    {
        nlohmann::json json;

        const auto amountOfOutputLocations = outputData.GetLocationsOutput().size();

        try
        {
            json[JsonDefinitions::locations] = nlohmann::json::array();

            for (auto i = 0; i < amountOfOutputLocations; i++)
            {
                auto location = nlohmann::json::object(
                    {
                        {
                            JsonDefinitions::name,
                            outputData.GetLocationsOutput().at(i)->GetName()
                        },
                        {
                            JsonDefinitions::revetment,
                            {
                                {
                                    JsonDefinitions::damage,
                                    outputData.GetLocationsOutput().at(i)->GetRevetmentOutput()->GetDamage()
                                }
                            }
                        }
                    });

                json[JsonDefinitions::locations].push_back(location);
            }

            //std::ofstream o(filePath);
            return json.dump();

            //std::cout << std::setw(4) << json << std::endl;
            //o.close();
        }
        catch (nlohmann::json::type_error& e)
        {
            std::cout << e.what() << '\n';
        }
    }
}

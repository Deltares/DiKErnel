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
#include <fstream>
#include <ostream>
#include <nlohmann/json.hpp>

#include "OutputData.h"
#include "RevetmentOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    void OutputComposer::WriteParametersToJson(
        std::filesystem::path filePath,
        OutputData outputData)
    {
        nlohmann::json json;

        json["Locaties"]["Naam"] = (outputData.GetLocationsOutput().at(0)->GetName());
        json["Locaties"]["Schade"] = (outputData.GetLocationsOutput().at(0)->GetRevetmentOutput()->GetDamage());

        std::ofstream o(filePath);
        o << std::setw(4) << json << std::endl;
        o.close();
    }
}

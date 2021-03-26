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

#pragma once

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "JsonInputData.h"
#include "JsonInputNaturalStoneRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputParser
    {
        public:
            static std::unique_ptr<JsonInputData> GetJsonInputData(
                const std::string& filePath);

            enum class CalculationType
            {
                Unknown,
                NaturalStone
            };

        private:

            static nlohmann::json ReadJson(
                const std::string& filePath);

            static std::vector<int> ParseTime(
                const nlohmann::json& json);

            static std::unique_ptr<JsonInputHydraulicData> ParseHydraulicData(
                const nlohmann::json& json);

            static std::vector<std::unique_ptr<JsonInputLocationData>> ParseLocationData(
                const nlohmann::json& json);

            static std::unique_ptr<IJsonInputRevetmentLocationData> ParseRevetmentLocationData(
                const nlohmann::basic_json<>::value_type& readRevetment);
    };
}

// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "JsonInputCalculationType.h"
#include "JsonInputData.h"
#include "JsonInputDikeProfileData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputParser
    {
        public:
            static std::unique_ptr<JsonInputData> GetJsonInputData(
                const std::string& filePath);

        private:
            static nlohmann::json ReadJson(
                const std::string& filePath);

            static std::unique_ptr<JsonInputProcessData> ParseProcessData(
                const nlohmann::json& readJson);

            static std::vector<int> ParseTime(
                const nlohmann::json& readCalculationData);

            static std::unique_ptr<JsonInputHydraulicData> ParseHydraulicData(
                const nlohmann::json& readCalculationData);

            static std::unique_ptr<JsonInputDikeProfileData> ParseDikeProfileData(
                const nlohmann::json& readCalculationData);

            static std::vector<std::unique_ptr<JsonInputLocationData>> ParseLocationData(
                const nlohmann::json& readCalculationData);

            static std::map<JsonInputCalculationType, std::unique_ptr<JsonInputCalculationDefinitionData>> ParseCalculationDefinitionData(
                const nlohmann::json& readCalculationData);

            template <typename T>
            static std::unique_ptr<T> CreateLocationParser(
                const nlohmann::json& readLocation,
                const nlohmann::json& readRevetment,
                const nlohmann::json& readCalculationMethod);

            template <typename T>
            static std::unique_ptr<T> CreateCalculationDefinitionParser(
                const nlohmann::json& readCalculationDefinition);
    };
}

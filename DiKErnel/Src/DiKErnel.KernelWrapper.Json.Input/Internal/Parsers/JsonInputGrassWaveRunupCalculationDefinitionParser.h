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

#include <nlohmann/json.hpp>

#include "JsonInputCalculationDefinitionParser.h"
#include "JsonInputGrassRevetmentTopLayerType.h"
#include "JsonInputGrassWaveRunupCalculationProtocolData.h"
#include "JsonInputGrassWaveRunupTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupCalculationDefinitionParser : public JsonInputCalculationDefinitionParser
    {
        public:
            explicit JsonInputGrassWaveRunupCalculationDefinitionParser(
                const nlohmann::json& readCalculationMethod);

        protected:
            std::unique_ptr<JsonInputCalculationDefinitionData> ParseCalculationDefinition(
                std::unique_ptr<double> failureNumber) override;

        private:
            static std::unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> ReadCalculationProtocolData(
                const nlohmann::json& readCalculationMethod);

            static std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>>
            ReadTopLayerDefinitionData(
                const nlohmann::json& readCalculationMethod);
    };
}

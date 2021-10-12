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

#include <nlohmann/json.hpp>

#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputLocationParser
    {
        public:
            virtual ~JsonInputLocationParser() = default;

            explicit JsonInputLocationParser(
                const nlohmann::json& readLocation,
                const nlohmann::json& readRevetment,
                const nlohmann::json& readCalculationMethod);

            std::unique_ptr<JsonInputLocationData> Parse();

        protected:
            virtual std::unique_ptr<JsonInputLocationData> ParseLocationData(
                std::string name,
                double x,
                std::unique_ptr<JsonInputDamageData> damageData) = 0;

            const nlohmann::json& GetReadRevetment() const;

            const nlohmann::json& GetReadCalculationMethod() const;

        private:
            const nlohmann::json& _readLocation;
            const nlohmann::json& _readRevetment;
            const nlohmann::json& _readCalculationMethod;
    };
}

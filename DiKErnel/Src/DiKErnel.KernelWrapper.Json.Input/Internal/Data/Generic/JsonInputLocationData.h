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

#include "JsonInputDamageData.h"
#include "JsonInputProfileSchematizationData.h"
#include "JsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputLocationData
    {
        public:
            explicit JsonInputLocationData(
                std::string name,
                std::unique_ptr<JsonInputDamageData> damageData,
                std::unique_ptr<JsonInputRevetmentLocationData> revetmentLocationData,
                std::unique_ptr<JsonInputProfileSchematizationData> profileSchematizationData);

            const std::string& GetName() const;

            const JsonInputDamageData& GetDamageData() const;

            const JsonInputRevetmentLocationData& GetRevetmentLocationData() const;

            const JsonInputProfileSchematizationData& GetProfileSchematizationData() const;

        private:
            std::string _name;
            std::unique_ptr<JsonInputDamageData> _damageData;
            std::unique_ptr<JsonInputRevetmentLocationData> _revetmentLocationData;
            std::unique_ptr<JsonInputProfileSchematizationData> _profileSchematizationData;
    };
}

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

#include <map>
#include <memory>
#include <vector>

#include "JsonInputCalculationDefinitionData.h"
#include "JsonInputCalculationType.h"
#include "JsonInputDikeProfileData.h"
#include "JsonInputHydraulicData.h"
#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputData
    {
        public:
            explicit JsonInputData(
                std::vector<int> times,
                std::unique_ptr<JsonInputHydraulicData> hydraulicData,
                std::unique_ptr<JsonInputDikeProfileData> dikeProfileData,
                std::vector<std::unique_ptr<JsonInputLocationData>> locationData,
                std::map<JsonInputCalculationType, std::unique_ptr<JsonInputCalculationDefinitionData>> calculationDefinitionData);

            [[nodiscard]]
            const std::vector<int>& GetTimes() const;

            [[nodiscard]]
            const JsonInputHydraulicData& GetHydraulicData() const;

            [[nodiscard]]
            const JsonInputDikeProfileData& GetDikeProfileData() const;

            [[nodiscard]]
            const std::vector<std::reference_wrapper<JsonInputLocationData>>& GetLocationData() const;

            [[nodiscard]]
            const std::map<JsonInputCalculationType, std::reference_wrapper<JsonInputCalculationDefinitionData>>&
            GetCalculationDefinitionData() const;

        private:
            std::vector<int> _times;
            std::unique_ptr<JsonInputHydraulicData> _hydraulicData;
            std::unique_ptr<JsonInputDikeProfileData> _dikeProfileData;
            std::vector<std::unique_ptr<JsonInputLocationData>> _locationData;
            std::vector<std::reference_wrapper<JsonInputLocationData>> _locationDataReferences;
            std::map<JsonInputCalculationType, std::unique_ptr<JsonInputCalculationDefinitionData>> _calculationDefinitionData;
            std::map<JsonInputCalculationType, std::reference_wrapper<JsonInputCalculationDefinitionData>> _calculationDefinitionDataReferences;
    };
}

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

#include "JsonInputGrassRevetmentWaveRunupProfileSchematizationData.h"
#include "JsonInputGrassRevetmentWaveRunupRayleighLocationData.h"
#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupRayleighLocationData : public JsonInputLocationData
    {
        public:
            explicit JsonInputGrassWaveRunupRayleighLocationData(
                double x,
                std::unique_ptr<JsonInputDamageData> damageData,
                std::unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> revetmentLocationData,
                std::unique_ptr<JsonInputGrassRevetmentWaveRunupProfileSchematizationData> profileSchematizationData);

            [[nodiscard]]
            const JsonInputGrassRevetmentWaveRunupRayleighLocationData& GetRevetmentLocationData() const;

            [[nodiscard]]
            const JsonInputGrassRevetmentWaveRunupProfileSchematizationData& GetProfileSchematizationData() const;

        private:
            std::unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> _revetmentLocationData;
            std::unique_ptr<JsonInputGrassRevetmentWaveRunupProfileSchematizationData> _profileSchematizationData;
    };
}

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

#include "JsonInputGrassWaveRunupCalculationProtocolData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupRayleighCalculationProtocolData : public JsonInputGrassWaveRunupCalculationProtocolData
    {
        public:
            #pragma region Set methods

            void SetFixedNumberOfWaves(
                std::unique_ptr<int> fixedNumberOfWaves);

            void SetFrontVelocityCu(
                std::unique_ptr<double> frontVelocityCu);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const int* GetFixedNumberOfWaves() const;

            [[nodiscard]]
            const double* GetFrontVelocityCu() const;

            #pragma endregion

        private:
            std::unique_ptr<int> _fixedNumberOfWaves = nullptr;
            std::unique_ptr<double> _frontVelocityCu = nullptr;
    };
}

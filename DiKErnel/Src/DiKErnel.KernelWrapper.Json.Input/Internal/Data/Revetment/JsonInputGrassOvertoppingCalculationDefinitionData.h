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

#include "JsonInputCalculationDefinitionData.h"
#include "JsonInputGrassCumulativeOverloadTopLayerDefinitionData.h"
#include "JsonInputGrassOvertoppingCalculationProtocolData.h"
#include "JsonInputGrassRevetmentTopLayerType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassOvertoppingCalculationDefinitionData : public JsonInputCalculationDefinitionData
    {
        public:
            explicit JsonInputGrassOvertoppingCalculationDefinitionData(
                std::unique_ptr<double> failureNumber,
                std::unique_ptr<JsonInputGrassOvertoppingCalculationProtocolData> calculationProtocolData,
                std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>
                topLayerDefinitionData);

            #pragma region Set methods

            void SetAccelerationAlphaACrest(
                std::unique_ptr<double> accelerationAlphaACrest);

            void SetAccelerationAlphaAInnerSlope(
                std::unique_ptr<double> accelerationAlphaAInnerSlope);

            void SetFixedNumberOfWaves(
                std::unique_ptr<int> fixedNumberOfWaves);

            void SetFrontVelocity(
                std::unique_ptr<double> frontVelocity);

            void SetFactorCtm(
                std::unique_ptr<double> factorCtm);

            #pragma endregion

            #pragma region Set methods

            [[nodiscard]]
            const double* GetAccelerationAlphaACrest() const;

            [[nodiscard]]
            const double* GetAccelerationAlphaAInnerSlope() const;

            [[nodiscard]]
            const int* GetFixedNumberOfWaves() const;

            [[nodiscard]]
            const double* GetFrontVelocity() const;

            [[nodiscard]]
            const double* GetFactorCtm() const;

            #pragma endregion

        private:
            std::unique_ptr<JsonInputGrassOvertoppingCalculationProtocolData> _calculationProtocolData;
            std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>
            _topLayerDefinitionData;

            std::unique_ptr<double> _accelerationAlphaACrest = nullptr;
            std::unique_ptr<double> _accelerationAlphaAInnerSlope = nullptr;
            std::unique_ptr<int> _fixedNumberOfWaves = nullptr;
            std::unique_ptr<double> _frontVelocity = nullptr;
            std::unique_ptr<double> _factorCtm = nullptr;
    };
}

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

#include "JsonInputAsphaltRevetmentTopLayerType.h"
#include "JsonInputAsphaltWaveImpactTopLayerDefinitionData.h"
#include "JsonInputCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAsphaltWaveImpactCalculationDefinitionData : public JsonInputCalculationDefinitionData
    {
        public:
            explicit JsonInputAsphaltWaveImpactCalculationDefinitionData(
                std::unique_ptr<double> failureNumber,
                std::map<JsonInputAsphaltRevetmentTopLayerType, std::unique_ptr<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>
                topLayerDefinitionData);

            #pragma region Set methods

            void SetDensityOfWater(
                std::unique_ptr<double> densityOfWater);

            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            void SetImpactNumberC(
                std::unique_ptr<double> impactNumberC);

            void SetWidthFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> widthFactors);

            void SetDepthFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> depthFactors);

            void SetImpactFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> impactFactors);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const std::map<JsonInputAsphaltRevetmentTopLayerType, std::reference_wrapper<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>& GetTopLayerDefinitionData() const;

            [[nodiscard]]
            const double* GetDensityOfWater() const;

            [[nodiscard]]
            const double* GetAverageNumberOfWavesCtm() const;

            [[nodiscard]]
            const double* GetImpactNumberC() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetWidthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetDepthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetImpactFactors() const;

            #pragma endregion

        private:
            std::map<JsonInputAsphaltRevetmentTopLayerType, std::unique_ptr<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>
                _topLayerDefinitionData;
            std::map<JsonInputAsphaltRevetmentTopLayerType, std::reference_wrapper<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>
                _topLayerDefinitionDataReferences;
            std::unique_ptr<double> _densityOfWater;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _impactNumberC = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _widthFactors = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _depthFactors = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _impactFactors = nullptr;
    };
}

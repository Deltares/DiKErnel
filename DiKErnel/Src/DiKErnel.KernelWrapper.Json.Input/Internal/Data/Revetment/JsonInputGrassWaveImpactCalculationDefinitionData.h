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

#include "JsonInputCalculationDefinitionData.h"
#include "JsonInputGrassRevetmentTopLayerType.h"
#include "JsonInputGrassWaveImpactTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveImpactCalculationDefinitionData : public JsonInputCalculationDefinitionData
    {
        public:
            explicit JsonInputGrassWaveImpactCalculationDefinitionData(
                std::unique_ptr<double> failureNumber,
                std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassWaveImpactTopLayerDefinitionData>>
                topLayerDefinitionData);

            #pragma region Set methods

            void SetTemax(
                std::unique_ptr<double> temax);

            void SetTemin(
                std::unique_ptr<double> temin);

            void SetWaveAngleImpactN(
                std::unique_ptr<double> waveAngleImpactN);

            void SetWaveAngleImpactQ(
                std::unique_ptr<double> waveAngleImpactQ);

            void SetWaveAngleImpactR(
                std::unique_ptr<double> waveAngleImpactR);

            void SetUpperLimitLoading(
                std::unique_ptr<double> upperLimitLoading);

            void SetLowerLimitLoading(
                std::unique_ptr<double> lowerLimitLoading);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const std::map<JsonInputGrassRevetmentTopLayerType, std::reference_wrapper<JsonInputGrassWaveImpactTopLayerDefinitionData>>&
            GetTopLayerDefinitionData() const;

            [[nodiscard]]
            const double* GetTemax() const;

            [[nodiscard]]
            const double* GetTemin() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactN() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactQ() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactR() const;

            [[nodiscard]]
            const double* GetUpperLimitLoading() const;

            [[nodiscard]]
            const double* GetLowerLimitLoading() const;

            #pragma endregion

        private:
            std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassWaveImpactTopLayerDefinitionData>>
            _topLayerDefinitionData;
            std::map<JsonInputGrassRevetmentTopLayerType, std::reference_wrapper<JsonInputGrassWaveImpactTopLayerDefinitionData>>
            _topLayerDefinitionDataReferences;
            std::unique_ptr<double> _temax = nullptr;
            std::unique_ptr<double> _temin = nullptr;
            std::unique_ptr<double> _waveAngleImpactN = nullptr;
            std::unique_ptr<double> _waveAngleImpactQ = nullptr;
            std::unique_ptr<double> _waveAngleImpactR = nullptr;
            std::unique_ptr<double> _upperLimitLoading = nullptr;
            std::unique_ptr<double> _lowerLimitLoading = nullptr;
    };
}

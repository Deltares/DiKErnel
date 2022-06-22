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
#include "JsonInputNaturalStoneRevetmentTopLayerType.h"
#include "JsonInputNaturalStoneTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneCalculationDefinitionData : public JsonInputCalculationDefinitionData
    {
        public:
            explicit JsonInputNaturalStoneCalculationDefinitionData(
                std::unique_ptr<double> failureNumber,
                std::map<JsonInputNaturalStoneRevetmentTopLayerType, std::unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>
                topLayerDefinitionData);

            #pragma region Set methods

            void SetSlopeUpperLevel(
                std::unique_ptr<double> slopeUpperLevel);

            void SetSlopeLowerLevel(
                std::unique_ptr<double> slopeLowerLevel);

            void SetUpperLimitLoadingA(
                std::unique_ptr<double> upperLimitLoadingA);

            void SetUpperLimitLoadingB(
                std::unique_ptr<double> upperLimitLoadingB);

            void SetUpperLimitLoadingC(
                std::unique_ptr<double> upperLimitLoadingC);

            void SetLowerLimitLoadingA(
                std::unique_ptr<double> lowerLimitLoadingA);

            void SetLowerLimitLoadingB(
                std::unique_ptr<double> lowerLimitLoadingB);

            void SetLowerLimitLoadingC(
                std::unique_ptr<double> lowerLimitLoadingC);

            void SetDistanceMaximumWaveElevationA(
                std::unique_ptr<double> distanceMaximumWaveElevationA);

            void SetDistanceMaximumWaveElevationB(
                std::unique_ptr<double> distanceMaximumWaveElevationB);

            void SetNormativeWidthOfWaveImpactA(
                std::unique_ptr<double> normativeWidthOfWaveImpactA);

            void SetNormativeWidthOfWaveImpactB(
                std::unique_ptr<double> normativeWidthOfWaveImpactB);

            void SetWaveAngleImpactBetaMax(
                std::unique_ptr<double> waveAngleImpactBetaMax);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const std::map<JsonInputNaturalStoneRevetmentTopLayerType, std::reference_wrapper<JsonInputNaturalStoneTopLayerDefinitionData>>&
            GetTopLayerDefinitionData() const;

            [[nodiscard]]
            const double* GetSlopeUpperLevelA() const;

            [[nodiscard]]
            const double* GetSlopeLowerLevelA() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingA() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingB() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingC() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingA() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingB() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingC() const;

            [[nodiscard]]
            const double* GetDistanceMaximumWaveElevationA() const;

            [[nodiscard]]
            const double* GetDistanceMaximumWaveElevationB() const;

            [[nodiscard]]
            const double* GetNormativeWidthOfWaveImpactA() const;

            [[nodiscard]]
            const double* GetNormativeWidthOfWaveImpactB() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactBetaMax() const;

            #pragma endregion

        private:
            std::map<JsonInputNaturalStoneRevetmentTopLayerType, std::unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>>
            _topLayerDefinitionData;
            std::map<JsonInputNaturalStoneRevetmentTopLayerType, std::reference_wrapper<JsonInputNaturalStoneTopLayerDefinitionData>>
            _topLayerDefinitionDataReferences;
            std::unique_ptr<double> _slopeUpperLevel = nullptr;
            std::unique_ptr<double> _slopeLowerLevel = nullptr;
            std::unique_ptr<double> _upperLimitLoadingA = nullptr;
            std::unique_ptr<double> _upperLimitLoadingB = nullptr;
            std::unique_ptr<double> _upperLimitLoadingC = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingA = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingB = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingC = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationA = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationB = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactA = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactB = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetaMax = nullptr;
    };
}

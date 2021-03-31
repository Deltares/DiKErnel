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

#include "IJsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassRevetmentWaveImpactLocationData : public IJsonInputRevetmentLocationData
    {
        public:
            enum class TopLayerType
            {
                Unknown,
                OpenSod,
                ClosedSod
            };

            explicit JsonInputGrassRevetmentWaveImpactLocationData(
                TopLayerType topLayerType);

            #pragma region Set methods

            void SetTimeLineAgwi(
                std::unique_ptr<double> timeLineAgwi);

            void SetTimeLineBgwi(
                std::unique_ptr<double> timeLineBgwi);

            void SetTimeLineCgwi(
                std::unique_ptr<double> timeLineCgwi);

            void SetMinimumWaveHeightTemax(
                std::unique_ptr<double> minimumWaveHeightTemax);

            void SetMaximumWaveHeightTemin(
                std::unique_ptr<double> maximumWaveHeightTemin);

            void SetWaveAngleImpactNwa(
                std::unique_ptr<double> waveAngleImpactNwa);

            void SetWaveAngleImpactQwa(
                std::unique_ptr<double> waveAngleImpactQwa);

            void SetWaveAngleImpactRwa(
                std::unique_ptr<double> waveAngleImpactRwa);

            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            #pragma endregion

            #pragma region Get methods

            TopLayerType GetTopLayerType() const;

            const double* GetTimeLineAgwi() const;

            const double* GetTimeLineBgwi() const;

            const double* GetTimeLineCgwi() const;

            const double* GetMinimumWaveHeightTemax() const;

            const double* GetMaximumWaveHeightTemin() const;

            const double* GetWaveAngleImpactNwa() const;

            const double* GetWaveAngleImpactQwa() const;

            const double* GetWaveAngleImpactRwa() const;

            const double* GetUpperLimitLoadingAul() const;

            const double* GetLowerLimitLoadingAll() const;

            #pragma endregion

        private:
            TopLayerType _topLayerType;
            std::unique_ptr<double> _timeLineAgwi = nullptr;
            std::unique_ptr<double> _timeLineBgwi = nullptr;
            std::unique_ptr<double> _timeLineCgwi = nullptr;
            std::unique_ptr<double> _minimumWaveHeightTemax = nullptr;
            std::unique_ptr<double> _maximumWaveHeightTemin = nullptr;
            std::unique_ptr<double> _waveAngleImpactNwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactQwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactRwa = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
    };
}

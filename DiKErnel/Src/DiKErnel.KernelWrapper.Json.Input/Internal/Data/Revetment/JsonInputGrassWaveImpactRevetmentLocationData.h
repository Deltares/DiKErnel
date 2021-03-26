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

#include "JsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveImpactRevetmentLocationData : public JsonInputRevetmentLocationData
    {
        public:
            enum class TopLayerType
            {
                Unknown,
                OpenSod,
                ClosedSod
            };

            explicit JsonInputGrassWaveImpactRevetmentLocationData(
                TopLayerType topLayerType);

            #pragma region Set methods

            void SetFailureTimeAgwi(
                std::unique_ptr<double> failureTimeAgwi);

            void SetFailureTimeBgwi(
                std::unique_ptr<double> failureTimeBgwi);

            void SetFailureTimeCgwi(
                std::unique_ptr<double> failureTimeCgwi);

            void SetMinimumWaveHeightTemax(
                std::unique_ptr<double> minimumWaveHeightTemax);

            void SetMinimumWaveHeightTemin(
                std::unique_ptr<double> minimumWaveHeightTemin);

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

            const double* GetFailureTimeAgwi() const;

            const double* GetFailureTimeBgwi() const;

            const double* GetFailureTimeCgwi() const;

            const double* GetMinimumWaveHeightTemax() const;

            const double* GetMinimumWaveHeightTemin() const;

            const double* GetWaveAngleImpactNwa() const;

            const double* GetWaveAngleImpactQwa() const;

            const double* GetWaveAngleImpactRwa() const;

            const double* GetUpperLimitLoadingAul() const;

            const double* GetLowerLimitLoadingAll() const;

            #pragma endregion

        private:
            TopLayerType _topLayerType;
            std::unique_ptr<double> _failureTimeAgwi = nullptr;
            std::unique_ptr<double> _failureTimeBgwi = nullptr;
            std::unique_ptr<double> _failureTimeCgwi = nullptr;
            std::unique_ptr<double> _minimumWaveHeightTemax = nullptr;
            std::unique_ptr<double> _minimumWaveHeightTemin = nullptr;
            std::unique_ptr<double> _waveAngleImpactNwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactQwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactRwa = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
    };
}

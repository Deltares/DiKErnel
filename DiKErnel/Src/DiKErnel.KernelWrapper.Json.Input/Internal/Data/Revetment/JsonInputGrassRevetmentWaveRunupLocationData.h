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
#include "JsonInputGrassRevetmentTopLayerType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassRevetmentWaveRunupLocationData : public IJsonInputRevetmentLocationData
    {
        public:
            #pragma region Set methods

            void SetCriticalCumulativeOverload(
                std::unique_ptr<double> criticalCumulativeOverload);

            void SetCriticalFrontVelocity(
                std::unique_ptr<double> criticalFrontVelocity);

            void SetIncreasedLoadTransitionAlphaM(
                std::unique_ptr<double> increasedLoadTransitionAlphaM);

            void SetReducedStrengthTransitionAlphaS(
                std::unique_ptr<double> reducedStrengthTransitionAlphaS);

            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            void SetRepresentativeWaveRunUp2PAru(
                std::unique_ptr<double> representativeWaveRunUp2PAru);

            void SetRepresentativeWaveRunUp2PBru(
                std::unique_ptr<double> representativeWaveRunUp2PBru);

            void SetRepresentativeWaveRunUp2PCru(
                std::unique_ptr<double> representativeWaveRunUp2PCru);

            void SetWaveAngleImpactAbeta(
                std::unique_ptr<double> waveAngleImpactAbeta);

            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            JsonInputGrassRevetmentTopLayerType GetTopLayerType() const;

            const double* GetCriticalCumulativeOverload() const;

            const double* GetCriticalFrontVelocity() const;

            const double* GetIncreasedLoadTransitionAlphaM() const;

            const double* GetReducedStrengthTransitionAlphaS() const;

            const double* GetAverageNumberOfWavesCtm() const;

            const double* GetRepresentativeWaveRunUp2PAru() const;

            const double* GetRepresentativeWaveRunUp2PBru() const;

            const double* GetRepresentativeWaveRunUp2PCru() const;

            const double* GetWaveAngleImpactAbeta() const;

            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        protected:
            explicit JsonInputGrassRevetmentWaveRunupLocationData(
                JsonInputGrassRevetmentTopLayerType topLayerType);

        private:
            JsonInputGrassRevetmentTopLayerType _topLayerType;
            std::unique_ptr<double> _criticalCumulativeOverload = nullptr;
            std::unique_ptr<double> _criticalFrontVelocity = nullptr;
            std::unique_ptr<double> _increasedLoadTransitionAlphaM = nullptr;
            std::unique_ptr<double> _reducedStrengthTransitionAlphaS = nullptr;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _representativeWaveRunUp2PAru = nullptr;
            std::unique_ptr<double> _representativeWaveRunUp2PBru = nullptr;
            std::unique_ptr<double> _representativeWaveRunUp2PCru = nullptr;
            std::unique_ptr<double> _waveAngleImpactAbeta = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetamax = nullptr;
    };
}

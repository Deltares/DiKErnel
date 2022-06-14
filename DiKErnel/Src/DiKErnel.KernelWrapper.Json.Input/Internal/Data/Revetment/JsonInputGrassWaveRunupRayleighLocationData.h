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

#include "JsonInputGrassRevetmentTopLayerType.h"
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
                std::unique_ptr<double> initialDamage,
                JsonInputGrassRevetmentTopLayerType topLayerType,
                double outerSlope,
                std::unique_ptr<JsonInputDamageData> damageData,
                std::unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> revetmentLocationData,
                std::unique_ptr<JsonInputGrassRevetmentWaveRunupProfileSchematizationData> profileSchematizationData);

            void SetIncreasedLoadTransitionAlphaM(
                std::unique_ptr<double> increasedLoadTransitionAlphaM);

            void SetReducedStrengthTransitionAlphaS(
                std::unique_ptr<double> reducedStrengthTransitionAlphaS);

            void SetRepresentativeWaveRunup2PGammab(
                std::unique_ptr<double> representativeWaveRunup2PGammab);

            void SetRepresentativeWaveRunup2PGammaf(
                std::unique_ptr<double> representativeWaveRunup2PGammaf);

            [[nodiscard]]
            JsonInputGrassRevetmentTopLayerType GetTopLayerType() const;

            [[nodiscard]]
            double GetOuterSlope() const;

            [[nodiscard]]
            const double* GetIncreasedLoadTransitionAlphaM() const;

            [[nodiscard]]
            const double* GetReducedStrengthTransitionAlphaS() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammab() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammaf() const;

            [[nodiscard]]
            const JsonInputGrassRevetmentWaveRunupRayleighLocationData& GetRevetmentLocationData() const;

            [[nodiscard]]
            const JsonInputGrassRevetmentWaveRunupProfileSchematizationData& GetProfileSchematizationData() const;

        private:
            JsonInputGrassRevetmentTopLayerType _topLayerType;
            double _outerSlope;
            std::unique_ptr<double> _increasedLoadTransitionAlphaM = nullptr;
            std::unique_ptr<double> _reducedStrengthTransitionAlphaS = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PGammab = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PGammaf = nullptr;
            std::unique_ptr<JsonInputGrassRevetmentWaveRunupRayleighLocationData> _revetmentLocationData;
            std::unique_ptr<JsonInputGrassRevetmentWaveRunupProfileSchematizationData> _profileSchematizationData;
    };
}

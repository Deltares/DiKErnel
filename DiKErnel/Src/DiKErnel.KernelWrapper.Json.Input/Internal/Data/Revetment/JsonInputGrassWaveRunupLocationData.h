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
#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupLocationData : public JsonInputLocationData
    {
        public:
            explicit JsonInputGrassWaveRunupLocationData(
                double x,
                std::unique_ptr<double> initialDamage,
                JsonInputGrassRevetmentTopLayerType topLayerType,
                double outerSlope);

            void SetIncreasedLoadTransitionAlphaM(
                std::unique_ptr<double> increasedLoadTransitionAlphaM);

            void SetReducedStrengthTransitionAlphaS(
                std::unique_ptr<double> reducedStrengthTransitionAlphaS);

            void SetRepresentativeWaveRunup2PGammaB(
                std::unique_ptr<double> representativeWaveRunup2PGammaB);

            void SetRepresentativeWaveRunup2PGammaF(
                std::unique_ptr<double> representativeWaveRunup2PGammaF);

            [[nodiscard]]
            JsonInputGrassRevetmentTopLayerType GetTopLayerType() const;

            [[nodiscard]]
            double GetOuterSlope() const;

            [[nodiscard]]
            const double* GetIncreasedLoadTransitionAlphaM() const;

            [[nodiscard]]
            const double* GetReducedStrengthTransitionAlphaS() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammaG() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammaF() const;

        private:
            JsonInputGrassRevetmentTopLayerType _topLayerType;
            double _outerSlope;
            std::unique_ptr<double> _increasedLoadTransitionAlphaM = nullptr;
            std::unique_ptr<double> _reducedStrengthTransitionAlphaS = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PGammaB = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PGammaF = nullptr;
    };
}

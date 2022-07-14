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

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    class AsphaltRevetmentWaveImpactFunctionsInput
    {
        public:
            explicit AsphaltRevetmentWaveImpactFunctionsInput(
                double z,
                const std::vector<std::pair<double, double>>& widthFactors,
                const std::vector<std::pair<double, double>>& depthFactors,
                const std::vector<std::pair<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            void SetWaterLevel(
                double waterLevel);

            void SetWaveHeightHm0(
                double waveHeightHm0);

            [[nodiscard]]
            double GetZ() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetWidthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetDepthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetImpactFactors() const;

            [[nodiscard]]
            double GetFatigueAlpha() const;

            [[nodiscard]]
            double GetFatigueBeta() const;

            [[nodiscard]]
            double GetImpactNumberC() const;

            [[nodiscard]]
            double GetWaterLevel() const;

            [[nodiscard]]
            double GetWaveHeightHm0() const;

        private:
            double _z;
            const std::vector<std::pair<double, double>>& _widthFactors;
            const std::vector<std::pair<double, double>>& _depthFactors;
            const std::vector<std::pair<double, double>>& _impactFactors;
            double _fatigueAlpha;
            double _fatigueBeta;
            double _impactNumberC;
            double _waterLevel = std::numeric_limits<double>::infinity();
            double _waveHeightHm0 = std::numeric_limits<double>::infinity();
    };
}

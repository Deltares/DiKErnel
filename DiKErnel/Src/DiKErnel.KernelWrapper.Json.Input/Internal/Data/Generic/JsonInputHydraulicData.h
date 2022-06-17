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

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputHydraulicData
    {
        public:
            explicit JsonInputHydraulicData(
                std::vector<double> waterLevels,
                std::vector<double> waveHeightsHm0,
                std::vector<double> wavePeriodsTm10,
                std::vector<double> waveAngles);

            [[nodiscard]]
            const std::vector<double>& GetWaterLevels() const;

            [[nodiscard]]
            const std::vector<double>& GetWaveHeightsHm0() const;

            [[nodiscard]]
            const std::vector<double>& GetWavePeriodsTm10() const;

            [[nodiscard]]
            const std::vector<double>& GetWaveAngles() const;

        private:
            std::vector<double> _waterLevels;
            std::vector<double> _waveHeightsHm0;
            std::vector<double> _wavePeriodsTm10;
            std::vector<double> _waveAngles;
    };
}

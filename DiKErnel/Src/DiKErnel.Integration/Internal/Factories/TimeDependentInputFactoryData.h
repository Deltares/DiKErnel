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

namespace DiKErnel::Integration
{
    class TimeDependentInputFactoryData
    {
        public:
            explicit TimeDependentInputFactoryData(
                double beginTime,
                double endTime,
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle);

            [[nodiscard]]
            double GetBeginTime() const;

            [[nodiscard]]
            double GetEndTime() const;

            [[nodiscard]]
            double GetWaterLevel() const;

            [[nodiscard]]
            double GetWaveHeightHm0() const;

            [[nodiscard]]
            double GetWavePeriodTm10() const;

            [[nodiscard]]
            double GetWaveAngle() const;

        private:
            double _beginTime;
            double _endTime;
            double _waterLevel;
            double _waveHeightHm0;
            double _wavePeriodTm10;
            double _waveAngle;
    };
}

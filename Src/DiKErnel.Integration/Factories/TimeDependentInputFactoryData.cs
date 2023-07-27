﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.Integration.Factories
{
    internal static class TimeDependentInputFactoryData
    {
        public TimeDependentInputFactoryData(
                int beginTime,
                int endTime,
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle);

        public int GetBeginTime() const;

        public int GetEndTime() const;

        public double GetWaterLevel() const;

        public double GetWaveHeightHm0() const;

        public double GetWavePeriodTm10() const;

        public double GetWaveAngle() const;

        private:
            int _beginTime;
            int _endTime;
            double _waterLevel;
            double _waveHeightHm0;
            double _wavePeriodTm10;
            double _waveAngle;
    };
}

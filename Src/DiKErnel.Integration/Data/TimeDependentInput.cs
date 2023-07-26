// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

namespace DiKErnel.Integration.Data
{
    internal class TimeDependentInput : ITimeDependentInput
    {
        public TimeDependentInput(
                int beginTime,
                int endTime,
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle) {}

    public bool Validate() override;

    public int GetBeginTime() override;

    public int GetEndTime() override;

    public double GetWaterLevel() override;

    public double GetWaveHeightHm0() override;

    public double GetWavePeriodTm10() override;

    public double GetWaveAngle() override;

            private int _beginTime;
            private int _endTime;
            private double _waterLevel;
            private double _waveHeightHm0;
            private double _wavePeriodTm10;
            private double _waveAngle;
    }
}

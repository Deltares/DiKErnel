// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.GpuConsole
{
    public struct TimeDependentGpuInput
    {
        public TimeDependentGpuInput(float beginTime, float endTime, float waterLevel, float waveHeightHm0,
                                     float wavePeriodTm10, float waveDirection)
        {
            BeginTime = beginTime;
            EndTime = endTime;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            WaveDirection = waveDirection;
        }

        public float BeginTime { get; }

        public float EndTime { get; }

        public float WaterLevel { get; }

        public float WaveHeightHm0 { get; }

        public float WavePeriodTm10 { get; }

        public float WaveDirection { get; }
    }
}
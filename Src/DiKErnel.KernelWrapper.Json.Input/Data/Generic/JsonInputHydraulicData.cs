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

using System.Collections.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    public class JsonInputHydraulicData
    {
        public JsonInputHydraulicData(
            IEnumerable<double> waterLevels,
            IEnumerable<double> waveHeightsHm0,
            IEnumerable<double> wavePeriodsTm10,
            IEnumerable<double> waveAngles)
        {
            WaterLevels = waterLevels;
            WaveHeightsHm0 = waveHeightsHm0;
            WavePeriodsTm10 = wavePeriodsTm10;
            WaveAngles = waveAngles;
        }

        [JsonProperty(JsonInputDefinitions.WATER_LEVELS)]
        public IEnumerable<double> WaterLevels { get; }
        
        [JsonProperty(JsonInputDefinitions.WAVE_HEIGHTS_HM0)]
        public IEnumerable<double> WaveHeightsHm0 { get; }
        
        [JsonProperty(JsonInputDefinitions.WAVE_PERIODS_TM10)]
        public IEnumerable<double> WavePeriodsTm10 { get; }
        
        [JsonProperty(JsonInputDefinitions.WAVE_ANGLES)]
        public IEnumerable<double> WaveAngles { get; }
    }
}
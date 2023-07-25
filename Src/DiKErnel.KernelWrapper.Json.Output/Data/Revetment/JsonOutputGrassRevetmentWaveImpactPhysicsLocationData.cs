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
using DiKErnel.KernelWrapper.Json.Output.Data.Definitions;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Output.Data.Revetment
{
    internal class JsonOutputGrassRevetmentWaveImpactPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        public JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(IReadOnlyList<double> incrementDamage, double z,
                                                                     IReadOnlyList<bool> loadingRevetment,
                                                                     IReadOnlyList<double> upperLimitLoading,
                                                                     IReadOnlyList<double> lowerLimitLoading,
                                                                     IReadOnlyList<double?> minimumWaveHeight,
                                                                     IReadOnlyList<double?> maximumWaveHeight,
                                                                     IReadOnlyList<double?> waveAngleImpact,
                                                                     IReadOnlyList<double?> waveHeightImpact) : base(incrementDamage)
        {
            Z = z;
            LoadingRevetment = loadingRevetment;
            UpperLimitLoading = upperLimitLoading;
            LowerLimitLoading = lowerLimitLoading;
            MinimumWaveHeight = minimumWaveHeight;
            MaximumWaveHeight = maximumWaveHeight;
            WaveAngleImpact = waveAngleImpact;
            WaveHeightImpact = waveHeightImpact;
        }

        [JsonProperty(JsonOutputDefinitions.Z)]
        public double Z { get; }

        [JsonProperty(JsonOutputDefinitions.HYDRAULIC_LOAD)]
        public IReadOnlyList<bool> LoadingRevetment { get; }

        [JsonProperty(JsonOutputDefinitions.UPPER_LIMIT_LOADING)]
        public IReadOnlyList<double> UpperLimitLoading { get; }

        [JsonProperty(JsonOutputDefinitions.LOWER_LIMIT_LOADING)]
        public IReadOnlyList<double> LowerLimitLoading { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.MINIMUM_WAVE_HEIGHT)]
        public IReadOnlyList<double?> MinimumWaveHeight { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.MAXIMUM_WAVE_HEIGHT)]
        public IReadOnlyList<double?> MaximumWaveHeight { get; }

        [JsonProperty(JsonOutputDefinitions.WAVE_ANGLE_IMPACT)]
        public IReadOnlyList<double?> WaveAngleImpact { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.WAVE_HEIGHT_IMPACT)]
        public IReadOnlyList<double?> WaveHeightImpact { get; }
    }
}
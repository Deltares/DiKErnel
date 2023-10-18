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

using System.Collections.Generic;
using DiKErnel.KernelWrapper.Json.Output.Data.Definitions;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Output.Data.Revetment
{
    internal class JsonOutputGrassRevetmentWaveImpactPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        public JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(IReadOnlyList<double> incrementDamage, double z,
                                                                     double minimumWaveHeight, double maximumWaveHeight,
                                                                     IReadOnlyList<bool> loadingRevetment,
                                                                     IReadOnlyList<double> upperLimitLoading,
                                                                     IReadOnlyList<double> lowerLimitLoading,
                                                                     IReadOnlyList<double?> waveAngle,
                                                                     IReadOnlyList<double?> waveAngleImpact,
                                                                     IReadOnlyList<double?> waveHeightImpact) : base(incrementDamage)
        {
            Z = z;
            MinimumWaveHeight = minimumWaveHeight;
            MaximumWaveHeight = maximumWaveHeight;
            LoadingRevetment = loadingRevetment;
            UpperLimitLoading = upperLimitLoading;
            LowerLimitLoading = lowerLimitLoading;
            WaveAngle = waveAngle;
            WaveAngleImpact = waveAngleImpact;
            WaveHeightImpact = waveHeightImpact;
        }

        [JsonProperty(JsonOutputDefinitions.Z, Order = -2)]
        public double Z { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.MinimumWaveHeight, Order = -2)]
        public double MinimumWaveHeight { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.MaximumWaveHeight, Order = -2)]
        public double MaximumWaveHeight { get; }

        [JsonProperty(JsonOutputDefinitions.HydraulicLoad)]
        public IReadOnlyList<bool> LoadingRevetment { get; }

        [JsonProperty(JsonOutputDefinitions.UpperLimitLoading)]
        public IReadOnlyList<double> UpperLimitLoading { get; }

        [JsonProperty(JsonOutputDefinitions.LowerLimitLoading)]
        public IReadOnlyList<double> LowerLimitLoading { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngle)]
        public IReadOnlyList<double?> WaveAngle { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngleImpact)]
        public IReadOnlyList<double?> WaveAngleImpact { get; }

        [JsonProperty(JsonOutputGrassRevetmentWaveImpactDefinitions.WaveHeightImpact)]
        public IReadOnlyList<double?> WaveHeightImpact { get; }
    }
}
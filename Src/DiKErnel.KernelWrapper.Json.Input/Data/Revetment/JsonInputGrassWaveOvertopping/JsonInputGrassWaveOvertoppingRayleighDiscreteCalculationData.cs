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
using DiKErnel.KernelWrapper.Json.Input.Data.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrass;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveOvertopping
{
    internal class JsonInputGrassWaveOvertoppingRayleighDiscreteCalculationData : JsonInputCalculationData
    {
        [JsonProperty(JsonInputDefinitions.TopLayers)]
        public IReadOnlyList<JsonInputGrassCumulativeOverloadTopLayerData> TopLayerData { get; private set; }

        [JsonProperty(JsonInputGrassWaveOvertoppingRayleighDiscreteDefinitions.DikeHeight)]
        public double? DikeHeight { get; private set; }

        [JsonProperty(JsonInputGrassWaveOvertoppingRayleighDiscreteDefinitions.AccelerationAlphaA)]
        public JsonInputGrassWaveOvertoppingRayleighDiscreteAccelerationAlphaAData AccelerationAlphaAData { get; private set; }

        [JsonProperty(JsonInputGrassDefinitions.FixedNumberOfWaves)]
        public int? FixedNumberOfWaves { get; private set; }

        [JsonProperty(JsonInputGrassWaveOvertoppingRayleighDiscreteDefinitions.FrontVelocityCwo)]
        public double? FrontVelocity { get; private set; }

        [JsonProperty(JsonInputDefinitions.FactorCtm)]
        public double? FactorCtm { get; private set; }
    }
}
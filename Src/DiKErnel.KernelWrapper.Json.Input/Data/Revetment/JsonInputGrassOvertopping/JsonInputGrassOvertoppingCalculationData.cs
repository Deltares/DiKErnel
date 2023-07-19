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
using DiKErnel.KernelWrapper.Json.Input.Data.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassOvertopping
{
    internal class JsonInputGrassOvertoppingCalculationData : JsonInputCalculationData
    {
        [JsonProperty(JsonInputDefinitions.TOP_LAYERS)]
        public IReadOnlyList<JsonInputGrassCumulativeOverloadTopLayerData> TopLayerDefinitionData { get; private set; }

        [JsonProperty(JsonInputGrassOvertoppingDefinitions.DIKE_HEIGHT)]
        public double DikeHeight { get; set; }

        [JsonProperty(JsonInputGrassOvertoppingDefinitions.ACCELERATION_ALPHA_A)]
        public JsonInputGrassOvertoppingCalculationAccelerationAlphaAData AccelerationAlphaAData { get; set; }

        [JsonProperty(JsonInputGrassRevetmentDefinitions.FIXED_NUMBER_OF_WAVES)]
        public int FixedNumberOfWaves { get; set; }

        [JsonProperty(JsonInputGrassOvertoppingDefinitions.FRONT_VELOCITY_CWO)]
        public double FrontVelocity { get; set; }

        [JsonProperty(JsonInputDefinitions.FACTOR_CTM)]
        public double FactorCtm { get; set; }
    }
}
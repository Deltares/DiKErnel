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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup
{
    public class JsonInputGrassWaveRunupCalculationDefinitionData : JsonInputCalculationDefinitionData
    {
        public JsonInputGrassWaveRunupCalculationDefinitionData(
            double failureNumber,
            JsonInputGrassWaveRunupCalculationProtocolData calculationProtocolData,
            IReadOnlyDictionary<JsonInputGrassRevetmentTopLayerType, JsonInputGrassCumulativeOverloadTopLayerDefinitionData>
                topLayerDefinitionData
        ) : base(failureNumber)
        {
            CalculationProtocolData = calculationProtocolData;
            TopLayerDefinitionData = topLayerDefinitionData;
        }

        [JsonProperty(JsonInputGrassWaveRunupDefinitions.CALCULATION_PROTOCOL)]
        public JsonInputGrassWaveRunupCalculationProtocolData CalculationProtocolData { get; }
        
        [JsonProperty(JsonInputDefinitions.TYPE_TOP_LAYER)]
        public IReadOnlyDictionary<JsonInputGrassRevetmentTopLayerType, JsonInputGrassCumulativeOverloadTopLayerDefinitionData> TopLayerDefinitionData { get; }

        [JsonProperty(JsonInputDefinitions.FACTOR_CTM)]
        public double FactorCtm { get; set; }
        
        [JsonProperty(JsonInputDefinitions.A_COEFFICIENT)]
        public double RepresentativeWaveRunup2Pa { get; set; }
        
        [JsonProperty(JsonInputDefinitions.B_COEFFICIENT)]
        public double RepresentativeWaveRunup2Pb { get; set; }
        
        [JsonProperty(JsonInputDefinitions.C_COEFFICIENT)]
        public double RepresentativeWaveRunup2Pc { get; set; }
        
        [JsonProperty(JsonInputGrassWaveRunupDefinitions.A_BETA)]
        public double WaveAngleImpactABeta { get; set; }
        
        [JsonProperty(JsonInputDefinitions.BETA_MAX)]
        public double WaveAngleImpactBetaMax { get; set; }
    }
}
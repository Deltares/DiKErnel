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

using System.Collections.ObjectModel;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStone
{
    public class JsonInputNaturalStoneCalculationDefinitionData : JsonInputCalculationDefinitionData
    {
        public JsonInputNaturalStoneCalculationDefinitionData(
            double failureNumber,
            ReadOnlyDictionary<JsonInputNaturalStoneRevetmentTopLayerType, JsonInputNaturalStoneTopLayerDefinitionData>
                topLayerDefinitionData
        ) : base(failureNumber)
        {
            TopLayerDefinitionData = topLayerDefinitionData;
        }

        [JsonProperty(JsonInputDefinitions.TYPE_TOP_LAYER)]
        public ReadOnlyDictionary<JsonInputNaturalStoneRevetmentTopLayerType, JsonInputNaturalStoneTopLayerDefinitionData>
            TopLayerDefinitionData { get; private set; }

        [JsonProperty(JsonInputNaturalStoneDefinitions.SLOPE_UPPER_LEVEL)]
        public double SlopeUpperLevel { get; set; }
        
        [JsonProperty(JsonInputNaturalStoneDefinitions.SLOPE_LOWER_LEVEL)]
        public double SlopeLowerLevel { get; set; }

        [JsonProperty(JsonInputDefinitions.A_COEFFICIENT)]
        public double UpperLimitLoadingA { get; set; }
        
        [JsonProperty(JsonInputDefinitions.B_COEFFICIENT)]
        public double UpperLimitLoadingB { get; set; }
        
        [JsonProperty(JsonInputDefinitions.C_COEFFICIENT)]
        public double UpperLimitLoadingC { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.A_COEFFICIENT)]
        // public double LowerLimitLoadingA { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.B_COEFFICIENT)]
        // public double LowerLimitLoadingB { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.C_COEFFICIENT)]
        // public double LowerLimitLoadingC { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.A_COEFFICIENT)]
        // public double DistanceMaximumWaveElevationA { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.B_COEFFICIENT)]
        // public double DistanceMaximumWaveElevationB { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.A_COEFFICIENT)]
        // public double NormativeWidthOfWaveImpactA { get; set; }
        //
        // [JsonProperty(JsonInputDefinitions.B_COEFFICIENT)]
        // public double NormativeWidthOfWaveImpactB { get; set; }
        // todo find out how to generate multiple types from a single data object
        [JsonProperty(JsonInputDefinitions.BETA_MAX)]
        public double WaveAngleImpactBetaMax { get; set; }
    }
}
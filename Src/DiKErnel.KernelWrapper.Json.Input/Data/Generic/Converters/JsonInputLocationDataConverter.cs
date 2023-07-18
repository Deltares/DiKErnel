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

using System;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputAsphaltWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassOvertopping;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStone;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic.Converters
{
    public class JsonInputLocationDataConverter : JsonConverter<JsonInputLocationData>
    {
        public override void WriteJson(JsonWriter writer, JsonInputLocationData value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override JsonInputLocationData ReadJson(JsonReader reader, Type objectType, JsonInputLocationData existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            JObject jo = JObject.Load(reader);

            string typeDiscriminator = jo[JsonInputDefinitions.CALCULATION_METHOD_TYPE].ToString();
            JsonInputLocationData jsonInputCalculationDefinitionData = typeDiscriminator switch
            {
                JsonInputDefinitions.CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT => jo.ToObject<JsonInputAsphaltWaveImpactLocationData>()!,
                JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_OVERTOPPING => jo.ToObject<JsonInputGrassOvertoppingLocationData>()!,
                JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT => jo.ToObject<JsonInputGrassWaveImpactLocationData>()!,
                JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP => jo.ToObject<JsonInputGrassWaveRunupLocationData>()!,
                JsonInputDefinitions.CALCULATION_METHOD_TYPE_NATURAL_STONE => jo.ToObject<JsonInputNaturalStoneLocationData>()!,
                _ => null
            };

            return jsonInputCalculationDefinitionData;
        }
    }
}
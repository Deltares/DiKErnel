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

using System;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputAsphaltWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassOvertopping;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStoneWaveImpact;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic.Converters
{
    internal class JsonInputLocationDataConverter : JsonConverter<JsonInputLocationData>
    {
        public override bool CanWrite => false;

        public override void WriteJson(JsonWriter writer, JsonInputLocationData value, JsonSerializer serializer)
        {
            throw new NotSupportedException();
        }

        public override JsonInputLocationData ReadJson(JsonReader reader, Type objectType, JsonInputLocationData existingValue,
                                                       bool hasExistingValue, JsonSerializer serializer)
        {
            JObject calculationData = JObject.Load(reader);

            JsonInputCalculationType typeDiscriminator = calculationData.ToObject<JsonInputLocationData>().CalculationMethodType;

            JsonInputLocationData jsonInputCalculationDefinitionData = typeDiscriminator switch
            {
                JsonInputCalculationType.AsphaltWaveImpact =>
                    calculationData.ToObject<JsonInputAsphaltWaveImpactLocationData>(),
                JsonInputCalculationType.GrassOvertopping =>
                    calculationData.ToObject<JsonInputGrassOvertoppingRayleighDiscreteLocationData>(),
                JsonInputCalculationType.GrassWaveImpact =>
                    calculationData.ToObject<JsonInputGrassWaveImpactLocationData>(),
                JsonInputCalculationType.GrassWaveRunup =>
                    calculationData.ToObject<JsonInputGrassWaveRunupLocationData>(),
                JsonInputCalculationType.NaturalStone =>
                    calculationData.ToObject<JsonInputNaturalStoneLocationData>(),
                _ => null
            };

            return jsonInputCalculationDefinitionData;
        }
    }
}
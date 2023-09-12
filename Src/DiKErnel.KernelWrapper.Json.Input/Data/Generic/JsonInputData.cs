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
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    internal class JsonInputData
    {
        [JsonProperty(JsonInputDefinitions.TIME)]
        public IReadOnlyList<int> Times { get; private set; }

        [JsonProperty(JsonInputDefinitions.HYDRAULIC_LOADS)]
        public JsonInputHydraulicData HydraulicData { get; private set; }

        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE)]
        public JsonInputDikeProfileData DikeProfileData { get; private set; }

        [JsonProperty(JsonInputDefinitions.LOCATIONS)]
        public IReadOnlyList<JsonInputLocationData> LocationData { get; private set; }

        [JsonProperty(JsonInputDefinitions.CALCULATION_METHODS)]
        public IReadOnlyList<JsonInputCalculationData> CalculationDefinitionData { get; private set; }
    }
}
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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStone
{
    internal class JsonInputNaturalStoneCalculationData : JsonInputCalculationData
    {
        [JsonProperty(JsonInputDefinitions.TOP_LAYERS)]
        public IReadOnlyList<JsonInputNaturalStoneTopLayerData> TopLayerDefinitionData { get; private set; }

        [JsonProperty(JsonInputDefinitions.LOADING_AREA)]
        public JsonInputNaturalStoneCalculationLoadingAreaData LoadingArea { get; private set; }

        [JsonProperty(JsonInputNaturalStoneDefinitions.SLOPE)]
        public JsonInputNaturalStoneCalculationSlopeData Slope { get; private set; }

        [JsonProperty(JsonInputNaturalStoneDefinitions.DISTANCE_MAXIMUM_WAVE_ELEVATION)]
        public JsonInputNaturalStoneCalculationMaximumWaveElevationData DistanceMaximumWaveElevation { get; private set; }

        [JsonProperty(JsonInputNaturalStoneDefinitions.NORMATIVE_WIDTH_OF_WAVE_IMPACT)]
        public JsonInputNaturalStoneCalculationNormativeWidthWaveImpactData NormativeWidthOfWaveImpact { get; private set; }

        [JsonProperty(JsonInputDefinitions.WAVE_ANGLE_IMPACT)]
        public JsonInputNaturalStoneCalculationWaveImpactData WaveAngleImpact { get; private set; }
    }
}
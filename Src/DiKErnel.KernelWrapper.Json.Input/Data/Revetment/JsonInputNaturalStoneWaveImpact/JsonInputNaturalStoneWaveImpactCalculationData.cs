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
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStoneWaveImpact
{
    internal class JsonInputNaturalStoneWaveImpactCalculationData : JsonInputCalculationData
    {
        [JsonProperty(JsonInputDefinitions.TopLayers)]
        public IReadOnlyList<JsonInputNaturalStoneWaveImpactTopLayerData> TopLayerData { get; private set; }

        [JsonProperty(JsonInputDefinitions.LoadingArea)]
        public JsonInputNaturalStoneWaveImpactLoadingAreaData LoadingAreaData { get; private set; }

        [JsonProperty(JsonInputNaturalStoneWaveImpactDefinitions.Slope)]
        public JsonInputNaturalStoneWaveImpactSlopeData SlopeData { get; private set; }

        [JsonProperty(JsonInputNaturalStoneWaveImpactDefinitions.DistanceMaximumWaveElevation)]
        public JsonInputNaturalStoneWaveImpactMaximumWaveElevationData MaximumWaveElevationData { get; private set; }

        [JsonProperty(JsonInputNaturalStoneWaveImpactDefinitions.NormativeWidthOfWaveImpact)]
        public JsonInputNaturalStoneWaveImpactNormativeWidthData NormativeWidthData { get; private set; }

        [JsonProperty(JsonInputDefinitions.WaveAngleImpact)]
        public JsonInputNaturalStoneWaveImpactWaveAngleData WaveAngleData { get; private set; }
    }
}
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
    internal class JsonInputDikeProfileData
    {
        [JsonProperty(JsonInputDefinitions.DIKE_ORIENTATION)]
        public double DikeOrientation { get; private set; }
        
        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE_POINTS_X)]
        public IReadOnlyList<double> XLocations { get; private set; }

        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE_POINTS_Z)]
        public IReadOnlyList<double> ZLocations { get; private set; }

        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE_ROUGHNESS_COEFFICIENTS)]
        public IReadOnlyList<double> RoughnessCoefficients { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_OUTER_TOE)]
        public double? OuterToe { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM)]
        public double? CrestOuterBerm { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM)]
        public double? NotchOuterBerm { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_OUTER_CREST)]
        public double? OuterCrest { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_INNER_CREST)]
        public double? InnerCrest { get; private set; }

        [JsonProperty(JsonInputDefinitions.CHARACTERISTIC_POINT_TYPE_INNER_TOE)]
        public double? InnerToe { get; private set; }
    }
}
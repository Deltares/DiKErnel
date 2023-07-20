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
using DiKErnel.KernelWrapper.Json.Output.Data.Definitions;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Output.Data.Revetment
{
    internal class JsonOutputGrassRevetmentOvertoppingPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        [JsonProperty(JsonOutputGrassRevetmentDefinitions.VERTICAL_DISTANCE_WATER_LEVEL_ELEVATION)]
        public IReadOnlyList<double> VerticalDistanceWaterLevelElevation { get; set; }

        [JsonProperty(JsonOutputGrassRevetmentDefinitions.REPRESENTATIVE_WAVE_RUNUP_2P, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> RepresentativeWaveRunup2P { get; set; }

        [JsonProperty(JsonOutputGrassRevetmentDefinitions.CUMULATIVE_OVERLOAD, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> CumulativeOverload { get; set; }
    }
}
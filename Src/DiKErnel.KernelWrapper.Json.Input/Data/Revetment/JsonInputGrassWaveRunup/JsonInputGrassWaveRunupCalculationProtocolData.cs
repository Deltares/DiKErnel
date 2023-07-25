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

using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup
{
    internal class JsonInputGrassWaveRunupCalculationProtocolData
    {
        [JsonProperty(JsonInputGrassWaveRunupDefinitions.CALCULATION_PROTOCOL_TYPE)]
        public JsonInputGrassWaveRunupCalculationProtocolType CalculationProtocolType { get; private set; }

        [JsonProperty(JsonInputGrassRevetmentDefinitions.FIXED_NUMBER_OF_WAVES)]
        public int? FixedNumberOfWaves { get; private set; }

        [JsonProperty(JsonInputGrassWaveRunupDefinitions.FRONT_VELOCITY)]
        public double? FrontVelocity { get; private set; }
    }
}
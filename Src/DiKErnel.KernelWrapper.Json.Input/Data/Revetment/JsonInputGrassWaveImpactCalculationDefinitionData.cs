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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment
{
    internal class JsonInputGrassWaveImpactCalculationDefinitionData : JsonInputCalculationDefinitionData
    {
        public JsonInputGrassWaveImpactCalculationDefinitionData(
            double failureNumber,
            IReadOnlyDictionary<JsonInputGrassRevetmentTopLayerType, JsonInputGrassWaveImpactTopLayerDefinitionData>
                topLayerDefinitionData
        ) : base(failureNumber)
        {
            TopLayerDefinitionData = topLayerDefinitionData;
        }

        public IReadOnlyDictionary<JsonInputGrassRevetmentTopLayerType, JsonInputGrassWaveImpactTopLayerDefinitionData> TopLayerDefinitionData { get; }

        public double Temax { get; set; }
        public double Temin { get; set; }
        public double WaveAngleImpactN { get; set; }
        public double WaveAngleImpactQ { get; set; }
        public double WaveAngleImpactR { get; set; }
        public double UpperLimitLoading { get; set; }
        public double LowerLimitLoading { get; set; }
    }
}
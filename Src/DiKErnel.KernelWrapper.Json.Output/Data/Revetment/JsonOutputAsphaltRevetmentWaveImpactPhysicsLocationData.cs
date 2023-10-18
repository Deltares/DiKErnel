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
using DiKErnel.KernelWrapper.Json.Output.Data.Definitions;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Output.Data.Revetment
{
    internal class JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        public JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(IReadOnlyList<double> incrementDamage, double z, double outerSlope,
                                                                       double logFlexuralStrength, double stiffnessRelation,
                                                                       double computationalThickness, double equivalentElasticModulus,
                                                                       IReadOnlyList<double> maximumPeakStress,
                                                                       IReadOnlyList<double> averageNumberOfWaves)
            : base(incrementDamage)
        {
            Z = z;
            OuterSlope = outerSlope;
            LogFlexuralStrength = logFlexuralStrength;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            EquivalentElasticModulus = equivalentElasticModulus;
            MaximumPeakStress = maximumPeakStress;
            AverageNumberOfWaves = averageNumberOfWaves;
        }

        [JsonProperty(JsonOutputDefinitions.Z, Order = -2)]
        public double Z { get; }

        [JsonProperty(JsonOutputDefinitions.OuterSlope, Order = -2)]
        public double OuterSlope { get; }

        [JsonProperty(JsonOutputAsphaltRevetmentWaveImpactDefinitions.LogFlexuralStrength, Order = -2)]
        public double LogFlexuralStrength { get; }

        [JsonProperty(JsonOutputAsphaltRevetmentWaveImpactDefinitions.StiffnessRelation, Order = -2)]
        public double StiffnessRelation { get; }

        [JsonProperty(JsonOutputAsphaltRevetmentWaveImpactDefinitions.ComputationalThickness, Order = -2)]
        public double ComputationalThickness { get; }

        [JsonProperty(JsonOutputAsphaltRevetmentWaveImpactDefinitions.EquivalentElasticModulus, Order = -2)]
        public double EquivalentElasticModulus { get; }

        [JsonProperty(JsonOutputAsphaltRevetmentWaveImpactDefinitions.MaximumPeakStress)]
        public IReadOnlyList<double> MaximumPeakStress { get; }

        [JsonProperty(JsonOutputDefinitions.AverageNumberOfWaves)]
        public IReadOnlyList<double> AverageNumberOfWaves { get; }
    }
}
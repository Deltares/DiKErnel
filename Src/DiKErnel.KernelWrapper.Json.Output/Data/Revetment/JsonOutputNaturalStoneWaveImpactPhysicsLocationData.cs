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
    internal class JsonOutputNaturalStoneWaveImpactPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        public JsonOutputNaturalStoneWaveImpactPhysicsLocationData(IReadOnlyList<double> incrementDamage,
                                                                   double z, double resistance,
                                                                   IReadOnlyList<double> outerSlope,
                                                                   IReadOnlyList<double> slopeUpperLevel,
                                                                   IReadOnlyList<double> slopeUpperPosition,
                                                                   IReadOnlyList<double> slopeLowerLevel,
                                                                   IReadOnlyList<double> slopeLowerPosition,
                                                                   IReadOnlyList<bool> loadingRevetment,
                                                                   IReadOnlyList<double> surfSimilarityParameter,
                                                                   IReadOnlyList<double> waveSteepnessDeepWater,
                                                                   IReadOnlyList<double> upperLimitLoading,
                                                                   IReadOnlyList<double> lowerLimitLoading,
                                                                   IReadOnlyList<double> depthMaximumWaveLoad,
                                                                   IReadOnlyList<double> distanceMaximumWaveElevation,
                                                                   IReadOnlyList<double> normativeWidthOfWaveImpact,
                                                                   IReadOnlyList<double?> hydraulicLoad,
                                                                   IReadOnlyList<double?> waveAngle,
                                                                   IReadOnlyList<double?> waveAngleImpact,
                                                                   IReadOnlyList<double?> referenceTimeDegradation,
                                                                   IReadOnlyList<double?> referenceDegradation)
            : base(incrementDamage)
        {
            Z = z;
            Resistance = resistance;
            OuterSlope = outerSlope;
            SlopeUpperLevel = slopeUpperLevel;
            SlopeUpperPosition = slopeUpperPosition;
            SlopeLowerLevel = slopeLowerLevel;
            SlopeLowerPosition = slopeLowerPosition;
            LoadingRevetment = loadingRevetment;
            SurfSimilarityParameter = surfSimilarityParameter;
            WaveSteepnessDeepWater = waveSteepnessDeepWater;
            UpperLimitLoading = upperLimitLoading;
            LowerLimitLoading = lowerLimitLoading;
            DepthMaximumWaveLoad = depthMaximumWaveLoad;
            DistanceMaximumWaveElevation = distanceMaximumWaveElevation;
            NormativeWidthOfWaveImpact = normativeWidthOfWaveImpact;
            HydraulicLoad = hydraulicLoad;
            WaveAngle = waveAngle;
            WaveAngleImpact = waveAngleImpact;
            ReferenceTimeDegradation = referenceTimeDegradation;
            ReferenceDegradation = referenceDegradation;
        }

        [JsonProperty(JsonOutputDefinitions.Z, Order = -2)]
        public double Z { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.Resistance, Order = -2)]
        public double Resistance { get; }

        [JsonProperty(JsonOutputDefinitions.OuterSlope)]
        public IReadOnlyList<double> OuterSlope { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.SlopeUpperLevel)]
        public IReadOnlyList<double> SlopeUpperLevel { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.SlopeUpperPosition)]
        public IReadOnlyList<double> SlopeUpperPosition { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.SlopeLowerLevel)]
        public IReadOnlyList<double> SlopeLowerLevel { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.SlopeLowerPosition)]
        public IReadOnlyList<double> SlopeLowerPosition { get; }

        [JsonProperty(JsonOutputDefinitions.HydraulicLoad)]
        public IReadOnlyList<bool> LoadingRevetment { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.SurfSimilarityParameter)]
        public IReadOnlyList<double> SurfSimilarityParameter { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.WaveSteepnessDeepWater)]
        public IReadOnlyList<double> WaveSteepnessDeepWater { get; }

        [JsonProperty(JsonOutputDefinitions.UpperLimitLoading)]
        public IReadOnlyList<double> UpperLimitLoading { get; }

        [JsonProperty(JsonOutputDefinitions.LowerLimitLoading)]
        public IReadOnlyList<double> LowerLimitLoading { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.DepthMaximumWaveLoad)]
        public IReadOnlyList<double> DepthMaximumWaveLoad { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.DistanceMaximumWaveElevation)]
        public IReadOnlyList<double> DistanceMaximumWaveElevation { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.NormativeWidthWaveImpact)]
        public IReadOnlyList<double> NormativeWidthOfWaveImpact { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.HydraulicLoad)]
        public IReadOnlyList<double?> HydraulicLoad { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngle)]
        public IReadOnlyList<double?> WaveAngle { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngleImpact)]
        public IReadOnlyList<double?> WaveAngleImpact { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.ReferenceTimeDegradation)]
        public IReadOnlyList<double?> ReferenceTimeDegradation { get; }

        [JsonProperty(JsonOutputNaturalStoneWaveImpactDefinitions.ReferenceDegradation)]
        public IReadOnlyList<double?> ReferenceDegradation { get; }
    }
}
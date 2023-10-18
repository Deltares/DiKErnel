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
    internal class JsonOutputNaturalStoneRevetmentPhysicsLocationData : JsonOutputPhysicsLocationData
    {
        public JsonOutputNaturalStoneRevetmentPhysicsLocationData(IReadOnlyList<double> incrementDamage,
                                                                  double z,
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
                                                                  IReadOnlyList<double?> resistance,
                                                                  IReadOnlyList<double?> referenceTimeDegradation,
                                                                  IReadOnlyList<double?> referenceDegradation) : base(incrementDamage)
        {
            Z = z;
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
            Resistance = resistance;
            ReferenceTimeDegradation = referenceTimeDegradation;
            ReferenceDegradation = referenceDegradation;
        }

        [JsonProperty(JsonOutputDefinitions.Z, Order = -2)]
        public double Z { get; }

        [JsonProperty(JsonOutputDefinitions.OuterSlope)]
        public IReadOnlyList<double> OuterSlope { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SlopeUpperLevel)]
        public IReadOnlyList<double> SlopeUpperLevel { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SlopeUpperPosition)]
        public IReadOnlyList<double> SlopeUpperPosition { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SlopeLowerLevel)]
        public IReadOnlyList<double> SlopeLowerLevel { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SlopeLowerPosition)]
        public IReadOnlyList<double> SlopeLowerPosition { get; }

        [JsonProperty(JsonOutputDefinitions.HydraulicLoad)]
        public IReadOnlyList<bool> LoadingRevetment { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SurfSimilarityParameter)]
        public IReadOnlyList<double> SurfSimilarityParameter { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.WaveSteepnessDeepWater)]
        public IReadOnlyList<double> WaveSteepnessDeepWater { get; }

        [JsonProperty(JsonOutputDefinitions.UpperLimitLoading)]
        public IReadOnlyList<double> UpperLimitLoading { get; }

        [JsonProperty(JsonOutputDefinitions.LowerLimitLoading)]
        public IReadOnlyList<double> LowerLimitLoading { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.DepthMaximumWaveLoad)]
        public IReadOnlyList<double> DepthMaximumWaveLoad { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.DistanceMaximumWaveElevation)]
        public IReadOnlyList<double> DistanceMaximumWaveElevation { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.NormativeWidthWaveImpact)]
        public IReadOnlyList<double> NormativeWidthOfWaveImpact { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.HydraulicLoad)]
        public IReadOnlyList<double?> HydraulicLoad { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngle)]
        public IReadOnlyList<double?> WaveAngle { get; }

        [JsonProperty(JsonOutputDefinitions.WaveAngleImpact)]
        public IReadOnlyList<double?> WaveAngleImpact { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.Resistance)]
        public IReadOnlyList<double?> Resistance { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.ReferenceTimeDegradation)]
        public IReadOnlyList<double?> ReferenceTimeDegradation { get; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.ReferenceDegradation)]
        public IReadOnlyList<double?> ReferenceDegradation { get; }
    }
}
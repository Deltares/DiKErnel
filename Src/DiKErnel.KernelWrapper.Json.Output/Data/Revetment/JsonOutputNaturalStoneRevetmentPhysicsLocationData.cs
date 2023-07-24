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
                                                                  IReadOnlyList<double> hydraulicLoad,
                                                                  IReadOnlyList<double> waveAngleImpact,
                                                                  IReadOnlyList<double> resistance,
                                                                  IReadOnlyList<double> referenceTimeDegradation,
                                                                  IReadOnlyList<double> referenceDegradation) : base(incrementDamage)
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
            WaveAngleImpact = waveAngleImpact;
            Resistance = resistance;
            ReferenceTimeDegradation = referenceTimeDegradation;
            ReferenceDegradation = referenceDegradation;
        }

        [JsonProperty(JsonOutputDefinitions.Z)]
        public double Z { get; set; }

        [JsonProperty(JsonOutputDefinitions.OUTER_SLOPE)]
        public IReadOnlyList<double> OuterSlope { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SLOPE_UPPER_LEVEL)]
        public IReadOnlyList<double> SlopeUpperLevel { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SLOPE_UPPER_POSITION)]
        public IReadOnlyList<double> SlopeUpperPosition { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SLOPE_LOWER_LEVEL)]
        public IReadOnlyList<double> SlopeLowerLevel { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SLOPE_LOWER_POSITION)]
        public IReadOnlyList<double> SlopeLowerPosition { get; set; }

        [JsonProperty(JsonOutputDefinitions.HYDRAULIC_LOAD)]
        public IReadOnlyList<bool> LoadingRevetment { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.SURF_SIMILARITY_PARAMETER)]
        public IReadOnlyList<double> SurfSimilarityParameter { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.WAVE_STEEPNESS_DEEP_WATER)]
        public IReadOnlyList<double> WaveSteepnessDeepWater { get; set; }

        [JsonProperty(JsonOutputDefinitions.UPPER_LIMIT_LOADING)]
        public IReadOnlyList<double> UpperLimitLoading { get; set; }

        [JsonProperty(JsonOutputDefinitions.LOWER_LIMIT_LOADING)]
        public IReadOnlyList<double> LowerLimitLoading { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.DEPTH_MAXIMUM_WAVE_LOAD)]
        public IReadOnlyList<double> DepthMaximumWaveLoad { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.DISTANCE_MAXIMUM_WAVE_ELEVATION)]
        public IReadOnlyList<double> DistanceMaximumWaveElevation { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.NORMATIVE_WIDTH_WAVE_IMPACT)]
        public IReadOnlyList<double> NormativeWidthOfWaveImpact { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.HYDRAULIC_LOAD, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> HydraulicLoad { get; set; }

        [JsonProperty(JsonOutputDefinitions.WAVE_ANGLE_IMPACT, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> WaveAngleImpact { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.RESISTANCE, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> Resistance { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.REFERENCE_TIME_DEGRADATION, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> ReferenceTimeDegradation { get; set; }

        [JsonProperty(JsonOutputNaturalStoneRevetmentDefinitions.REFERENCE_DEGRADATION, NullValueHandling = NullValueHandling.Ignore)]
        public IReadOnlyList<double> ReferenceDegradation { get; set; }
    }
}
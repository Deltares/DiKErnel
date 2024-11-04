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

using ILGPU;

namespace DiKErnel.GpuConsole
{
    public struct AsphaltWaveImpactIncrementDamageGpuInput
    {
        public AsphaltWaveImpactIncrementDamageGpuInput(float logFlexuralStrength, float averageNumberOfWaves, float maximumPeakStress,
                                                        float stiffnessRelation, float computationalThickness, float outerSlope,
                                                        ArrayView<float> widthFactorValues, ArrayView<float> widthFactorProbabilities,
                                                        ArrayView<float> depthFactorValues, ArrayView<float> depthFactorProbabilities,
                                                        ArrayView<float> impactFactorValues, ArrayView<float> impactFactorProbabilities,
                                                        float z, float waterLevel, float waveHeightHm0, float fatigueAlpha,
                                                        float fatigueBeta, float impactNumberC)
        {
            LogFlexuralStrength = logFlexuralStrength;
            AverageNumberOfWaves = averageNumberOfWaves;
            MaximumPeakStress = maximumPeakStress;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            OuterSlope = outerSlope;
            WidthFactorValues = widthFactorValues;
            WidthFactorProbabilities = widthFactorProbabilities;
            DepthFactorValues = depthFactorValues;
            DepthFactorProbabilities = depthFactorProbabilities;
            ImpactFactorValues = impactFactorValues;
            ImpactFactorProbabilities = impactFactorProbabilities;
            Z = z;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            FatigueAlpha = fatigueAlpha;
            FatigueBeta = fatigueBeta;
            ImpactNumberC = impactNumberC;
        }

        public float LogFlexuralStrength { get; }

        public float AverageNumberOfWaves { get; }

        public float MaximumPeakStress { get; }

        public float StiffnessRelation { get; }

        public float ComputationalThickness { get; }

        public float OuterSlope { get; }

        public float Z { get; }

        public float WaterLevel { get; }

        public float WaveHeightHm0 { get; }

        public float FatigueAlpha { get; }

        public float FatigueBeta { get; }

        public float ImpactNumberC { get; }

        public ArrayView<float> WidthFactorValues { get; }

        public ArrayView<float> WidthFactorProbabilities { get; }

        public ArrayView<float> DepthFactorValues { get; }

        public ArrayView<float> DepthFactorProbabilities { get; }

        public ArrayView<float> ImpactFactorValues { get; }

        public ArrayView<float> ImpactFactorProbabilities { get; }
    }
}
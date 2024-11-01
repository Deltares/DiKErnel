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

namespace DiKErnel.GpuConsole
{
    public struct AsphaltWaveImpactGpuInput
    {
        public AsphaltWaveImpactGpuInput(float logFlexuralStrength, float stiffnessRelation, float computationalThickness,
                                         float outerSlope, float z, float fatigueAlpha, float fatigueBeta,
                                         float averageNumberOfWavesCtm, float densityOfWater, float impactNumberC)
        {
            LogFlexuralStrength = logFlexuralStrength;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            OuterSlope = outerSlope;
            Z = z;
            FatigueAlpha = fatigueAlpha;
            FatigueBeta = fatigueBeta;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            DensityOfWater = densityOfWater;
            ImpactNumberC = impactNumberC;
        }

        public float LogFlexuralStrength { get; }

        public float StiffnessRelation { get; }

        public float ComputationalThickness { get; }

        public float OuterSlope { get; }

        public float Z { get; }

        public float FatigueAlpha { get; }

        public float FatigueBeta { get; }

        public float AverageNumberOfWavesCtm { get; }

        public float DensityOfWater { get; }

        public float ImpactNumberC { get; }
    }
}
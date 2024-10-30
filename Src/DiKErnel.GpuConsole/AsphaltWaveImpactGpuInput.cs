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
        public AsphaltWaveImpactGpuInput(double logFlexuralStrength, double stiffnessRelation, double computationalThickness,
                                         double outerSlope, double z, double fatigueAlpha, double fatigueBeta,
                                         double averageNumberOfWavesCtm, double densityOfWater, double impactNumberC)
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

        public double LogFlexuralStrength { get; }

        public double StiffnessRelation { get; }

        public double ComputationalThickness { get; }

        public double OuterSlope { get; }

        public double Z { get; }

        public double FatigueAlpha { get; }

        public double FatigueBeta { get; }

        public double AverageNumberOfWavesCtm { get; }

        public double DensityOfWater { get; }

        public double ImpactNumberC { get; }
    }
}
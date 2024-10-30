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

namespace DiKErnel.GpuConsole
{
    public struct AsphaltWaveImpactIncrementDamageGpuInput
    {
        public AsphaltWaveImpactIncrementDamageGpuInput(double logFlexuralStrength, double averageNumberOfWaves, double maximumPeakStress,
                                                        double stiffnessRelation, double computationalThickness, double outerSlope,
                                                        IReadOnlyList<(double, double)> widthFactors,
                                                        IReadOnlyList<(double, double)> depthFactors,
                                                        IReadOnlyList<(double, double)> impactFactors,
                                                        double z, double waterLevel, double waveHeightHm0, double fatigueAlpha,
                                                        double fatigueBeta, double impactNumberC)
        {
            LogFlexuralStrength = logFlexuralStrength;
            AverageNumberOfWaves = averageNumberOfWaves;
            MaximumPeakStress = maximumPeakStress;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            OuterSlope = outerSlope;
            WidthFactors = widthFactors;
            DepthFactors = depthFactors;
            ImpactFactors = impactFactors;
            Z = z;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            FatigueAlpha = fatigueAlpha;
            FatigueBeta = fatigueBeta;
            ImpactNumberC = impactNumberC;
        }

        public double LogFlexuralStrength { get; }

        public double AverageNumberOfWaves { get; }

        public double MaximumPeakStress { get; }

        public double StiffnessRelation { get; }

        public double ComputationalThickness { get; }

        public double OuterSlope { get; }

        public IReadOnlyList<(double, double)> WidthFactors { get; }

        public IReadOnlyList<(double, double)> DepthFactors { get; }

        public IReadOnlyList<(double, double)> ImpactFactors { get; }

        public double Z { get; }

        public double WaterLevel { get; }

        public double WaveHeightHm0 { get; }

        public double FatigueAlpha { get; }

        public double FatigueBeta { get; }

        public double ImpactNumberC { get; }
    }
}
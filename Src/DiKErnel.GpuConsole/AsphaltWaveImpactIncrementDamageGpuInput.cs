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
        public AsphaltWaveImpactIncrementDamageGpuInput(double logFlexuralStrength, double averageNumberOfWaves, double maximumPeakStress,
                                                        double stiffnessRelation, double computationalThickness, double outerSlope,
                                                        ArrayView<double> wfValues,
                                                        ArrayView<double> wfProbabilities,
                                                        ArrayView<double> dfValues,
                                                        ArrayView<double> dfProbabilities,
                                                        ArrayView<double> ifValues,
                                                        ArrayView<double> ifProbabilities,
                                                        double z, double waterLevel, double waveHeightHm0, double fatigueAlpha,
                                                        double fatigueBeta, double impactNumberC)
        {
            LogFlexuralStrength = logFlexuralStrength;
            AverageNumberOfWaves = averageNumberOfWaves;
            MaximumPeakStress = maximumPeakStress;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            OuterSlope = outerSlope;
            WidthFactorValues = wfValues;
            WidthFactorProbabilities = wfProbabilities;
            DepthFactorValues = dfValues;
            DepthFactorProbabilities = dfProbabilities;
            ImpactFactorValues = ifValues;
            ImpactFactorProbabilities = ifProbabilities;
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

        public double Z { get; }

        public double WaterLevel { get; }

        public double WaveHeightHm0 { get; }

        public double FatigueAlpha { get; }

        public double FatigueBeta { get; }

        public double ImpactNumberC { get; }

        public ArrayView<double> WidthFactorValues { get; }

        public ArrayView<double> WidthFactorProbabilities { get; }

        public ArrayView<double> DepthFactorValues { get; }

        public ArrayView<double> DepthFactorProbabilities { get; }

        public ArrayView<double> ImpactFactorValues { get; }

        public ArrayView<double> ImpactFactorProbabilities { get; }
    }
}
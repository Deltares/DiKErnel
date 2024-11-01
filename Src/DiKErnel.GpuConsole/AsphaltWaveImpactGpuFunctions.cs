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

using System;

namespace DiKErnel.GpuConsole
{
    public static class AsphaltWaveImpactGpuFunctions
    {
        private static readonly float bendingStressPartial1 = MathF.Pow(10, -99);

        public static float IncrementDamage(AsphaltWaveImpactIncrementDamageGpuInput input)
        {
            float result = 0;

            float sinA = MathF.Sin(MathF.Atan(input.OuterSlope));

            float bendingStressPartial2 = -3 * input.MaximumPeakStress /
                                          (4 * MathF.Pow(input.StiffnessRelation, 2) * MathF.Pow(input.ComputationalThickness, 2));

            for (var i = 0; i < input.WidthFactorValues.Length; i++)
            {
                float relativeWidthWaveImpact = RelativeWidthWaveImpact(input.StiffnessRelation, input.WidthFactorValues[i],
                                                                        input.WaveHeightHm0);

                float depthFactorAccumulation = DepthFactorAccumulation(input, relativeWidthWaveImpact, sinA, bendingStressPartial2);

                result += input.WidthFactorProbabilities[i] * depthFactorAccumulation;
            }

            return result;
        }

        private static float DepthFactorAccumulation(AsphaltWaveImpactIncrementDamageGpuInput input, float relativeWidthWaveImpact,
                                                     float sinA, float bendingStressPartial2)
        {
            float result = 0;

            float sinRelativeWidthWaveImpact = MathF.Sin(relativeWidthWaveImpact);
            float cosRelativeWidthWaveImpact = MathF.Cos(relativeWidthWaveImpact);
            float expNegativeRelativeWidthWaveImpact = MathF.Exp(-relativeWidthWaveImpact);

            for (var i = 0; i < input.DepthFactorValues.Length; i++)
            {
                float bendingStress = BendingStress(input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact,
                                                    expNegativeRelativeWidthWaveImpact, sinA, input.DepthFactorValues[i],
                                                    bendingStressPartial2);

                float impactFactorAccumulation = ImpactFactorAccumulation(input, bendingStress);

                result += input.DepthFactorProbabilities[i] * impactFactorAccumulation;
            }

            return result;
        }

        private static float ImpactFactorAccumulation(AsphaltWaveImpactIncrementDamageGpuInput input, float bendingStress)
        {
            float result = 0;

            for (var i = 0; i < input.ImpactFactorValues.Length; i++)
            {
                float fatigue = Fatigue(input, bendingStress, ImpactNumber(input.OuterSlope, input.ImpactFactorValues[i],
                                                                           input.ImpactNumberC));

                result += input.ImpactFactorProbabilities[i] * input.AverageNumberOfWaves * fatigue;
            }

            return result;
        }

        private static float Fatigue(AsphaltWaveImpactIncrementDamageGpuInput input, float bendingStress, float impactNumber)
        {
            float logTension = LogTension(bendingStress, impactNumber);

            return MathF.Pow(10, -input.FatigueBeta * MathF.Pow(MathF.Max(0, input.LogFlexuralStrength - logTension), input.FatigueAlpha));
        }

        private static float LogTension(float bendingStress, float impactNumber)
        {
            return MathF.Log10(impactNumber * bendingStress);
        }

        private static float ImpactNumber(float outerSlope, float impactFactorValue, float impactNumberC)
        {
            return 4 * impactNumberC * outerSlope * impactFactorValue;
        }

        private static float BendingStress(AsphaltWaveImpactIncrementDamageGpuInput input, float relativeWidthWaveImpact,
                                           float sinRelativeWidthWaveImpact, float cosRelativeWidthWaveImpact,
                                           float expNegativeRelativeWidthWaveImpact, float sinA, float depthFactorValue,
                                           float bendingStressPartial2)
        {
            float spatialDistributionBendingStress = SpatialDistributionBendingStress(
                input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact, expNegativeRelativeWidthWaveImpact,
                sinA, depthFactorValue);

            return MathF.Max(bendingStressPartial1, bendingStressPartial2 * spatialDistributionBendingStress);
        }

        private static float SpatialDistributionBendingStress(AsphaltWaveImpactIncrementDamageGpuInput input,
                                                              float relativeWidthWaveImpact, float sinRelativeWidthWaveImpact,
                                                              float cosRelativeWidthWaveImpact, float expNegativeRelativeWidthWaveImpact,
                                                              float sinA, float depthFactorValue)
        {
            float relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(input, depthFactorValue, sinA);

            float sinRelativeDistanceCenterWaveImpact = MathF.Sin(relativeDistanceCenterWaveImpact);
            float cosRelativeDistanceCenterWaveImpact = MathF.Cos(relativeDistanceCenterWaveImpact);
            float expNegativeRelativeDistanceCenterWaveImpact = MathF.Exp(-relativeDistanceCenterWaveImpact);

            if (relativeWidthWaveImpact >= relativeDistanceCenterWaveImpact)
            {
                float expRelativeDistanceCenterWaveImpact = MathF.Exp(relativeDistanceCenterWaveImpact);

                return (-sinRelativeDistanceCenterWaveImpact
                        * (expRelativeDistanceCenterWaveImpact - expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        + cosRelativeDistanceCenterWaveImpact
                        * (expRelativeDistanceCenterWaveImpact + expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        - 2 * expNegativeRelativeDistanceCenterWaveImpact
                            * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                       / relativeWidthWaveImpact;
            }

            float expRelativeWidthWaveImpact = MathF.Exp(relativeWidthWaveImpact);

            return (cosRelativeDistanceCenterWaveImpact
                    * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact)
                       + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact))
                    + sinRelativeDistanceCenterWaveImpact
                    * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact)
                       + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact))
                    - 2 * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                   * expNegativeRelativeDistanceCenterWaveImpact / relativeWidthWaveImpact;
        }

        private static float RelativeWidthWaveImpact(float stiffnessRelation, float widthFactorValue, float waveHeightHm0)
        {
            return MathF.Min(85, stiffnessRelation * widthFactorValue * waveHeightHm0 / 2);
        }

        private static float RelativeDistanceCenterWaveImpact(AsphaltWaveImpactIncrementDamageGpuInput input, float depthFactorValue,
                                                              float sinA)
        {
            return MathF.Min(85, input.StiffnessRelation
                                 * MathF.Abs(input.Z - input.WaterLevel - depthFactorValue * input.WaveHeightHm0) / sinA);
        }
    }
}
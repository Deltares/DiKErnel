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
        private static readonly double bendingStressPartial1 = Math.Pow(10, -99);

        public static double IncrementDamage(AsphaltWaveImpactIncrementDamageGpuInput input)
        {
            double result = 0;

            double sinA = Math.Sin(Math.Atan(input.OuterSlope));

            double bendingStressPartial2 = -3 * input.MaximumPeakStress /
                                           (4 * Math.Pow(input.StiffnessRelation, 2) * Math.Pow(input.ComputationalThickness, 2));

            for (var i = 0; i < input.WidthFactorValues.Length; i++)
            {
                double relativeWidthWaveImpact = RelativeWidthWaveImpact(input.StiffnessRelation, input.WidthFactorValues[i],
                                                                         input.WaveHeightHm0);

                double depthFactorAccumulation = DepthFactorAccumulation(input, relativeWidthWaveImpact, sinA, bendingStressPartial2);

                result += input.WidthFactorProbabilities[i] * depthFactorAccumulation;
            }

            return result;
        }

        private static double DepthFactorAccumulation(AsphaltWaveImpactIncrementDamageGpuInput input, double relativeWidthWaveImpact,
                                                      double sinA, double bendingStressPartial2)
        {
            double result = 0;

            double sinRelativeWidthWaveImpact = Math.Sin(relativeWidthWaveImpact);
            double cosRelativeWidthWaveImpact = Math.Cos(relativeWidthWaveImpact);
            double expNegativeRelativeWidthWaveImpact = Math.Exp(-relativeWidthWaveImpact);

            for (var i = 0; i < input.DepthFactorValues.Length; i++)
            {
                double bendingStress = BendingStress(input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact,
                                                     expNegativeRelativeWidthWaveImpact, sinA, input.DepthFactorValues[i],
                                                     bendingStressPartial2);

                double impactFactorAccumulation = ImpactFactorAccumulation(input, bendingStress);

                result += input.DepthFactorProbabilities[i] * impactFactorAccumulation;
            }

            return result;
        }

        private static double ImpactFactorAccumulation(AsphaltWaveImpactIncrementDamageGpuInput input, double bendingStress)
        {
            double result = 0;

            for (var i = 0; i < input.ImpactFactorValues.Length; i++)
            {
                double fatigue = Fatigue(input, bendingStress, ImpactNumber(input.OuterSlope, input.ImpactFactorValues[i],
                                                                            input.ImpactNumberC));

                result += input.ImpactFactorProbabilities[i] * input.AverageNumberOfWaves * fatigue;
            }

            return result;
        }

        private static double Fatigue(AsphaltWaveImpactIncrementDamageGpuInput input, double bendingStress, double impactNumber)
        {
            double logTension = LogTension(bendingStress, impactNumber);

            return Math.Pow(10, -input.FatigueBeta * Math.Pow(Math.Max(0, input.LogFlexuralStrength - logTension), input.FatigueAlpha));
        }

        private static double LogTension(double bendingStress, double impactNumber)
        {
            return Math.Log10(impactNumber * bendingStress);
        }

        private static double ImpactNumber(double outerSlope, double impactFactorValue, double impactNumberC)
        {
            return 4 * impactNumberC * outerSlope * impactFactorValue;
        }

        private static double BendingStress(AsphaltWaveImpactIncrementDamageGpuInput input, double relativeWidthWaveImpact,
                                            double sinRelativeWidthWaveImpact, double cosRelativeWidthWaveImpact,
                                            double expNegativeRelativeWidthWaveImpact, double sinA, double depthFactorValue,
                                            double bendingStressPartial2)
        {
            double spatialDistributionBendingStress = SpatialDistributionBendingStress(
                input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact, expNegativeRelativeWidthWaveImpact,
                sinA, depthFactorValue);

            return Math.Max(bendingStressPartial1, bendingStressPartial2 * spatialDistributionBendingStress);
        }

        private static double SpatialDistributionBendingStress(AsphaltWaveImpactIncrementDamageGpuInput input,
                                                               double relativeWidthWaveImpact, double sinRelativeWidthWaveImpact,
                                                               double cosRelativeWidthWaveImpact, double expNegativeRelativeWidthWaveImpact,
                                                               double sinA, double depthFactorValue)
        {
            double relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(input, depthFactorValue, sinA);

            double sinRelativeDistanceCenterWaveImpact = Math.Sin(relativeDistanceCenterWaveImpact);
            double cosRelativeDistanceCenterWaveImpact = Math.Cos(relativeDistanceCenterWaveImpact);
            double expNegativeRelativeDistanceCenterWaveImpact = Math.Exp(-relativeDistanceCenterWaveImpact);

            if (relativeWidthWaveImpact >= relativeDistanceCenterWaveImpact)
            {
                double expRelativeDistanceCenterWaveImpact = Math.Exp(relativeDistanceCenterWaveImpact);

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

            double expRelativeWidthWaveImpact = Math.Exp(relativeWidthWaveImpact);

            return (cosRelativeDistanceCenterWaveImpact
                    * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact)
                       + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact))
                    + sinRelativeDistanceCenterWaveImpact
                    * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact)
                       + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact))
                    - 2 * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                   * expNegativeRelativeDistanceCenterWaveImpact / relativeWidthWaveImpact;
        }

        private static double RelativeWidthWaveImpact(double stiffnessRelation, double widthFactorValue, double waveHeightHm0)
        {
            return Math.Min(85, stiffnessRelation * widthFactorValue * waveHeightHm0 / 2);
        }

        private static double RelativeDistanceCenterWaveImpact(AsphaltWaveImpactIncrementDamageGpuInput input, double depthFactorValue,
                                                               double sinA)
        {
            return Math.Min(85, input.StiffnessRelation
                                * Math.Abs(input.Z - input.WaterLevel - depthFactorValue * input.WaveHeightHm0) / sinA);
        }
    }
}
// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// //
// // This file is part of DiKErnel.
// //
// // DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// // GNU Lesser General Public License as published by the Free Software Foundation, either
// // version 3 of the License, or (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// // without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// // See the GNU Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License along with this
// // program. If not, see <http://www.gnu.org/licenses/>.
// //
// // All names, logos, and references to "Deltares" are registered trademarks of Stichting
// // Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;

namespace DiKErnel.FunctionLibrary.AsphaltRevetmentWaveImpact
{
    /// <summary>
    /// Class that holds all asphalt revetment wave impact specific calculation routines.
    /// </summary>
    public static class AsphaltRevetmentWaveImpactFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(AsphaltRevetmentWaveImpactFunctionsInput input)
        {
            var result = 0.0;

            double sinA = Math.Sin(Math.Atan(input.OuterSlope));

            foreach ((double, double) widthFactor in input.WidthFactors)
            {
                double relativeWidthWaveImpact = RelativeWidthWaveImpact(input.StiffnessRelation, widthFactor.Item1,
                                                                         input.WaveHeightHm0);
                double depthFactorAccumulation = DepthFactorAccumulation(input, relativeWidthWaveImpact, sinA);

                result += widthFactor.Item2 * depthFactorAccumulation;
            }

            return result;
        }

        private static double DepthFactorAccumulation(AsphaltRevetmentWaveImpactFunctionsInput input,
                                                      double relativeWidthWaveImpact, double sinA)
        {
            var result = 0.0;
            foreach ((double, double) depthFactor in input.DepthFactors)
            {
                double bendingStress = BendingStress(input, relativeWidthWaveImpact, sinA, depthFactor.Item1);
                double impactFactorAccumulation = ImpactFactorAccumulation(input, bendingStress);

                result += depthFactor.Item2 * impactFactorAccumulation;
            }

            return result;
        }

        private static double ImpactFactorAccumulation(AsphaltRevetmentWaveImpactFunctionsInput input, double bendingStress)
        {
            var result = 0.0;
            foreach ((double, double) impactFactor in input.ImpactFactors)
            {
                double fatigue = Fatigue(input, bendingStress, impactFactor.Item1);

                result += impactFactor.Item2 * input.AverageNumberOfWaves * fatigue;
            }

            return result;
        }

        private static double Fatigue(AsphaltRevetmentWaveImpactFunctionsInput input, double bendingStress,
                                      double impactFactorValue)
        {
            double logTension = LogTension(bendingStress, input.OuterSlope, impactFactorValue, input.ImpactNumberC);

            return Math.Pow(10.0, -input.FatigueBeta * Math.Pow(Math.Max(0.0, input.LogFailureTension - logTension),
                                                                input.FatigueAlpha));
        }

        private static double LogTension(double bendingStress, double outerSlope, double impactFactorValue, double impactNumberC)
        {
            double impactNumber = ImpactNumber(outerSlope, impactFactorValue, impactNumberC);
            
            return Math.Log10(impactNumber * bendingStress);
        }

        private static double ImpactNumber(double outerSlope, double impactFactorValue, double impactNumberC)
        {
            return 4.0 * impactNumberC * outerSlope * impactFactorValue;
        }

        private static double BendingStress(AsphaltRevetmentWaveImpactFunctionsInput input, double relativeWidthWaveImpact,
                                            double sinA, double depthFactorValue)
        {
            double spatialDistributionBendingStress = SpatialDistributionBendingStress(input, relativeWidthWaveImpact, sinA,
                                                                                       depthFactorValue);

            return Math.Max(Math.Pow(10.0, -99.0),
                            -3.0 * input.MaximumPeakStress / (4.0 * Math.Pow(input.StiffnessRelation, 2.0) 
                                                                  * Math.Pow(input.ComputationalThickness, 2.0))
                            * spatialDistributionBendingStress);
        }

        private static double SpatialDistributionBendingStress(AsphaltRevetmentWaveImpactFunctionsInput input,
                                                               double relativeWidthWaveImpact, double sinA,
                                                               double depthFactorValue)
        {
            double relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(input, depthFactorValue, sinA);

            double sinRelativeDistanceCenterWaveImpact = Math.Sin(relativeDistanceCenterWaveImpact);
            double sinRelativeWidthWaveImpact = Math.Sin(relativeWidthWaveImpact);
            double cosRelativeDistanceCenterWaveImpact = Math.Cos(relativeDistanceCenterWaveImpact);
            double cosRelativeWidthWaveImpact = Math.Cos(relativeWidthWaveImpact);
            double expNegativeRelativeDistanceCenterWaveImpact = Math.Exp(-relativeDistanceCenterWaveImpact);
            double expNegativeRelativeWidthWaveImpact = Math.Exp(-relativeWidthWaveImpact);

            if (relativeWidthWaveImpact >= relativeDistanceCenterWaveImpact)
            {
                double expRelativeDistanceCenterWaveImpact = Math.Exp(relativeDistanceCenterWaveImpact);

                return (-sinRelativeDistanceCenterWaveImpact
                        * (expRelativeDistanceCenterWaveImpact - expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        + cosRelativeDistanceCenterWaveImpact
                        * (expRelativeDistanceCenterWaveImpact + expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        - 2.0 * expNegativeRelativeDistanceCenterWaveImpact
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
                    - 2.0 * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                   * expNegativeRelativeDistanceCenterWaveImpact / relativeWidthWaveImpact;
        }

        private static double RelativeWidthWaveImpact(double stiffnessRelation, double widthFactorValue, double waveHeightHm0)
        {
            return Math.Min(85.0, stiffnessRelation * widthFactorValue * waveHeightHm0 / 2.0);
        }

        private static double RelativeDistanceCenterWaveImpact(AsphaltRevetmentWaveImpactFunctionsInput input,
                                                               double depthFactorValue, double sinA)
        {
            return Math.Min(85.0, input.StiffnessRelation
                                  * Math.Abs(input.Z - input.WaterLevel - depthFactorValue * input.WaveHeightHm0) / sinA);
        }
    }
}
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

namespace DiKErnel.FunctionLibrary.AsphaltWaveImpact
{
    /// <summary>
    /// Class that holds asphalt wave impact calculation routines.
    /// </summary>
    public static class AsphaltWaveImpactFunctions
    {
        private static readonly double bindingStressCalculationConstant = Math.Pow(10, -99);

        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(AsphaltWaveImpactInput input)
        {
            double result = 0;

            double sinA = Math.Sin(Math.Atan(input.OuterSlope));

            double bindingStressCalculationPartial = -3 * input.MaximumPeakStress /
                                                     (4 * Math.Pow(input.StiffnessRelation, 2) * Math.Pow(input.ComputationalThickness, 2));

            foreach ((double, double) widthFactor in input.WidthFactors)
            {
                double relativeWidthWaveImpact = RelativeWidthWaveImpact(input.StiffnessRelation, widthFactor.Item1,
                                                                         input.WaveHeightHm0);

                double depthFactorAccumulation = DepthFactorAccumulation(input, relativeWidthWaveImpact, sinA,
                                                                         bindingStressCalculationPartial);

                result += widthFactor.Item2 * depthFactorAccumulation;
            }

            return result;
        }

        /// <summary>
        /// Calculates the logarithm of the flexural strength.
        /// </summary>
        /// <param name="flexuralStrength">The flexural strength [MPa].</param>
        /// <returns>The logarithm of the flexural strength [MPa].</returns>
        public static double LogFlexuralStrength(double flexuralStrength)
        {
            return Math.Log10(flexuralStrength);
        }

        /// <summary>
        /// Calculates the maximum peak stress.
        /// </summary>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="gravitationalAcceleration">The gravitational
        /// acceleration [m/s^2].</param>
        /// <param name="densityOfWater">The density of water [kg/m^3].</param>
        /// <returns>The maximum peak stress [MPa].</returns>
        public static double MaximumPeakStress(double waveHeightHm0, double gravitationalAcceleration, double densityOfWater)
        {
            return gravitationalAcceleration * densityOfWater * waveHeightHm0 / Math.Pow(10, 6);
        }

        /// <summary>
        /// Calculates the stiffness relation.
        /// </summary>
        /// <param name="computationalThickness">The computation thickness [m].</param>
        /// <param name="equivalentElasticModulus">The equivalent elastic modulus [MPa].</param>
        /// <param name="soilElasticity">The soil elasticity [MPa/m].</param>
        /// <param name="stiffnessRelationNu">The Nu coefficient [-].</param>
        /// <returns>The stiffness relation [m^-1].</returns>
        public static double StiffnessRelation(double computationalThickness, double equivalentElasticModulus,
                                               double soilElasticity, double stiffnessRelationNu)
        {
            return Math.Pow(3 * soilElasticity * (1 - Math.Pow(stiffnessRelationNu, 2))
                            / (equivalentElasticModulus * Math.Pow(computationalThickness, 3)),
                            1d / 4);
        }

        /// <summary>
        /// Calculates the computational thickness.
        /// </summary>
        /// <param name="thicknessUpperLayer">The thickness of the upper layer [m].</param>
        /// <param name="thicknessSubLayer">The thickness of the sub layer [m].</param>
        /// <param name="elasticModulusUpperLayer">The elastic modulus of the upper
        /// layer [MPa].</param>
        /// <param name="elasticModulusSubLayer">The elastic modulus of the sub
        /// layer [MPa].</param>
        /// <returns>The computational thickness [m].</returns>
        public static double ComputationalThickness(double thicknessUpperLayer, double thicknessSubLayer,
                                                    double elasticModulusUpperLayer, double elasticModulusSubLayer)
        {
            return thicknessUpperLayer * Math.Pow(elasticModulusUpperLayer / elasticModulusSubLayer, 1d / 3)
                   + thicknessSubLayer;
        }

        /// <summary>
        /// Calculates the outer slope.
        /// </summary>
        /// <param name="slopeLowerPosition">The lower position of the slope [m].</param>
        /// <param name="slopeLowerLevel">The lower level of the slope [m].</param>
        /// <param name="slopeUpperPosition">The upper position of the slope [m].</param>
        /// <param name="slopeUpperLevel">The upper level of the slope [m].</param>
        /// <returns>The outer slope [-].</returns>
        public static double OuterSlope(double slopeLowerPosition, double slopeLowerLevel, double slopeUpperPosition,
                                        double slopeUpperLevel)
        {
            return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
        }

        private static double DepthFactorAccumulation(AsphaltWaveImpactInput input, double relativeWidthWaveImpact, double sinA,
                                                      double bindingStressCalculationPartial)
        {
            double result = 0;

            double sinRelativeWidthWaveImpact = Math.Sin(relativeWidthWaveImpact);
            double cosRelativeWidthWaveImpact = Math.Cos(relativeWidthWaveImpact);
            double expNegativeRelativeWidthWaveImpact = Math.Exp(-relativeWidthWaveImpact);

            foreach ((double, double) depthFactor in input.DepthFactors)
            {
                double bendingStress = BendingStress(input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact,
                                                     expNegativeRelativeWidthWaveImpact, sinA, depthFactor.Item1,
                                                     bindingStressCalculationPartial);

                double impactFactorAccumulation = ImpactFactorAccumulation(input, bendingStress);

                result += depthFactor.Item2 * impactFactorAccumulation;
            }

            return result;
        }

        private static double ImpactFactorAccumulation(AsphaltWaveImpactInput input, double bendingStress)
        {
            double result = 0;

            foreach ((double, double) impactFactor in input.ImpactFactors)
            {
                double fatigue = Fatigue(input, bendingStress, impactFactor.Item1);

                result += impactFactor.Item2 * input.AverageNumberOfWaves * fatigue;
            }

            return result;
        }

        private static double Fatigue(AsphaltWaveImpactInput input, double bendingStress, double impactFactorValue)
        {
            double logTension = LogTension(bendingStress, input.OuterSlope, impactFactorValue, input.ImpactNumberC);

            return Math.Pow(10, -input.FatigueBeta * Math.Pow(Math.Max(0, input.LogFlexuralStrength - logTension),
                                                              input.FatigueAlpha));
        }

        private static double LogTension(double bendingStress, double outerSlope, double impactFactorValue, double impactNumberC)
        {
            double impactNumber = ImpactNumber(outerSlope, impactFactorValue, impactNumberC);

            return Math.Log10(impactNumber * bendingStress);
        }

        private static double ImpactNumber(double outerSlope, double impactFactorValue, double impactNumberC)
        {
            return 4 * impactNumberC * outerSlope * impactFactorValue;
        }

        private static double BendingStress(AsphaltWaveImpactInput input, double relativeWidthWaveImpact,
                                            double sinRelativeWidthWaveImpact, double cosRelativeWidthWaveImpact,
                                            double expNegativeRelativeWidthWaveImpact, double sinA, double depthFactorValue,
                                            double bindingStressCalculationPartial)
        {
            double spatialDistributionBendingStress = SpatialDistributionBendingStress(
                input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact, expNegativeRelativeWidthWaveImpact,
                sinA, depthFactorValue);

            return Math.Max(bindingStressCalculationConstant, bindingStressCalculationPartial * spatialDistributionBendingStress);
        }

        private static double SpatialDistributionBendingStress(AsphaltWaveImpactInput input, double relativeWidthWaveImpact,
                                                               double sinRelativeWidthWaveImpact, double cosRelativeWidthWaveImpact,
                                                               double expNegativeRelativeWidthWaveImpact, double sinA,
                                                               double depthFactorValue)
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

        private static double RelativeDistanceCenterWaveImpact(AsphaltWaveImpactInput input, double depthFactorValue,
                                                               double sinA)
        {
            return Math.Min(85, input.StiffnessRelation
                                * Math.Abs(input.Z - input.WaterLevel - depthFactorValue * input.WaveHeightHm0) / sinA);
        }
    }
}
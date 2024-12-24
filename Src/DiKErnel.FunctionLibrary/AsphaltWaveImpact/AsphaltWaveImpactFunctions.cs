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
using System.Linq;

namespace DiKErnel.FunctionLibrary.AsphaltWaveImpact
{
    /// <summary>
    /// Class that holds asphalt wave impact calculation routines.
    /// </summary>
    public static class AsphaltWaveImpactFunctions
    {
        private const float maximumPeakStressPartial = 1000000;
        private const float bendingStressPartial1 = 1e-99;

        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The increment of damage [-].</returns>
        public static float IncrementDamage(AsphaltWaveImpactInput input)
        {
            float result = 0;

            float sinA = Math.Sin(Math.Atan(input.OuterSlope));

            float bendingStressPartial2 = -3 * input.MaximumPeakStress /
                                          (4 * input.StiffnessRelation * input.StiffnessRelation * input.ComputationalThickness *
                                           input.ComputationalThickness);

            (float, float)[] widthFactorsArray = input.WidthFactors.ToArray();
            int widthFactorsCount = widthFactorsArray.Length;

            (float, float)[] depthFactorsArray = input.DepthFactors.ToArray();
            int depthFactorsCount = depthFactorsArray.Length;

            float[] impactFactorProbabilities = input.ImpactFactors.Select(impactFactor => impactFactor.Item2).ToArray();

            float[] impactNumberLookup = input.ImpactFactors
                                              .Select(impactFactor => ImpactNumber(input.OuterSlope, impactFactor.Item1,
                                                                                   input.ImpactNumberC))
                                              .ToArray();

            for (var i = 0; i < widthFactorsCount; i++)
            {
                (float, float) widthFactor = widthFactorsArray[i];

                float relativeWidthWaveImpact = RelativeWidthWaveImpact(input.StiffnessRelation, widthFactor.Item1,
                                                                        input.WaveHeightHm0);

                float depthFactorAccumulation = DepthFactorAccumulation(input, depthFactorsArray, depthFactorsCount,
                                                                        impactFactorProbabilities, relativeWidthWaveImpact, sinA,
                                                                        impactNumberLookup, bendingStressPartial2);

                result += widthFactor.Item2 * depthFactorAccumulation;
            }

            return result;
        }

        /// <summary>
        /// Calculates the logarithm of the flexural strength.
        /// </summary>
        /// <param name="flexuralStrength">The flexural strength [MPa].</param>
        /// <returns>The logarithm of the flexural strength [MPa].</returns>
        public static float LogFlexuralStrength(float flexuralStrength)
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
        public static float MaximumPeakStress(float waveHeightHm0, float gravitationalAcceleration, float densityOfWater)
        {
            return gravitationalAcceleration * densityOfWater * waveHeightHm0 / maximumPeakStressPartial;
        }

        /// <summary>
        /// Calculates the stiffness relation.
        /// </summary>
        /// <param name="computationalThickness">The computation thickness [m].</param>
        /// <param name="equivalentElasticModulus">The equivalent elastic modulus [MPa].</param>
        /// <param name="soilElasticity">The soil elasticity [MPa/m].</param>
        /// <param name="stiffnessRelationNu">The Nu coefficient [-].</param>
        /// <returns>The stiffness relation [m^-1].</returns>
        public static float StiffnessRelation(float computationalThickness, float equivalentElasticModulus,
                                              float soilElasticity, float stiffnessRelationNu)
        {
            return CMath.Pow(3 * soilElasticity * (1 - stiffnessRelationNu * stiffnessRelationNu)
                             / (equivalentElasticModulus * computationalThickness * computationalThickness * computationalThickness),
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
        public static float ComputationalThickness(float thicknessUpperLayer, float thicknessSubLayer,
                                                   float elasticModulusUpperLayer, float elasticModulusSubLayer)
        {
            return thicknessUpperLayer * CMath.Pow(elasticModulusUpperLayer / elasticModulusSubLayer, 1d / 3)
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
        public static float OuterSlope(float slopeLowerPosition, float slopeLowerLevel, float slopeUpperPosition,
                                       float slopeUpperLevel)
        {
            return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
        }

        private static float DepthFactorAccumulation(AsphaltWaveImpactInput input, (float, float)[] depthFactorsArray,
                                                     int depthFactorsCount, float[] impactFactorProbabilities,
                                                     float relativeWidthWaveImpact, float sinA, float[] impactNumberLookup,
                                                     float bendingStressPartial2)
        {
            float result = 0;

            float sinRelativeWidthWaveImpact = Math.Sin(relativeWidthWaveImpact);
            float cosRelativeWidthWaveImpact = Math.Cos(relativeWidthWaveImpact);
            float expNegativeRelativeWidthWaveImpact = Math.Exp(-relativeWidthWaveImpact);

            for (var i = 0; i < depthFactorsCount; i++)
            {
                (float, float) depthFactor = depthFactorsArray[i];

                float bendingStress = BendingStress(input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact,
                                                    expNegativeRelativeWidthWaveImpact, sinA, depthFactor.Item1, bendingStressPartial2);

                float impactFactorAccumulation = ImpactFactorAccumulation(input, impactFactorProbabilities, bendingStress,
                                                                          impactNumberLookup);

                result += depthFactor.Item2 * impactFactorAccumulation;
            }

            return result;
        }

        private static float ImpactFactorAccumulation(AsphaltWaveImpactInput input, float[] impactFactorProbabilities,
                                                      float bendingStress, float[] impactNumberLookup)
        {
            return CMath.OptimizedImpactFactorAccumulation(input.FatigueAlpha, input.FatigueBeta, input.AverageNumberOfWaves,
                                                           input.LogFlexuralStrength, bendingStress,
                                                           impactFactorProbabilities, impactFactorProbabilities.Length,
                                                           impactNumberLookup, impactNumberLookup.Length);
        }

        private static float ImpactNumber(float outerSlope, float impactFactorValue, float impactNumberC)
        {
            return 4 * impactNumberC * outerSlope * impactFactorValue;
        }

        private static float BendingStress(AsphaltWaveImpactInput input, float relativeWidthWaveImpact,
                                           float sinRelativeWidthWaveImpact, float cosRelativeWidthWaveImpact,
                                           float expNegativeRelativeWidthWaveImpact, float sinA, float depthFactorValue,
                                           float bendingStressPartial2)
        {
            float spatialDistributionBendingStress = SpatialDistributionBendingStress(
                input, relativeWidthWaveImpact, sinRelativeWidthWaveImpact, cosRelativeWidthWaveImpact, expNegativeRelativeWidthWaveImpact,
                sinA, depthFactorValue);

            return Math.Max(bendingStressPartial1, bendingStressPartial2 * spatialDistributionBendingStress);
        }

        private static float SpatialDistributionBendingStress(AsphaltWaveImpactInput input, float relativeWidthWaveImpact,
                                                              float sinRelativeWidthWaveImpact, float cosRelativeWidthWaveImpact,
                                                              float expNegativeRelativeWidthWaveImpact, float sinA,
                                                              float depthFactorValue)
        {
            float relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(input, depthFactorValue, sinA);

            float sinRelativeDistanceCenterWaveImpact = Math.Sin(relativeDistanceCenterWaveImpact);
            float cosRelativeDistanceCenterWaveImpact = Math.Cos(relativeDistanceCenterWaveImpact);
            float expNegativeRelativeDistanceCenterWaveImpact = Math.Exp(-relativeDistanceCenterWaveImpact);

            if (relativeWidthWaveImpact >= relativeDistanceCenterWaveImpact)
            {
                float expRelativeDistanceCenterWaveImpact = Math.Exp(relativeDistanceCenterWaveImpact);

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

            float expRelativeWidthWaveImpact = Math.Exp(relativeWidthWaveImpact);

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
            return Math.Min(85, stiffnessRelation * widthFactorValue * waveHeightHm0 / 2);
        }

        private static float RelativeDistanceCenterWaveImpact(AsphaltWaveImpactInput input, float depthFactorValue,
                                                              float sinA)
        {
            return Math.Min(85, input.StiffnessRelation
                                * Math.Abs(input.Z - input.WaterLevel - depthFactorValue * input.WaveHeightHm0) / sinA);
        }
    }
}
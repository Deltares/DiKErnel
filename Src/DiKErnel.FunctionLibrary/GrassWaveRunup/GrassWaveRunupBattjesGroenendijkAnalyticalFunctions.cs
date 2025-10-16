// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// 
// This file is part of DiKErnel.
// 
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
// 
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using System.Linq;
using MathNet.Numerics;
using MathNet.Numerics.Interpolation;

namespace DiKErnel.FunctionLibrary.GrassWaveRunup
{
    /// <summary>
    /// Class that holds grass wave run-up Battjes-Groenendijk analytical calculation
    /// routines.
    /// </summary>
    public static class GrassWaveRunupBattjesGroenendijkAnalyticalFunctions
    {
        private const double verticalWaveRunupLimit3 = 1000000;

        private static readonly IReadOnlyList<(double, double)> lambdasRu1 = new[]
        {
            (0, 12.193),
            (0.05, 12.193),
            (0.1, 7.003),
            (0.15, 5.063),
            (0.2, 4.022),
            (0.25, 3.365),
            (0.3, 2.908),
            (0.35, 2.571),
            (0.4, 2.311),
            (0.45, 2.104),
            (0.5, 1.936),
            (0.55, 1.796),
            (0.6, 1.678),
            (0.65, 1.578),
            (0.7, 1.492),
            (0.75, 1.419),
            (0.8, 1.356),
            (0.85, 1.302),
            (0.9, 1.256),
            (0.95, 1.216),
            (1, 1.182),
            (1.05, 1.153),
            (1.1, 1.128),
            (1.15, 1.108),
            (1.2, 1.09),
            (1.25, 1.075),
            (1.3, 1.063),
            (1.35, 1.052),
            (1.4, 1.043),
            (1.45, 1.036),
            (1.5, 1.03),
            (1.55, 1.024),
            (1.6, 1.02),
            (1.65, 1.016),
            (1.7, 1.013),
            (1.75, 1.011),
            (1.8, 1.009),
            (1.85, 1.007),
            (1.9, 1.006),
            (1.95, 1.004),
            (2, 1.004),
            (2.05, 1.003),
            (2.1, 1.002),
            (2.15, 1.002),
            (2.2, 1.001),
            (2.25, 1.001),
            (2.3, 1.001),
            (2.35, 1.001),
            (2.4, 1),
            (2.45, 1),
            (2.5, 1),
            (2.55, 1),
            (2.6, 1),
            (2.65, 1),
            (2.7, 1),
            (2.75, 1),
            (2.8, 1),
            (2.85, 1),
            (2.9, 1),
            (2.95, 1),
            (3, 1)
        };

        private static readonly IReadOnlyList<(double, double)> lambdasRu2 = new[]
        {
            (0, 1.06),
            (0.05, 1.06),
            (0.1, 1.06),
            (0.15, 1.06),
            (0.2, 1.06),
            (0.25, 1.06),
            (0.3, 1.06),
            (0.35, 1.06),
            (0.4, 1.06),
            (0.45, 1.06),
            (0.5, 1.061),
            (0.55, 1.061),
            (0.6, 1.062),
            (0.65, 1.064),
            (0.7, 1.066),
            (0.75, 1.069),
            (0.8, 1.073),
            (0.85, 1.077),
            (0.9, 1.083),
            (0.95, 1.09),
            (1, 1.097),
            (1.05, 1.106),
            (1.1, 1.116),
            (1.15, 1.126),
            (1.2, 1.138),
            (1.25, 1.15),
            (1.3, 1.162),
            (1.35, 1.175),
            (1.4, 1.189),
            (1.45, 1.203),
            (1.5, 1.217),
            (1.55, 1.231),
            (1.6, 1.246),
            (1.65, 1.261),
            (1.7, 1.275),
            (1.75, 1.29),
            (1.8, 1.305),
            (1.85, 1.32),
            (1.9, 1.334),
            (1.95, 1.349),
            (2, 1.363),
            (2.05, 1.378),
            (2.1, 1.392),
            (2.15, 1.407),
            (2.2, 1.421),
            (2.25, 1.435),
            (2.3, 1.449),
            (2.35, 1.462),
            (2.4, 1.476),
            (2.45, 1.49),
            (2.5, 1.503),
            (2.55, 1.516),
            (2.6, 1.529),
            (2.65, 1.542),
            (2.7, 1.555),
            (2.75, 1.568),
            (2.8, 1.58),
            (2.85, 1.593),
            (2.9, 1.605),
            (2.95, 1.617),
            (3, 1.63)
        };

        private static readonly IInterpolation lambdaRu1Interpolator =
            Interpolate.Linear(lambdasRu1.Select(x => x.Item1), lambdasRu1.Select(x => x.Item2));

        private static readonly IInterpolation lambdaRu2Interpolator =
            Interpolate.Linear(lambdasRu2.Select(x => x.Item1), lambdasRu2.Select(x => x.Item2));

        /// <summary>
        /// Calculates the upper limit wave run-up.
        /// </summary>
        /// <param name="increasedLoadTransitionAlphaM">The increased load transition alpha M [-].</param>
        /// <param name="reducedStrengthTransitionAlphaS">The reduced strength transition alpha S [-].</param>
        /// <param name="frontVelocityCu">The Cu coefficient [-].</param>
        /// <param name="criticalFrontVelocity">The critical front velocity [m/s].</param>
        /// <param name="gravitationalAcceleration">The gravitational acceleration [m/s^2].</param>
        /// <returns>The upper limit wave run-up [m].</returns>
        public static double UpperLimitWaveRunup(double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
                                                 double frontVelocityCu, double criticalFrontVelocity, double gravitationalAcceleration)
        {
            return (reducedStrengthTransitionAlphaS / increasedLoadTransitionAlphaM) *
                   (criticalFrontVelocity * criticalFrontVelocity / (frontVelocityCu * frontVelocityCu * gravitationalAcceleration));
        }

        /// <summary>
        /// Calculates the cumulative overload.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <param name="upperLimitWaveRunup">The upper limit wave run-up [m].</param>
        /// <returns>The cumulative overload [m^2/s^2].</returns>
        public static double CumulativeOverload(GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input,
                                                double upperLimitWaveRunup)
        {
            double lowerLimitWaveRunup = LowerLimitWaveRunup(input.VerticalDistanceWaterLevelElevation,
                                                             upperLimitWaveRunup);

            double depthForeshore = DepthForeshore(input.WaterLevel, input.BottomForeshoreZ);

            double waveRunupTransition = WaveRunupTransition(input.SlopeForeshore,
                                                             input.RepresentativeWaveRunup2P,
                                                             input.WaveHeightHm0, depthForeshore);

            double rootMeanSquareWaveRunup = RootMeanSquareWaveRunup(input.RepresentativeWaveRunup2P,
                                                                     input.WaveHeightHm0, depthForeshore);

            double scalingParameterRu1 = ScalingParameterRu(waveRunupTransition, rootMeanSquareWaveRunup, LambdaRu1);

            double scalingParameterRu2 = ScalingParameterRu(waveRunupTransition, rootMeanSquareWaveRunup, LambdaRu2);

            double scaledVerticalDistanceWaterLevelElevation =
                ScaledVerticalDistanceWaterLevelElevation(input.VerticalDistanceWaterLevelElevation);

            double verticalWaveRunupLimit2 = VerticalWaveRunupLimit2(scaledVerticalDistanceWaterLevelElevation, upperLimitWaveRunup);

            double verticalWaveRunupLimit1 = VerticalWaveRunupLimit1(waveRunupTransition, verticalWaveRunupLimit2);

            double verticalWaveRunupLimit6 = VerticalWaveRunupLimit6(input.VerticalDistanceWaterLevelElevation,
                                                                     scaledVerticalDistanceWaterLevelElevation,
                                                                     lowerLimitWaveRunup);

            double verticalWaveRunupLimit5 = VerticalWaveRunupLimit5(scaledVerticalDistanceWaterLevelElevation,
                                                                     waveRunupTransition, verticalWaveRunupLimit6);

            double cumulativeOverload1 = DeltaCumulativeLoad(input, verticalWaveRunupLimit1, scalingParameterRu1, input.K1);

            double cumulativeOverload2 = DeltaCumulativeLoad(input, verticalWaveRunupLimit2, scalingParameterRu1, input.K1);

            double cumulativeOverload3 = DeltaCumulativeLoad(input, verticalWaveRunupLimit3, scalingParameterRu2, input.K2);

            double cumulativeOverload4 = DeltaCumulativeLoad(input, verticalWaveRunupLimit1, scalingParameterRu2, input.K2);

            double cumulativeOverload5 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalWaveRunupLimit5, scalingParameterRu1, input.K1);

            double cumulativeOverload6 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalWaveRunupLimit6, scalingParameterRu1, input.K1);

            double cumulativeOverload7 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, scaledVerticalDistanceWaterLevelElevation, scalingParameterRu2,
                                                                  input.K2);

            double cumulativeOverload8 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalWaveRunupLimit5, scalingParameterRu2, input.K2);

            return input.AverageNumberOfWaves * (cumulativeOverload1 - cumulativeOverload2 +
                                                 cumulativeOverload3 - cumulativeOverload4 +
                                                 cumulativeOverload5 - cumulativeOverload6 +
                                                 cumulativeOverload7 - cumulativeOverload8);
        }

        private static double LowerLimitWaveRunup(double verticalWaterLevelDistance, double upperLimitWaveRunup)
        {
            return (1d / 32) * (32 * verticalWaterLevelDistance + upperLimitWaveRunup +
                                Math.Sqrt(upperLimitWaveRunup) * Math.Sqrt(64 * verticalWaterLevelDistance + upperLimitWaveRunup));
        }

        private static double DepthForeshore(double waterLevel, double bottomForeshoreZ)
        {
            return waterLevel - bottomForeshoreZ;
        }

        private static double WaveRunupTransition(double slopeForeshore, double representativeWaveRunup2P, double waveHeightHm0,
                                                  double depthForeshore)
        {
            return (0.35 + 5.8 * slopeForeshore) * depthForeshore * representativeWaveRunup2P / (1.4 * waveHeightHm0);
        }

        private static double RootMeanSquareWaveRunup(double representativeWaveRunup2P, double waveHeightHm0, double depthForeshore)
        {
            return (0.6725 + 0.2025 * waveHeightHm0 / depthForeshore) * (representativeWaveRunup2P / 1.4);
        }

        private static double ScalingParameterRu(double waveRunupTransition, double rootMeanSquareWaveRunup,
                                                 Func<double, double> getLambdaRuFunc)
        {
            return rootMeanSquareWaveRunup * getLambdaRuFunc(waveRunupTransition / rootMeanSquareWaveRunup);
        }

        private static double LambdaRu1(double kappa)
        {
            return kappa > 3d ? 1 : lambdaRu1Interpolator.Interpolate(kappa);
        }

        private static double LambdaRu2(double kappa)
        {
            return kappa > 3d ? Math.Pow(kappa, 4d / 9) : lambdaRu2Interpolator.Interpolate(kappa);
        }

        private static double VerticalWaveRunupLimit2(double scaledVerticalDistanceWaterLevelElevation, double upperLimitWaveRunup)
        {
            return Math.Max(scaledVerticalDistanceWaterLevelElevation, upperLimitWaveRunup);
        }

        private static double VerticalWaveRunupLimit1(double waveRunupTransition, double verticalWaveRunupLimit2)
        {
            return Math.Max(verticalWaveRunupLimit2, waveRunupTransition);
        }

        private static double VerticalWaveRunupLimit6(double verticalDistanceWaterLevelElevation,
                                                      double scaledVerticalDistanceWaterLevelElevation,
                                                      double lowerLimitWaveRunup)
        {
            return Math.Max(Math.Min(scaledVerticalDistanceWaterLevelElevation, lowerLimitWaveRunup),
                            verticalDistanceWaterLevelElevation);
        }

        private static double VerticalWaveRunupLimit5(double scaledVerticalDistanceWaterLevelElevation, double waveRunupTransition,
                                                      double verticalWaveRunupLimit6)
        {
            return Math.Max(verticalWaveRunupLimit6, Math.Min(scaledVerticalDistanceWaterLevelElevation, waveRunupTransition));
        }

        private static double ScaledVerticalDistanceWaterLevelElevation(double verticalDistanceWaterLevelElevation)
        {
            return (4d / 3) * verticalDistanceWaterLevelElevation;
        }

        private static double DeltaCumulativeLoad(GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input,
                                                  double verticalWaveRunupLimit, double scalingParameterRu, double k)
        {
            return input.IncreasedLoadTransitionAlphaM * input.FrontVelocityCu * input.FrontVelocityCu * input.GravitationalAcceleration *
                   scalingParameterRu * Probability(k, verticalWaveRunupLimit / scalingParameterRu) +
                   ((input.ReducedStrengthTransitionAlphaS * input.CriticalFrontVelocity * input.CriticalFrontVelocity) / k) *
                   Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k));
        }

        private static double DeltaCumulativeLoadWithVerticalDistanceWaterLevel(
            GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input,
            double verticalWaveRunupLimit, double scalingParameterRu, double k)
        {
            return input.IncreasedLoadTransitionAlphaM * input.FrontVelocityCu * input.FrontVelocityCu * input.GravitationalAcceleration *
                   k *
                   (((4 * scalingParameterRu) / k) *
                    Probability(k, verticalWaveRunupLimit / scalingParameterRu) +
                    ((4 * input.VerticalDistanceWaterLevelElevation) / k) *
                    Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k))) +
                   ((input.ReducedStrengthTransitionAlphaS * input.CriticalFrontVelocity * input.CriticalFrontVelocity) / k) *
                   Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k));
        }

        private static double Probability(double xi, double eta)
        {
            double probability = SpecialFunctions.GammaLowerRegularized(1 + 1 / xi, Math.Pow(eta, xi));

            double gammaNominator = SpecialFunctions.Gamma(1 + 1 / xi);

            double gammaDenominator = SpecialFunctions.Gamma(2 + 1 / xi);

            return (gammaNominator * probability) / gammaDenominator +
                   (gammaNominator * probability) / (xi * gammaDenominator);
        }
    }
}
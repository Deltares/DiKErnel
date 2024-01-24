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
    /// Class that holds grass revetment wave run-up calculation routines for
    /// the Battjes-Groenendijk analytical protocol.
    /// </summary>
    public static class GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalFunctions
    {
        private const double verticalLimitWaveRunup3 = 1000000;

        private static readonly IReadOnlyList<(double, double)> lambdasRu1 = new[]
        {
            (0.00, 12.193),
            (0.05, 12.193),
            (0.10, 7.003),
            (0.15, 5.063),
            (0.20, 4.022),
            (0.25, 3.365),
            (0.30, 2.908),
            (0.35, 2.571),
            (0.40, 2.311),
            (0.45, 2.104),
            (0.50, 1.936),
            (0.55, 1.796),
            (0.60, 1.678),
            (0.65, 1.578),
            (0.70, 1.492),
            (0.75, 1.419),
            (0.80, 1.356),
            (0.85, 1.302),
            (0.90, 1.256),
            (0.95, 1.216),
            (1.00, 1.182),
            (1.05, 1.153),
            (1.10, 1.128),
            (1.15, 1.108),
            (1.20, 1.090),
            (1.25, 1.075),
            (1.30, 1.063),
            (1.35, 1.052),
            (1.40, 1.043),
            (1.45, 1.036),
            (1.50, 1.030),
            (1.55, 1.024),
            (1.60, 1.020),
            (1.65, 1.016),
            (1.70, 1.013),
            (1.75, 1.011),
            (1.80, 1.009),
            (1.85, 1.007),
            (1.90, 1.006),
            (1.95, 1.004),
            (2.00, 1.004),
            (2.05, 1.003),
            (2.10, 1.002),
            (2.15, 1.002),
            (2.20, 1.001),
            (2.25, 1.001),
            (2.30, 1.001),
            (2.35, 1.001),
            (2.40, 1.000),
            (2.45, 1.000),
            (2.50, 1.000),
            (2.55, 1.000),
            (2.60, 1.000),
            (2.65, 1.000),
            (2.70, 1.000),
            (2.75, 1.000),
            (2.80, 1.000),
            (2.85, 1.000),
            (2.90, 1.000),
            (2.95, 1.000),
            (3.00, 1.000)
        };

        private static readonly IReadOnlyList<(double, double)> lambdasRu2 = new[]
        {
            (0.00, 1.060),
            (0.05, 1.060),
            (0.10, 1.060),
            (0.15, 1.060),
            (0.20, 1.060),
            (0.25, 1.060),
            (0.30, 1.060),
            (0.35, 1.060),
            (0.40, 1.060),
            (0.45, 1.060),
            (0.50, 1.061),
            (0.55, 1.061),
            (0.60, 1.062),
            (0.65, 1.064),
            (0.70, 1.066),
            (0.75, 1.069),
            (0.80, 1.073),
            (0.85, 1.077),
            (0.90, 1.083),
            (0.95, 1.090),
            (1.00, 1.097),
            (1.05, 1.106),
            (1.10, 1.116),
            (1.15, 1.126),
            (1.20, 1.138),
            (1.25, 1.150),
            (1.30, 1.162),
            (1.35, 1.175),
            (1.40, 1.189),
            (1.45, 1.203),
            (1.50, 1.217),
            (1.55, 1.231),
            (1.60, 1.246),
            (1.65, 1.261),
            (1.70, 1.275),
            (1.75, 1.290),
            (1.80, 1.305),
            (1.85, 1.320),
            (1.90, 1.334),
            (1.95, 1.349),
            (2.00, 1.363),
            (2.05, 1.378),
            (2.10, 1.392),
            (2.15, 1.407),
            (2.20, 1.421),
            (2.25, 1.435),
            (2.30, 1.449),
            (2.35, 1.462),
            (2.40, 1.476),
            (2.45, 1.490),
            (2.50, 1.503),
            (2.55, 1.516),
            (2.60, 1.529),
            (2.65, 1.542),
            (2.70, 1.555),
            (2.75, 1.568),
            (2.80, 1.580),
            (2.85, 1.593),
            (2.90, 1.605),
            (2.95, 1.617),
            (3.00, 1.630)
        };

        public static double CumulativeOverload(GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input)
        {
            double upperLimitWaveRunup = UpperLimitWaveRunup(input.IncreasedLoadTransitionAlphaM,
                                                             input.ReducedStrengthTransitionAlphaS,
                                                             input.FrontVelocityCu,
                                                             input.CriticalFrontVelocity,
                                                             input.GravitationalAcceleration);

            double lowerLimitWaveRunup = LowerLimitWaveRunup(input.VerticalDistanceWaterLevelElevation,
                                                             upperLimitWaveRunup);

            double waveRunupTransition = WaveRunupTransition(input.SlopeForeshore,
                                                             input.RepresentativeWaveRunup2P,
                                                             input.WaveHeightHm0,
                                                             input.WaterLevel,
                                                             input.BottomForeshoreZ);

            double rootMeanSquareWaveRunup = RootMeanSquareWaveRunup(input.RepresentativeWaveRunup2P,
                                                                     input.WaveHeightHm0,
                                                                     input.WaterLevel,
                                                                     input.BottomForeshoreZ);

            double scalingParameterRu1 = ScalingParameterRu(waveRunupTransition, rootMeanSquareWaveRunup, LambdaRu1);

            double scalingParameterRu2 = ScalingParameterRu(waveRunupTransition, rootMeanSquareWaveRunup, LambdaRu2);

            double verticalLimitWaveRunUp1 = VerticalWaveRunupLimit1(input.VerticalDistanceWaterLevelElevation,
                                                                     upperLimitWaveRunup,
                                                                     waveRunupTransition);

            double cumulativeOverLoad1 = DeltaCumulativeLoad(input, verticalLimitWaveRunUp1, scalingParameterRu1, input.K1);

            double verticalLimitWaveRunUp2 = VerticalWaveRunupLimit2(input.VerticalDistanceWaterLevelElevation, upperLimitWaveRunup);

            double cumulativeOverLoad2 = DeltaCumulativeLoad(input, verticalLimitWaveRunUp2, scalingParameterRu1, input.K1);

            double cumulativeOverLoad3 = DeltaCumulativeLoad(input, verticalLimitWaveRunup3, scalingParameterRu2, input.K2);

            double cumulativeOverLoad4 = DeltaCumulativeLoad(input, verticalLimitWaveRunUp1, scalingParameterRu2, input.K2);

            double verticalLimitWaveRunup5 = VerticalWaveRunupLimit5(input.VerticalDistanceWaterLevelElevation,
                                                                     lowerLimitWaveRunup, waveRunupTransition);

            double cumulativeOverLoad5 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalLimitWaveRunup5, scalingParameterRu1, input.K1);

            double verticalLimitWaveRunup6 = VerticalWaveRunupLimit6(input.VerticalDistanceWaterLevelElevation, lowerLimitWaveRunup);
            double cumulativeOverLoad6 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalLimitWaveRunup6, scalingParameterRu1, input.K1);

            double verticalLimitWaveRunup7 = ScaledVerticalDistanceWaterLevelElevation(input.VerticalDistanceWaterLevelElevation);
            double cumulativeOverLoad7 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalLimitWaveRunup7, scalingParameterRu2, input.K2);

            double cumulativeOverLoad8 =
                DeltaCumulativeLoadWithVerticalDistanceWaterLevel(input, verticalLimitWaveRunup5, scalingParameterRu2, input.K2);

            return input.AverageNumberOfWaves * (cumulativeOverLoad1 - cumulativeOverLoad2 +
                                                 cumulativeOverLoad3 - cumulativeOverLoad4 +
                                                 cumulativeOverLoad5 - cumulativeOverLoad6 +
                                                 cumulativeOverLoad7 - cumulativeOverLoad8);
        }

        private static double VerticalWaveRunupLimit1(double verticalDistanceWaterLevelElevation, double upperLimitWaveRunup,
                                                      double waveRunupTransition)
        {
            return Math.Max(VerticalWaveRunupLimit2(verticalDistanceWaterLevelElevation, upperLimitWaveRunup), waveRunupTransition);
        }

        private static double VerticalWaveRunupLimit2(double verticalDistanceWaterLevelElevation, double upperLimitWaveRunup)
        {
            return Math.Max(ScaledVerticalDistanceWaterLevelElevation(verticalDistanceWaterLevelElevation), upperLimitWaveRunup);
        }

        private static double VerticalWaveRunupLimit5(double verticalDistanceWaterLevelElevation, double lowerLimitWaveRunup,
                                                      double waveRunupTransition)
        {
            double scaledVerticalDistancesWaterLevelElevation =
                ScaledVerticalDistanceWaterLevelElevation(verticalDistanceWaterLevelElevation);

            return Math.Max(VerticalWaveRunupLimit6(verticalDistanceWaterLevelElevation, lowerLimitWaveRunup),
                            Math.Min(scaledVerticalDistancesWaterLevelElevation, waveRunupTransition));
        }

        private static double VerticalWaveRunupLimit6(double verticalDistanceWaterLevelElevation, double lowerLimitWaveRunup)
        {
            double scaledVerticalDistanceWaterLevelElevation =
                ScaledVerticalDistanceWaterLevelElevation(verticalDistanceWaterLevelElevation);

            return Math.Max(Math.Min(scaledVerticalDistanceWaterLevelElevation, lowerLimitWaveRunup),
                            verticalDistanceWaterLevelElevation);
        }

        private static double ScaledVerticalDistanceWaterLevelElevation(double verticalDistanceWaterLevelElevation)
        {
            return (4.0 / 3.0) * verticalDistanceWaterLevelElevation;
        }

        private static double DeltaCumulativeLoad(GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input,
                                                  double verticalWaveRunupLimit, double scalingParameterRu, double k)
        {
            return input.IncreasedLoadTransitionAlphaM * Math.Pow(input.FrontVelocityCu, 2) * input.GravitationalAcceleration *
                   scalingParameterRu * ProbabilityBattjesGroenendijkAnalytical(k, verticalWaveRunupLimit / scalingParameterRu) +
                   ((input.ReducedStrengthTransitionAlphaS * Math.Pow(input.CriticalFrontVelocity, 2)) / k) *
                   Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k));
        }

        private static double DeltaCumulativeLoadWithVerticalDistanceWaterLevel(
            GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput input,
            double verticalWaveRunupLimit, double scalingParameterRu, double k)
        {
            return input.IncreasedLoadTransitionAlphaM * Math.Pow(input.FrontVelocityCu, 2) * input.GravitationalAcceleration * k *
                   ((4.0 * scalingParameterRu) / k *
                    ProbabilityBattjesGroenendijkAnalytical(k, verticalWaveRunupLimit / scalingParameterRu) +
                    ((4.0 * input.VerticalDistanceWaterLevelElevation) / k) *
                    Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k))) +
                   ((input.ReducedStrengthTransitionAlphaS * Math.Pow(input.CriticalFrontVelocity, 2)) / k) *
                   Math.Exp(-Math.Pow(verticalWaveRunupLimit / scalingParameterRu, k));
        }

        private static double ProbabilityBattjesGroenendijkAnalytical(double xi, double eta)
        {
            double probability = SpecialFunctions.GammaLowerRegularized(1 + 1 / xi, Math.Pow(eta, xi));

            double gammaNominator = SpecialFunctions.Gamma(1 + 1 / xi);

            double gammaDenominator = SpecialFunctions.Gamma(2 + 1 / xi);

            return (gammaNominator * probability) / gammaDenominator +
                   (gammaNominator * probability) / (xi * gammaDenominator);
        }

        private static double ScalingParameterRu(double waveRunupTransition, double rootMeanSquareWaveRunup,
                                                 Func<double, double> getLambdaRuFunc)
        {
            return rootMeanSquareWaveRunup * getLambdaRuFunc(waveRunupTransition / rootMeanSquareWaveRunup);
        }

        private static double LambdaRu1(double kappa)
        {
            if (kappa > 3.0)
            {
                return 1.0;
            }

            IInterpolation interpolator = Interpolate.Linear(lambdasRu1.Select(x => x.Item1), lambdasRu1.Select(x => x.Item2));

            return interpolator.Interpolate(kappa);
        }

        private static double LambdaRu2(double kappa)
        {
            if (kappa > 3.0)
            {
                return Math.Pow(kappa, 4.0 / 9.0);
            }

            IInterpolation interpolator = Interpolate.Linear(lambdasRu2.Select(x => x.Item1), lambdasRu2.Select(x => x.Item2));

            return interpolator.Interpolate(kappa);
        }

        private static double RootMeanSquareWaveRunup(double representativeWaveRunup2P, double waveHeightHm0, double waterLevel,
                                                      double bottomForeshoreZ)
        {
            double depthForeshore = DepthForeshore(waterLevel, bottomForeshoreZ);

            return (0.6725 + 0.2025 * waveHeightHm0 / depthForeshore) * (representativeWaveRunup2P / 1.4);
        }

        private static double WaveRunupTransition(double slopeForeshore, double representativeWaveRunup2P, double waveHeightHm0,
                                                  double waterLevel, double bottomForeshoreZ)
        {
            double depthForeshore = DepthForeshore(waterLevel, bottomForeshoreZ);

            return (0.35 + 5.8 * slopeForeshore) * depthForeshore * representativeWaveRunup2P / (1.4 * waveHeightHm0);
        }

        private static double DepthForeshore(double waterLevel, double bottomForeshoreZ)
        {
            return waterLevel - bottomForeshoreZ;
        }

        private static double UpperLimitWaveRunup(double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
                                                  double frontVelocityCu, double criticalFrontVelocity, double gravitationalAcceleration)
        {
            return (reducedStrengthTransitionAlphaS / increasedLoadTransitionAlphaM) *
                   (Math.Pow(criticalFrontVelocity, 2) / (Math.Pow(frontVelocityCu, 2) * gravitationalAcceleration));
        }

        private static double LowerLimitWaveRunup(double verticalWaterLevelDistance, double upperLimitWaveRunup)
        {
            return (1 / 32.0) * (32 * verticalWaterLevelDistance + upperLimitWaveRunup +
                                 Math.Sqrt(upperLimitWaveRunup) * Math.Sqrt(64 * verticalWaterLevelDistance + upperLimitWaveRunup));
        }
    }
}
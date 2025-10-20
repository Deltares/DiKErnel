// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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

namespace DiKErnel.FunctionLibrary.NaturalStoneWaveImpact
{
    /// <summary>
    /// Class that holds natural stone wave impact calculation routines.
    /// </summary>
    public static class NaturalStoneWaveImpactFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="hydraulicLoad">The hydraulic load [m].</param>
        /// <param name="resistance">The resistance [m].</param>
        /// <param name="incrementDegradation">The increment of degradation [-].</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle [-].</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(double hydraulicLoad, double resistance, double incrementDegradation,
                                             double waveAngleImpact)
        {
            return hydraulicLoad / resistance * incrementDegradation * waveAngleImpact;
        }

        /// <summary>
        /// Calculates the hydraulic load.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The hydraulic load [m].</returns>
        public static double HydraulicLoad(NaturalStoneWaveImpactHydraulicLoadInput input)
        {
            return input.WaveHeightHm0 / (input.A * Math.Pow(input.SurfSimilarityParameter, input.N)
                                          + input.B * input.SurfSimilarityParameter
                                          + input.C);
        }

        /// <summary>
        /// Calculates the outer slope.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The outer slope [-].</returns>
        public static double OuterSlope(NaturalStoneWaveImpactOuterSlopeInput input)
        {
            return !HasBerm(input)
                       ? SingleSlopePart(input.SlopeUpperLevel, input.SlopeLowerLevel, input.SlopeUpperPosition,
                                         input.SlopeLowerPosition)
                       : OuterSlopeWithBerm(input);
        }

        /// <summary>
        /// Calculates the slope upper level.
        /// </summary>
        /// <param name="outerToeHeight">The height of the outer toe [m].</param>
        /// <param name="outerCrestHeight">The height of the outer crest [m].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="slopeUpperLevelAus">The Aus coefficient [-].</param>
        /// <returns>The slope upper level [m].</returns>
        public static double SlopeUpperLevel(double outerToeHeight, double outerCrestHeight, double waterLevel,
                                             double waveHeightHm0, double slopeUpperLevelAus)
        {
            return Math.Min(outerCrestHeight, Math.Max(waterLevel, outerToeHeight + slopeUpperLevelAus * waveHeightHm0));
        }

        /// <summary>
        /// Calculates the slope lower level.
        /// </summary>
        /// <param name="outerToeHeight">The height of the outer toe [m].</param>
        /// <param name="slopeUpperLevel">The slope upper level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="slopeLowerLevelAls">The Als coefficient [-].</param>
        /// <returns>The slope lower level [m].</returns>
        public static double SlopeLowerLevel(double outerToeHeight, double slopeUpperLevel, double waveHeightHm0,
                                             double slopeLowerLevelAls)
        {
            return Math.Max(outerToeHeight, slopeUpperLevel - slopeLowerLevelAls * waveHeightHm0);
        }

        /// <summary>
        /// Calculates the upper limit of loading.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The upper limit of loading [m].</returns>
        public static double UpperLimitLoading(NaturalStoneWaveImpactLimitLoadingInput input)
        {
            return input.WaterLevel - 2 * input.DepthMaximumWaveLoad
                   + Math.Max(input.DepthMaximumWaveLoad + input.A,
                              input.B * input.WaveHeightHm0 * Math.Min(input.SurfSimilarityParameter, input.C));
        }

        /// <summary>
        /// Calculates the lower limit of loading.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The lower limit of loading [m].</returns>
        public static double LowerLimitLoading(NaturalStoneWaveImpactLimitLoadingInput input)
        {
            return input.WaterLevel
                   - 2 * input.DepthMaximumWaveLoad
                   + Math.Min(input.DepthMaximumWaveLoad - input.A,
                              input.B * input.WaveHeightHm0 * Math.Min(input.SurfSimilarityParameter, input.C));
        }

        /// <summary>
        /// Calculates the depth of the maximum wave load.
        /// </summary>
        /// <param name="distanceMaximumWaveElevation">The maximum distance of wave
        /// elevation [m].</param>
        /// <param name="normativeWidthWaveImpact">The normative width of wave
        /// impact [m].</param>
        /// <param name="slopeAngle">The slope angle [deg].</param>
        /// <returns>The depth of the maximum wave load [m].</returns>
        public static double DepthMaximumWaveLoad(double distanceMaximumWaveElevation, double normativeWidthWaveImpact,
                                                  double slopeAngle)
        {
            double slopeAngleRadians = GenericFunctions.Radians(slopeAngle);

            return (distanceMaximumWaveElevation - 0.5 * normativeWidthWaveImpact * Math.Cos(slopeAngleRadians))
                   * Math.Tan(slopeAngleRadians);
        }

        /// <summary>
        /// Calculates the maximum distance of wave elevation.
        /// </summary>
        /// <param name="impactShallowWater">The impact in shallow water [-].</param>
        /// <param name="waveSteepnessDeepWater">The wave steepness in deep
        /// water [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="distanceMaximumWaveElevationAsmax">The Asmax
        /// coefficient [-].</param>
        /// <param name="distanceMaximumWaveElevationBsmax">The Bsmax
        /// coefficient [-].</param>
        /// <returns>The maximum distance of wave elevation [m].</returns>
        public static double DistanceMaximumWaveElevation(double impactShallowWater, double waveSteepnessDeepWater,
                                                          double waveHeightHm0, double distanceMaximumWaveElevationAsmax,
                                                          double distanceMaximumWaveElevationBsmax)
        {
            return waveHeightHm0
                   * (distanceMaximumWaveElevationAsmax / Math.Sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationBsmax)
                   * impactShallowWater;
        }

        /// <summary>
        /// Calculates the normative width of wave impact.
        /// </summary>
        /// <param name="surfSimilarityParameter">The surf similarity parameter [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="normativeWidthWaveImpactAwi">The Awi coefficient [-].</param>
        /// <param name="normativeWidthWaveImpactBwi">The Bwi coefficient [-].</param>
        /// <returns>The normative width of wave impact [m].</returns>
        public static double NormativeWidthWaveImpact(double surfSimilarityParameter, double waveHeightHm0,
                                                      double normativeWidthWaveImpactAwi, double normativeWidthWaveImpactBwi)
        {
            return (normativeWidthWaveImpactAwi - normativeWidthWaveImpactBwi * surfSimilarityParameter) * waveHeightHm0;
        }

        /// <summary>
        /// Calculates the wave impact with respect to the wave angle.
        /// </summary>
        /// <param name="waveAngle">The wave angle [deg].</param>
        /// <param name="waveAngleImpactBetamax">The Betamax coefficient [deg].</param>
        /// <returns>The wave impact with respect to the wave angle [-].</returns>
        public static double WaveAngleImpact(double waveAngle, double waveAngleImpactBetamax)
        {
            return Math.Pow(Math.Cos(GenericFunctions.Radians(Math.Min(waveAngleImpactBetamax, Math.Abs(waveAngle)))), 2d / 3);
        }

        /// <summary>
        /// Calculates the resistance.
        /// </summary>
        /// <param name="relativeDensity">The relative density [-].</param>
        /// <param name="thicknessTopLayer">The thickness of the top layer [m].</param>
        /// <returns>The resistance [m].</returns>
        public static double Resistance(double relativeDensity, double thicknessTopLayer)
        {
            return relativeDensity * thicknessTopLayer;
        }

        /// <summary>
        /// Calculates the increment of degradation.
        /// </summary>
        /// <param name="referenceTimeDegradation">The reference time of
        /// degradation [s].</param>
        /// <param name="incrementTime">The increment of time [s].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <returns>The increment of degradation [-].</returns>
        public static double IncrementDegradation(double referenceTimeDegradation, double incrementTime, double wavePeriodTm10)
        {
            return Degradation(referenceTimeDegradation + incrementTime, wavePeriodTm10)
                   - Degradation(referenceTimeDegradation, wavePeriodTm10);
        }

        /// <summary>
        /// Calculates the reference time of degradation.
        /// </summary>
        /// <param name="referenceDegradation">The reference of degradation [-].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <returns>The reference time of degradation [s].</returns>
        public static double ReferenceTimeDegradation(double referenceDegradation, double wavePeriodTm10)
        {
            return ReferenceTime(referenceDegradation, wavePeriodTm10);
        }

        /// <summary>
        /// Calculates the reference of degradation.
        /// </summary>
        /// <param name="resistance">The resistance [m].</param>
        /// <param name="hydraulicLoad">The hydraulic load [m].</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle [-].</param>
        /// <param name="initialDamage">The initial damage [-].</param>
        /// <returns>The reference of degradation [-].</returns>
        public static double ReferenceDegradation(double resistance, double hydraulicLoad, double waveAngleImpact,
                                                  double initialDamage)
        {
            return Reference(resistance, hydraulicLoad, waveAngleImpact, initialDamage);
        }

        /// <summary>
        /// Calculates the duration in the time step of failure.
        /// </summary>
        /// <param name="referenceTimeFailure">The reference time of failure [s].</param>
        /// <param name="referenceTimeDegradation">The reference time of
        /// degradation [s].</param>
        /// <returns>The duration in the time step of failure [s].</returns>
        public static double DurationInTimeStepFailure(double referenceTimeFailure, double referenceTimeDegradation)
        {
            return referenceTimeFailure - referenceTimeDegradation;
        }

        /// <summary>
        /// Calculates the reference time of failure.
        /// </summary>
        /// <param name="referenceFailure">The reference of failure [-].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <returns>The reference time of failure [s].</returns>
        public static double ReferenceTimeFailure(double referenceFailure, double wavePeriodTm10)
        {
            return ReferenceTime(referenceFailure, wavePeriodTm10);
        }

        /// <summary>
        /// Calculates the reference of failure.
        /// </summary>
        /// <param name="resistance">The resistance [m].</param>
        /// <param name="hydraulicLoad">The hydraulic load [m].</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle [-].</param>
        /// <param name="failureNumber">The failure number [-].</param>
        /// <returns>The reference of failure [-].</returns>
        public static double ReferenceFailure(double resistance, double hydraulicLoad, double waveAngleImpact,
                                              double failureNumber)
        {
            return Reference(resistance, hydraulicLoad, waveAngleImpact, failureNumber);
        }

        private static double SingleSlopePart(double slopeUpperLevel, double slopeLowerLevel, double slopeUpperPosition,
                                              double slopeLowerPosition)
        {
            return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
        }

        private static double OuterSlopeWithBerm(NaturalStoneWaveImpactOuterSlopeInput input)
        {
            bool slopeLowerLevelOnLowerSlope = input.OuterToeHeight <= input.SlopeLowerLevel
                                               && input.SlopeLowerLevel < input.CrestOuterBermHeight;
            bool slopeUpperLevelOnLowerSlope = input.OuterToeHeight <= input.SlopeUpperLevel
                                               && input.SlopeUpperLevel < input.CrestOuterBermHeight;
            bool slopeLowerLevelOnBerm = input.CrestOuterBermHeight <= input.SlopeLowerLevel
                                         && input.SlopeLowerLevel <= input.NotchOuterBermHeight;
            bool slopeUpperLevelOnBerm = input.CrestOuterBermHeight <= input.SlopeUpperLevel
                                         && input.SlopeUpperLevel <= input.NotchOuterBermHeight;
            bool slopeLowerLevelOnUpperSlope = input.NotchOuterBermHeight < input.SlopeLowerLevel
                                               && input.SlopeLowerLevel <= input.OuterCrestHeight;
            bool slopeUpperLevelOnUpperSlope = input.NotchOuterBermHeight < input.SlopeUpperLevel
                                               && input.SlopeUpperLevel <= input.OuterCrestHeight;

            return OuterSlopeWithBerm(input, slopeLowerLevelOnLowerSlope, slopeUpperLevelOnLowerSlope,
                                      slopeLowerLevelOnBerm, slopeUpperLevelOnBerm, slopeLowerLevelOnUpperSlope,
                                      slopeUpperLevelOnUpperSlope);
        }

        private static double OuterSlopeWithBerm(NaturalStoneWaveImpactOuterSlopeInput input,
                                                 bool slopeLowerLevelOnLowerSlope, bool slopeUpperLevelOnLowerSlope,
                                                 bool slopeLowerLevelOnBerm, bool slopeUpperLevelOnBerm,
                                                 bool slopeLowerLevelOnUpperSlope, bool slopeUpperLevelOnUpperSlope)
        {
            if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnLowerSlope
                || slopeLowerLevelOnBerm && slopeUpperLevelOnBerm
                || slopeLowerLevelOnUpperSlope && slopeUpperLevelOnUpperSlope)
            {
                return SingleSlopePart(input.SlopeUpperLevel, input.SlopeLowerLevel, input.SlopeUpperPosition,
                                       input.SlopeLowerPosition);
            }

            if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnBerm)
            {
                return SlopeLowerSlopeBerm(input.CrestOuterBermPosition, input.CrestOuterBermHeight, input.SlopeLowerLevel,
                                           input.SlopeLowerPosition);
            }

            if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnUpperSlope)
            {
                double distanceBermUpperSlope = DistanceBermUpperSlope(input.CrestOuterBermHeight, input.NotchOuterBermPosition,
                                                                       input.NotchOuterBermHeight, input.SlopeUpperLevel,
                                                                       input.SlopeUpperPosition);
                double distanceBermLowerSlope = DistanceBermLowerSlope(input.CrestOuterBermPosition, input.CrestOuterBermHeight,
                                                                       input.NotchOuterBermHeight, input.SlopeLowerLevel,
                                                                       input.SlopeLowerPosition);

                return SlopeLowerUpperSlope(input.SlopeUpperLevel, input.SlopeLowerLevel, distanceBermUpperSlope, distanceBermLowerSlope);
            }

            if (slopeLowerLevelOnBerm && slopeUpperLevelOnUpperSlope)
            {
                return SlopeBermUpperSlope(input.NotchOuterBermPosition, input.NotchOuterBermHeight, input.SlopeUpperLevel,
                                           input.SlopeUpperPosition);
            }

            return double.NaN;
        }

        private static double SlopeLowerSlopeBerm(double crestOuterBermPosition, double crestOuterBermHeight,
                                                  double slopeLowerLevel, double slopeLowerPosition)
        {
            return (crestOuterBermHeight - slopeLowerLevel) / (crestOuterBermPosition - slopeLowerPosition);
        }

        private static double SlopeBermUpperSlope(double notchOuterBermPosition, double notchOuterBermHeight, double slopeUpperLevel,
                                                  double slopeUpperPosition)
        {
            return (slopeUpperLevel - notchOuterBermHeight) / (slopeUpperPosition - notchOuterBermPosition);
        }

        private static double SlopeLowerUpperSlope(double slopeUpperLevel, double slopeLowerLevel, double distanceBermUpperSlope,
                                                   double distanceBermLowerSlope)
        {
            return (slopeUpperLevel - slopeLowerLevel) / (distanceBermUpperSlope + distanceBermLowerSlope);
        }

        private static double DistanceBermUpperSlope(double crestOuterBermHeight, double notchOuterBermPosition,
                                                     double notchOuterBermHeight, double slopeUpperLevel,
                                                     double slopeUpperPosition)
        {
            return (slopeUpperLevel - 0.5 * (crestOuterBermHeight + notchOuterBermHeight))
                   * (slopeUpperPosition - notchOuterBermPosition) / (slopeUpperLevel - notchOuterBermHeight);
        }

        private static double DistanceBermLowerSlope(double crestOuterBermPosition, double crestOuterBermHeight,
                                                     double notchOuterBermHeight, double slopeLowerLevel,
                                                     double slopeLowerPosition)
        {
            return (0.5 * (crestOuterBermHeight + notchOuterBermHeight) - slopeLowerLevel)
                   * (crestOuterBermPosition - slopeLowerPosition) / (crestOuterBermHeight - slopeLowerLevel);
        }

        private static double Degradation(double referenceTimeDegradation, double wavePeriodTm10)
        {
            return Math.Pow(referenceTimeDegradation / (wavePeriodTm10 * 1000), 0.1);
        }

        private static double ReferenceTime(double reference, double wavePeriodTm10)
        {
            return 1000 * wavePeriodTm10 * Math.Pow(reference, 10);
        }

        private static double Reference(double resistance, double hydraulicLoad, double waveAngleImpact, double value)
        {
            return value * (resistance / hydraulicLoad) * (1 / waveAngleImpact);
        }

        private static bool HasBerm(NaturalStoneWaveImpactOuterSlopeInput input)
        {
            return !double.IsNaN(input.NotchOuterBermPosition)
                   && !double.IsNaN(input.NotchOuterBermHeight)
                   && !double.IsNaN(input.CrestOuterBermPosition)
                   && !double.IsNaN(input.CrestOuterBermHeight);
        }
    }
}
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

namespace DiKErnel.FunctionLibrary.NaturalStoneRevetment
{
    /// <summary>
    /// Class that holds all natural stone revetment specific calculation routines.
    /// </summary>
    public static class NaturalStoneRevetmentFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="hydraulicLoad">The hydraulic load. [m]</param>
        /// <param name="resistance">The resistance. [m]</param>
        /// <param name="incrementDegradation">The increment of degradation. [-]</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle. [-]</param>
        /// <returns>The increment of damage. [-]</returns>
        public static double IncrementDamage(double hydraulicLoad, double resistance, double incrementDegradation,
                                             double waveAngleImpact)
        {
            return hydraulicLoad / resistance * incrementDegradation * waveAngleImpact;
        }

        /// <summary>
        /// Calculates the hydraulic load.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The hydraulic load. [m]</returns>
        public static double HydraulicLoad(NaturalStoneRevetmentHydraulicLoadInput input)
        {
            return input.WaveHeightHm0 / (input.a * Math.Pow(input.SurfSimilarityParameter, input.n)
                                          + input.b * input.SurfSimilarityParameter
                                          + input.c);
        }

        /// <summary>
        /// Calculates the outer slope.
        /// </summary>
        /// <param name="input">The input to use for the calculation.</param>
        /// <returns>The outer slope. [-]</returns>
        public static double OuterSlope(NaturalStoneRevetmentOuterSlopeInput input)
        {
            return !input.HasBerm
                       ? SingleSlopePart(input.SlopeUpperLevel, input.SlopeLowerLevel,
                                         input.SlopeUpperPosition, input.SlopeLowerPosition)
                       : OuterSlopeWithBerm(input);
        }

        private static double SingleSlopePart(double slopeUpperLevel, double slopeLowerLevel, double slopeUpperPosition,
                                              double slopeLowerPosition)
        {
            return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
        }

        private static double OuterSlopeWithBerm(NaturalStoneRevetmentOuterSlopeInput input)
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

            return double.PositiveInfinity;
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
    }
}
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

namespace DiKErnel.FunctionLibrary.GrassWaveImpact
{
    /// <summary>
    /// Class that holds grass wave impact calculation routines.
    /// </summary>
    public static class GrassWaveImpactFunctions
    {
        /// <summary>
        /// Calculates the increment of damage.
        /// </summary>
        /// <param name="incrementTime">The increment of time [s].</param>
        /// <param name="timeLine">The time line [-].</param>
        /// <returns>The increment of damage [-].</returns>
        public static double IncrementDamage(double incrementTime, double timeLine)
        {
            return incrementTime / timeLine;
        }

        /// <summary>
        /// Calculates the time line.
        /// </summary>
        /// <param name="waveHeightImpact">The wave height with respect to the wave
        /// impact [m].</param>
        /// <param name="timeLineAgwi">The Agwi coefficient [m].</param>
        /// <param name="timeLineBgwi">The Bgwi coefficient [s^-1].</param>
        /// <param name="timeLineCgwi">The Cgwi coefficient [m].</param>
        /// <returns>The time line [-].</returns>
        public static double TimeLine(double waveHeightImpact, double timeLineAgwi, double timeLineBgwi, double timeLineCgwi)
        {
            return 1 / timeLineBgwi * Math.Log((waveHeightImpact - timeLineCgwi) / timeLineAgwi);
        }

        /// <summary>
        /// Calculates the wave height with respect to the wave impact.
        /// </summary>
        /// <param name="minimumWaveHeight">The minimum wave height [m].</param>
        /// <param name="maximumWaveHeight">The maximum wave height [m].</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <returns>The wave height with respect to the wave impact [m].</returns>
        public static double WaveHeightImpact(double minimumWaveHeight, double maximumWaveHeight, double waveAngleImpact,
                                              double waveHeightHm0)
        {
            return Math.Min(maximumWaveHeight, Math.Max(waveAngleImpact * waveHeightHm0, minimumWaveHeight));
        }

        /// <summary>
        /// Calculates the minimum wave height.
        /// </summary>
        /// <param name="timeLineAgwi">The Agwi coefficient [m].</param>
        /// <param name="timeLineBgwi">The Bgwi coefficient [s^-1].</param>
        /// <param name="timeLineCgwi">The Cgwi coefficient [m].</param>
        /// <param name="minimumWaveHeightTemax">The Temax coefficient [s].</param>
        /// <returns>The minimum wave height [m].</returns>
        public static double MinimumWaveHeight(double timeLineAgwi, double timeLineBgwi, double timeLineCgwi,
                                               double minimumWaveHeightTemax)
        {
            return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, minimumWaveHeightTemax);
        }

        /// <summary>
        /// Calculates the maximum wave height.
        /// </summary>
        /// <param name="timeLineAgwi">The Agwi coefficient [m].</param>
        /// <param name="timeLineBgwi">The Bgwi coefficient [s^-1].</param>
        /// <param name="timeLineCgwi">The Cgwi coefficient [m].</param>
        /// <param name="maximumWaveHeightTemin">The Temin coefficient [s].</param>
        /// <returns>The maximum wave height [m].</returns>
        public static double MaximumWaveHeight(double timeLineAgwi, double timeLineBgwi, double timeLineCgwi,
                                               double maximumWaveHeightTemin)
        {
            return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, maximumWaveHeightTemin);
        }

        /// <summary>
        /// Calculates the wave impact with respect to the wave angle.
        /// </summary>
        /// <param name="waveAngle">The wave angle [deg].</param>
        /// <param name="waveAngleImpactNwa">The Nwa coefficient [-].</param>
        /// <param name="waveAngleImpactQwa">The Qwa coefficient [-].</param>
        /// <param name="waveAngleImpactRwa">The Rwa coefficient [-].</param>
        /// <returns>The wave impact with respect to the wave angle [-].</returns>
        public static double WaveAngleImpact(double waveAngle, double waveAngleImpactNwa, double waveAngleImpactQwa,
                                             double waveAngleImpactRwa)
        {
            if (Math.Abs(waveAngle) <= 90d)
            {
                return Math.Max(Math.Pow(Math.Cos(GenericFunctions.Radians(waveAngle)), waveAngleImpactNwa), waveAngleImpactQwa);
            }

            return Math.Max(waveAngleImpactQwa * ((90 + waveAngleImpactRwa - Math.Abs(waveAngle)) / waveAngleImpactRwa), 0);
        }

        /// <summary>
        /// Calculates the upper limit of loading.
        /// </summary>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="upperLimitLoadingAul">The Aul coefficient [-].</param>
        /// <returns>The upper limit of loading [m].</returns>
        public static double UpperLimitLoading(double waterLevel, double waveHeightHm0, double upperLimitLoadingAul)
        {
            return LimitLoading(waterLevel, waveHeightHm0, upperLimitLoadingAul);
        }

        /// <summary>
        /// Calculates the lower limit of loading.
        /// </summary>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="lowerLimitLoadingAll">The All coefficient [-].</param>
        /// <returns>The lower limit of loading [m].</returns>
        public static double LowerLimitLoading(double waterLevel, double waveHeightHm0, double lowerLimitLoadingAll)
        {
            return LimitLoading(waterLevel, waveHeightHm0, lowerLimitLoadingAll);
        }

        private static double WaveHeightBoundary(double timeLineAgwi, double timeLineBgwi, double timeLineCgwi,
                                                 double waveHeightCoefficient)
        {
            return timeLineAgwi * Math.Exp(timeLineBgwi * waveHeightCoefficient) + timeLineCgwi;
        }

        private static double LimitLoading(double waterLevel, double waveHeightHm0, double coefficientA)
        {
            return waterLevel - coefficientA * waveHeightHm0;
        }
    }
}
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

namespace DiKErnel.FunctionLibrary
{
    /// <summary>
    /// Class that holds generic hydraulic load calculation routines.
    /// </summary>
    public static class HydraulicLoadFunctions
    {
        /// <summary>
        /// Calculates the wave angle.
        /// </summary>
        /// <param name="waveDirection">The wave direction [deg].</param>
        /// <param name="dikeOrientation">The dike orientation [deg].</param>
        /// <returns>The wave angle [deg].</returns>
        public static double WaveAngle(double waveDirection, double dikeOrientation)
        {
            double waveAngle = waveDirection - dikeOrientation;

            if (waveAngle > 180d)
            {
                return waveAngle - 360;
            }

            if (waveAngle < -180d)
            {
                return waveAngle + 360;
            }

            return waveAngle;
        }

        /// <summary>
        /// Calculates the slope angle.
        /// </summary>
        /// <param name="outerSlope">The outer slope [-].</param>
        /// <returns>The slope angle [deg].</returns>
        public static double SlopeAngle(double outerSlope)
        {
            return GenericFunctions.Degrees(Math.Atan(outerSlope));
        }

        /// <summary>
        /// Calculates whether there is loading of the revetment.
        /// </summary>
        /// <param name="lowerLimitLoadingRevetment">The lower limit of loading [m].</param>
        /// <param name="upperLimitLoadingRevetment">The upper limit of loading [m].</param>
        /// <param name="z">The z coordinate [m].</param>
        /// <returns>Whether there is loading of the revetment.</returns>
        public static bool LoadingRevetment(double lowerLimitLoadingRevetment, double upperLimitLoadingRevetment, double z)
        {
            return z >= lowerLimitLoadingRevetment && z <= upperLimitLoadingRevetment;
        }

        /// <summary>
        /// Calculates the surf similarity parameter.
        /// </summary>
        /// <param name="outerSlope">The outer slope [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <param name="gravitationalAcceleration">The gravitational acceleration [m/s^2].</param>
        /// <returns>The surf similarity parameter [-].</returns>
        public static double SurfSimilarityParameter(double outerSlope, double waveHeightHm0, double wavePeriodTm10,
                                                     double gravitationalAcceleration)
        {
            return outerSlope / Math.Sqrt(2 * Math.PI * waveHeightHm0 / (gravitationalAcceleration * wavePeriodTm10 * wavePeriodTm10));
        }

        /// <summary>
        /// Calculates the wave steepness in deep water.
        /// </summary>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <param name="gravitationalAcceleration">The gravitational accelerations [m/s^2].</param>
        /// <returns>The wave steepness in deep water [-].</returns>
        public static double WaveSteepnessDeepWater(double waveHeightHm0, double wavePeriodTm10, double gravitationalAcceleration)
        {
            return waveHeightHm0 / (gravitationalAcceleration / (2 * Math.PI) * wavePeriodTm10 * wavePeriodTm10);
        }

        /// <summary>
        /// Calculates the vertical distance of the water elevation.
        /// </summary>
        /// <param name="z">The z coordinate [m].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <returns>The vertical distance of the water elevation [m].</returns>
        public static double VerticalDistanceWaterLevelElevation(double z, double waterLevel)
        {
            return z - waterLevel;
        }
    }
}
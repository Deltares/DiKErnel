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

namespace DiKErnel.FunctionLibrary
{
    /// <summary>
    /// Class that holds all generic hydraulic load calculation routines.
    /// </summary>
    public static class HydraulicLoadFunctions
    {
        /// <summary>
        /// Calculates the wave direction.
        /// </summary>
        /// <param name="waveAngle">The wave angle. [deg]</param>
        /// <returns>The wave direction. [deg]</returns>
        public static double WaveDirection(double waveAngle)
        {
            if (waveAngle >= -180 && waveAngle < 0)
            {
                return 360 - Math.Abs(waveAngle);
            }

            return waveAngle;
        }

        /// <summary>
        /// Calculates the slope angle.
        /// </summary>
        /// <param name="outerSlope">The outer slope. [-]</param>
        /// <returns>The slope angle. [deg]</returns>
        public static double SlopeAngle(double outerSlope)
        {
            return GenericFunctions.Degrees(Math.Atan(outerSlope));
        }

        /// <summary>
        /// Calculates whether there is loading of the revetment.
        /// </summary>
        /// <param name="lowerLimitLoadingRevetment">The lower limit of loading. [m]</param>
        /// <param name="upperLimitLoadingRevetment">The upper limit of loading. [m]</param>
        /// <param name="z">The z coordinate. [m]</param>
        /// <returns>Whether there is loading of the revetment</returns>
        public static bool LoadingRevetment(double lowerLimitLoadingRevetment,
                                            double upperLimitLoadingRevetment,
                                            double z)
        {
            return z >= lowerLimitLoadingRevetment && z <= upperLimitLoadingRevetment;
        }

        /// <summary>
        /// Calculates the surf similarity parameter.
        /// </summary>
        /// <param name="outerSlope">The outer slope. [-]</param>
        /// <param name="waveHeightHm0">The wave height. [m]</param>
        /// <param name="wavePeriodTm10">The wave period. [s]</param>
        /// <param name="gravitationalAcceleration">The gravitational acceleration. [m/s^2]</param>
        /// <returns>The surf similarity parameter. [-]</returns>
        public static double SurfSimilarityParameter(double outerSlope, double waveHeightHm0, double wavePeriodTm10,
                                                     double gravitationalAcceleration)
        {
            return outerSlope / Math.Sqrt(2.0 * Math.PI * waveHeightHm0 / (gravitationalAcceleration * Math.Pow(wavePeriodTm10, 2.0)));
        }

        /// <summary>
        /// Calculates the wave steepness in deep water.
        /// </summary>
        /// <param name="waveHeightHm0">The wave height. [m]</param>
        /// <param name="wavePeriodTm10">The wave period. [s]</param>
        /// <param name="gravitationalAcceleration">The gravitational accelerations. [m/s^2]</param>
        /// <returns>The wave steepness in deep water. [-]</returns>
        public static double WaveSteepnessDeepWater(double waveHeightHm0, double wavePeriodTm10, double gravitationalAcceleration)
        {
            return waveHeightHm0 / (gravitationalAcceleration / (2.0 * Math.PI) * Math.Pow(wavePeriodTm10, 2.0));
        }

        /// <summary>
        /// Calculates the vertical distance of the water elevation. 
        /// </summary>
        /// <param name="z">The z coordinate. [m]</param>
        /// <param name="waterLevel">The water level. [m]</param>
        /// <returns>The vertical distance of the water elevation. [m]</returns>
        public static double VerticalWaterDistanceWaterLevelElevation(double z, double waterLevel)
        {
            return z - waterLevel;
        }
    }
}
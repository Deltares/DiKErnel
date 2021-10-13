// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all generic hydraulic load calculation routines.
     */
    class HydraulicLoad
    {
        public:
            /*!
             * \brief Calculates the slope angle.
             * \param outerSlope
             *        The outer slope.
             *        Unit = [-]
             * \return The slope angle.
             *         Unit = [deg]
             */
            static double SlopeAngle(
                double outerSlope);

            /*!
             * \brief Calculates whether there is loading of the revetment.
             * \param lowerLimitLoadingRevetment
             *        The lower limit of loading.
             *        Unit = [m]
             * \param upperLimitLoadingRevetment
             *        The upper limit of loading.
             *        Unit = [m]
             * \param z
             *        The vertical position.
             *        Unit = [m]
             * \return Whether there is loading of the revetment.
             */
            static bool LoadingRevetment(
                double lowerLimitLoadingRevetment,
                double upperLimitLoadingRevetment,
                double z);

            /*!
             * \brief Calculates the surf similarity parameter.
             * \param outerSlope
             *        The outer slope.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \param gravitationalAcceleration
             *        The gravitational acceleration.
             *        Unit = [m/s^2]
             * \return The surf similarity parameter.
             *         Unit = [-]
             */
            static double SurfSimilarityParameter(
                double outerSlope,
                double waveHeightHm0,
                double wavePeriodTm10,
                double gravitationalAcceleration);

            /*!
             * \brief Calculates the wave steepness in deep water.
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \param gravitationalAcceleration
             *        The gravitational acceleration.
             *        Unit = [m/s^2]
             * \return The wave steepness in deep water.
             *         Unit = [-]
             */
            static double WaveSteepnessDeepWater(
                double waveHeightHm0,
                double wavePeriodTm10,
                double gravitationalAcceleration);

            /*!
             * \brief Calculates the vertical distance of the water elevation.
             * \param z
             *        The vertical position.
             *        Unit = [m]
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \return The vertical distance of the water elevation.
             *         Unit = [m]
             */
            static double VerticalDistanceWaterLevelElevation(
                double z,
                double waterLevel);
    };
}

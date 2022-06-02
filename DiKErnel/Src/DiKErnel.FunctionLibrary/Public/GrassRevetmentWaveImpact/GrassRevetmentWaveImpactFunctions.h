// Copyright (C) Stichting Deltares 2022. All rights reserved.
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
     * \brief Class that holds all grass revetment wave impact specific calculation routines.
     */
    class GrassRevetmentWaveImpactFunctions
    {
        public:
            /*!
             * \brief Calculates the increment of damage.
             * \param incrementTime
             *        The increment of time.
             *        Unit = [s]
             * \param timeLine
             *        The time line.
             *        Unit = [-]
             * \return The increment of damage.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double IncrementDamage(
                double incrementTime,
                double timeLine);

            /*!
             * \brief Calculates the time line.
             * \param waveHeightImpact
             *        The wave height with respect to the wave impact.
             *        Unit = [m]
             * \param timeLineAgwi
             *        The Agwi coefficient.
             *        Unit = [m]
             * \param timeLineBgwi
             *        The Bgwi coefficient.
             *        Unit = [s^-1]
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             *        Unit = [m]
             * \return The time line.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double TimeLine(
                double waveHeightImpact,
                double timeLineAgwi,
                double timeLineBgwi,
                double timeLineCgwi);

            /*!
             * \brief Calculates the wave height with respect to the wave impact.
             * \param minimumWaveHeight
             *        The minimum wave height.
             *        Unit = [m]
             * \param maximumWaveHeight
             *        The maximum wave height.
             *        Unit = [m]
             * \param waveAngleImpact
             *        The wave impact with respect to the wave angle.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \return The wave height with respect to the wave impact.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double WaveHeightImpact(
                double minimumWaveHeight,
                double maximumWaveHeight,
                double waveAngleImpact,
                double waveHeightHm0);

            /*!
             * \brief Calculates the minimum wave height.
             * \param timeLineAgwi
             *        The Agwi coefficient.
             *        Unit = [m]
             * \param timeLineBgwi
             *        The Bgwi coefficient.
             *        Unit = [s^-1]
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             *        Unit = [m]
             * \param minimumWaveHeightTemax
             *        The Temax coefficient.
             *        Unit = [s]
             * \return The minimum wave height.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double MinimumWaveHeight(
                double timeLineAgwi,
                double timeLineBgwi,
                double timeLineCgwi,
                double minimumWaveHeightTemax);

            /*!
             * \brief Calculates the maximum wave height.
             * \param timeLineAgwi
             *        The Agwi coefficient.
             *        Unit = [m]
             * \param timeLineBgwi
             *        The Bgwi coefficient.
             *        Unit = [s^-1]
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             *        Unit = [m]
             * \param maximumWaveHeightTemin
             *        The Temin coefficient.
             *        Unit = [s]
             * \return The maximum wave height.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double MaximumWaveHeight(
                double timeLineAgwi,
                double timeLineBgwi,
                double timeLineCgwi,
                double maximumWaveHeightTemin);

            /*!
             * \brief Calculates the wave impact with respect to the wave angle.
             * \param waveAngle
             *        The wave angle.
             *        Unit = [deg]
             * \param waveAngleImpactNwa
             *        The Nwa coefficient.
             *        Unit = [-]
             * \param waveAngleImpactQwa
             *        The Qwa coefficient.
             *        Unit = [-]
             * \param waveAngleImpactRwa
             *        The Rwa coefficient.
             *        Unit = [-]
             * \return The wave impact with respect to the wave angle.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double WaveAngleImpact(
                double waveAngle,
                double waveAngleImpactNwa,
                double waveAngleImpactQwa,
                double waveAngleImpactRwa);

            /*!
             * \brief Calculates the upper limit of loading.
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             *        Unit = [-]
             * \return The upper limit of loading.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double UpperLimitLoading(
                double waterLevel,
                double waveHeightHm0,
                double upperLimitLoadingAul);

            /*!
             * \brief Calculates the lower limit of loading.
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             *        Unit = [-]
             * \return The lower limit of loading.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double LowerLimitLoading(
                double waterLevel,
                double waveHeightHm0,
                double lowerLimitLoadingAll);

        private:
            [[nodiscard]]
            static double WaveHeightBoundary(
                double timeLineAgwi,
                double timeLineBgwi,
                double timeLineCgwi,
                double waveHeightCoefficient);

            [[nodiscard]]
            static double LimitLoading(
                double waterLevel,
                double waveHeightHm0,
                double coefficientA);
    };
}

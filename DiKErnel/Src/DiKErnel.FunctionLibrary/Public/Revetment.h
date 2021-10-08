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

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all generic revetment calculation routines.
     */
    class Revetment
    {
        public:
            /*!
             * \brief Calculates the increment of time.
             * \param beginTime
             *        The begin time.
             *        Unit = [s]
             * \param endTime
             *        The end time.
             *        Unit = [s]
             * \return The increment of time.
             *         Unit = [s]
             */
            static int IncrementTime(
                int beginTime,
                int endTime);

            /*!
             * \brief Calculates the average number of waves.
             * \param incrementTime
             *        The increment of time.
             *        Unit = [s]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \param averageNumberOfWavesCtm
             *        The Ctm coefficient.
             *        Unit = [-]
             * \return The average number of waves.
             *         Unit = [-]
             */
            static double AverageNumberOfWaves(
                double incrementTime,
                double wavePeriodTm10,
                double averageNumberOfWavesCtm);

            /*!
             * \brief Calculates the vertical height based on linear interpolation.
             * \param horizontalPosition
             *        The horizontal position.
             *        Unit = [m]
             * \param dikeProfile
             *        The dike profile.
             *        Unit = [-]
             * \return The vertical height or INFINITY when the horizontal position cannot be
             *         fitted with the dike profile.
             *         Unit = [m]
             */
            static double InterpolationVerticalHeight(
                double horizontalPosition,
                std::vector<std::pair<double, double>> dikeProfile);

            /*!
             * \brief Calculates the horizontal position based on linear interpolation.
             * \param verticalHeight
             *        The vertical height.
             *        Unit = [m]
             * \param dikeProfile
             *        The dike profile.
             *        Unit = [-]
             * \return The horizontal position or INFINITY when the vertical height cannot be
             *         fitted with the dike profile.
             *         Unit = [m]
             */
            static double InterpolationHorizontalPosition(
                double verticalHeight,
                std::vector<std::pair<double, double>> dikeProfile);

            /*!
             * \brief Calculates the damage.
             * \param incrementDamage
             *        The increment of damage.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return The damage.
             *         Unit = [-]
             */
            static double Damage(
                double incrementDamage,
                double initialDamage);

            /*!
             * \brief Calculates whether the revetment has failed or not.
             * \param damage
             *        The damage.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \param failureNumber
             *        The failure number.
             *        Unit = [-]
             * \return Whether the revetment has failed or not.
             */
            static bool FailureRevetment(
                double damage,
                double initialDamage,
                double failureNumber);

            /*!
             * \brief Calculates the duration in the time step of failure.
             * \param incrementTime
             *        The increment of time.
             *        Unit = [s]
             * \param incrementDamage
             *        The increment of damage.
             *        Unit = [-]
             * \param failureNumber
             *        The failure number.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return The duration in the time step of failure.
             *         Unit = [s]
             */
            static double DurationInTimeStepFailure(
                double incrementTime,
                double incrementDamage,
                double failureNumber,
                double initialDamage);

            /*!
             * \brief Calculates the time of failure.
             * \param durationInTimeStepFailure
             *        The duration in the time step of failure.
             *        Unit = [s]
             * \param beginTime
             *        The begin time.
             *        Unit = [s]
             * \return The time of failure.
             *         Unit = [s]
             */
            static int TimeOfFailure(
                double durationInTimeStepFailure,
                double beginTime);
    };
}

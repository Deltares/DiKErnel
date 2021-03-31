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
     * \brief Class that holds all generic revetment calculation routines.
     */
    class Revetment
    {
        public:
            /*!
             * \brief Calculates the increment of time.
             * \param startTime
             *        The start time.
             *        Unit = [s]
             * \param endTime
             *        The end time.
             *        Unit = [s]
             * \return The increment of time.
             *         Unit = [s]
             */
            static int IncrementTime(
                int startTime,
                int endTime);

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
    };
}

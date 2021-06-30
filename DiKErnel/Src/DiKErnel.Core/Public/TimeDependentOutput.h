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

#include <memory>

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing time dependent output of a location.
     */
    class TimeDependentOutput
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~TimeDependentOutput() = default;

            /*!
             * \brief Gets the increment damage.
             * \return The increment damage.
             */
            double GetIncrementDamage() const;

            /*!
             * \brief Gets the damage.
             * \return The damage.
             */
            double GetDamage() const;

            /*!
             * \brief Gets the time of failure.
             * \return The time of failure.
             */
            const int* GetTimeOfFailure() const;

        protected:
            /*!
             * \brief Creates a new instance.
             * \param incrementDamage
             *        The increment damage.
             * \param damage
             *        The damage.
             * \param timeOfFailure
             *        The time of failure.
             */
            explicit TimeDependentOutput(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);

        private:
            double _incrementDamage;
            double _damage;
            std::unique_ptr<int> _timeOfFailure;
    };
}

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

#include "TimeDependentData.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing all location related data to perform a calculation.
     */
    class LocationDependentData
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~LocationDependentData() = default;

            /*!
             * \brief Performs a calculation.
             * \param timeDependentData
             *        The time dependent data to use in the calculation.
             * \param maximumWaveAngle
             *        The maximum wave angle.
             */
            virtual void Calculate(
                const TimeDependentData& timeDependentData,
                double maximumWaveAngle) = 0;

            /*!
             * \brief Gets the current damage.
             * \return The current damage.
             */
            double GetCurrentDamage() const;

            /*!
             * \brief Gets all the damages.
             * \return All damages.
             */
            std::vector<double> GetAllDamages() const;

        protected:
            /*!
             * \brief Creates a new instance.
             * \param initialDamage
             *        The initial damage of the location.
             */
            explicit LocationDependentData(
                double initialDamage);

        private:
            std::vector<double> allDamages;
    };
}

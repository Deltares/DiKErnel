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

#include "ITimeDependentInput.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Interface defining all location dependent input that is needed to perform a
     *        calculation.
     */
    class ILocationDependentData
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~ILocationDependentData() = default;

            /*!
             * \brief Performs a location dependent calculation.
             * \param startDamage
             *        The damage at the start of the calculation.
             * \param timeDependentData
             *        The time dependent data to use in the calculation.
             * \param maximumWaveAngle
             *        The maximum wave angle.
             * \return The calculated damage.
             */
            virtual double Calculate(
                double startDamage,
                const ITimeDependentData& timeDependentData,
                double maximumWaveAngle) = 0;

            /*!
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            virtual double GetInitialDamage() const = 0;
    };
}

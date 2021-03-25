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

#include <string>

#include "ITimeDependentInput.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Interface defining all location dependent input that is needed to perform a
     *        calculation.
     */
    class ILocationDependentInput
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~ILocationDependentInput() = default;

            /*!
             * \brief Performs a location dependent calculation.
             * \param startDamage
             *        The damage at the start of the calculation.
             * \param timeDependentInput
             *        The time dependent input to use in the calculation.
             * \return The calculated damage.
             */
            virtual double Calculate(
                double startDamage,
                const ITimeDependentInput& timeDependentInput) = 0;

            /*!
             * \brief Gets the name.
             * \return The name.
             */
            virtual std::string GetName() const = 0;

            /*!
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            virtual double GetInitialDamage() const = 0;

            /*!
             * \brief Gets the failure number.
             * \return The failure number.
             */
            virtual double GetFailureNumber() const = 0;
    };
}

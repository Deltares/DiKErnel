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

#include "ILocationDependentInput.h"
#include "IProfileData.h"
#include "ITimeDependentInput.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Interface defining all input that is needed to perform a calculation.
     */
    class ICalculationInput
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~ICalculationInput() = default;

            /*!
             * \brief Gets the profile data to use in the calculation.
             * \return The profile data to use in the calculation.
             */
            virtual const IProfileData& GetProfileData() const = 0;

            /*!
             * \brief Gets the location dependent input items to use in the calculation.
             * \return The location dependent input items to use in the calculation.
             */
            virtual const std::vector<std::reference_wrapper<ILocationDependentInput>>& GetLocationDependentInputItems() const = 0;

            /*!
             * \brief Gets the time dependent input items to use in the calculation.
             * \return The time dependent input items to use in the calculation.
             */
            virtual const std::vector<std::reference_wrapper<ITimeDependentInput>>& GetTimeDependentInputItems() const = 0;
    };
}

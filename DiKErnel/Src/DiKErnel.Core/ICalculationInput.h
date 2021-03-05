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

#include "ILocationDependentData.h"
#include "ITimeDependentData.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Interface containing all data that is needed to perform a calculation.
     */
    class ICalculationInput
    {
        public:
            virtual ~ICalculationInput() = default;

            /*!
             * \brief Gets the locations dependent data items to use in the calculation.
             * \return The locations dependent data items to use in the calculation.
             */
            virtual const std::vector<std::reference_wrapper<ILocationDependentData>>& GetLocationDependentDataItems() const = 0;

            /*!
             * \brief Gets the time dependent data items to use in the calculation.
             * \return The time dependent data items to use in the calculation.
             */
            virtual const std::vector<std::reference_wrapper<ITimeDependentData>>& GetTimeDependentDataItems() const = 0;

            /*!
             * \brief Gets the maximum wave angle.
             * \return The maximum wave angle.
             */
            virtual double GetMaximumWaveAngle() const = 0;
    };
}

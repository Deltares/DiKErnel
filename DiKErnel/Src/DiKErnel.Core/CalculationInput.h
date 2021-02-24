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
#include <vector>

#include "ILocationDependentData.h"
#include "TimeDependentData.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing all data that is needed to perform a calculation.
     */
    class CalculationInput
    {
        public:
            /*!
             * \brief Create a new instance.
             * \param locationDependentDataItems
             *        The location dependent data items to use in the calculation.
             * \param timeDependentDataItems
             *        The time dependent data items to use in the calculation.
             * \param maximumWaveAngle
             *        The maximum wave angle.
             * \exception InvalidCalculationDataException
             *            Thrown when timeDependentDataItems do not connect or are unordered.
             */
            explicit CalculationInput(
                std::vector<std::unique_ptr<ILocationDependentData>> locationDependentDataItems,
                std::vector<std::unique_ptr<TimeDependentData>> timeDependentDataItems,
                double maximumWaveAngle
            );

            /*!
             * \brief Gets the locations dependent data items to use in the calculation.
             * \return The locations dependent data items to use in the calculation.
             */
            const std::vector<std::reference_wrapper<ILocationDependentData>>& GetLocationDependentDataItems() const;

            /*!
             * \brief Gets the time dependent data items to use in the calculation.
             * \return The time dependent data items to use in the calculation.
             */
            const std::vector<std::reference_wrapper<TimeDependentData>>& GetTimeDependentDataItems() const;

            /*!
             * \brief Gets the maximum wave angle.
             * \return The maximum wave angle.
             */
            double GetMaximumWaveAngle() const;

        private:
            std::vector<std::unique_ptr<ILocationDependentData>> locationDependentDataItems;
            std::vector<std::unique_ptr<TimeDependentData>> timeDependentDataItems;

            std::vector<std::reference_wrapper<ILocationDependentData>> locationDependentDataItemReferences;
            std::vector<std::reference_wrapper<TimeDependentData>> timeDependentDataItemReferences;

            double maximumWaveAngle;
    };
}

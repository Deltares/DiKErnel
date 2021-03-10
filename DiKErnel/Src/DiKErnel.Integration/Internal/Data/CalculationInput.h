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

#include "ICalculationInput.h"
#include "LocationDependentData.h"
#include "TimeDependentData.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Class containing all input that is needed to perform a calculation.
     */
    class CalculationInput : public Core::ICalculationInput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param locationDependentInputItems
             *        The location dependent input items to use in the calculation.
             * \param timeDependentInputItems
             *        The time dependent input items to use in the calculation.
             * \param maximumWaveAngle
             *        The maximum wave angle.
             * \exception InvalidCalculationDataException
             *            Thrown when timeDependentInputItems do not connect or are unordered.
             */
            explicit CalculationInput(
                std::vector<std::unique_ptr<LocationDependentData>> locationDependentInputItems,
                std::vector<std::unique_ptr<TimeDependentData>> timeDependentInputItems,
                double maximumWaveAngle
            );

            /*!
             * \brief Gets the location dependent input items to use in the calculation.
             * \return The location dependent input items to use in the calculation.
             */
            const std::vector<std::reference_wrapper<Core::ILocationDependentInput>>& GetLocationDependentInputItems() const override;

            /*!
             * \brief Gets the time dependent input items to use in the calculation.
             * \return The time dependent input items to use in the calculation.
             */
            const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& GetTimeDependentInputItems() const override;

            /*!
             * \brief Gets the maximum wave angle.
             * \return The maximum wave angle.
             */
            double GetMaximumWaveAngle() const override;

        private:
            std::vector<std::unique_ptr<LocationDependentData>> _locationDependentInputItems;
            std::vector<std::unique_ptr<TimeDependentData>> _timeDependentInputItems;

            std::vector<std::reference_wrapper<Core::ILocationDependentInput>> _locationDependentInputItemReferences;
            std::vector<std::reference_wrapper<Core::ITimeDependentInput>> _timeDependentInputItemReferences;

            double _maximumWaveAngle;
    };
}

// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "IProfileData.h"
#include "ITimeDependentInput.h"
#include "LocationDependentOutput.h"
#include "TimeDependentOutput.h"

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
             * \brief Performs validation on the input.
             * \param profileData
             *        The profile data to use in the validation.
             * \return Whether the validation was successful.
             */
            [[nodiscard]]
            virtual bool Validate(
                const IProfileData& profileData) const = 0;

            /*!
             * \brief Performs a location dependent calculation.
             * \param initialDamage
             *        The damage at the start of the calculation.
             * \param timeDependentInput
             *        The time dependent input to use in the calculation.
             * \param profileData
             *        The profile data to use in the calculation.
             * \return The time dependent output.
             */
            virtual std::unique_ptr<TimeDependentOutput> Calculate(
                double initialDamage,
                const ITimeDependentInput& timeDependentInput,
                const IProfileData& profileData) = 0;

            /*!
             * \brief Gets location dependent output based on the derived location dependent input
             *        and the provided time dependent output items.
             * \param timeDependentOutputItems
             *        One or more time dependent output items that were calculated for the
             *        location.
             * \return The location dependent output.
             */
            virtual std::unique_ptr<LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<TimeDependentOutput>> timeDependentOutputItems) = 0;

            /*!
             * \brief Gets the x coordinate.
             * \return The x coordinate.
             */
            [[nodiscard]]
            virtual double GetX() const = 0;

            /*!
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            [[nodiscard]]
            virtual double GetInitialDamage() const = 0;

            /*!
             * \brief Gets the failure number.
             * \return The failure number.
             */
            [[nodiscard]]
            virtual double GetFailureNumber() const = 0;
    };
}

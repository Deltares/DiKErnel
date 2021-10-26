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

#include "IProfileData.h"
#include "ITimeDependentInput.h"
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
             * \brief Performs a location dependent validation.
             * \param profileData
             *        The profile data to use in the calculation.
             * \return Indicator whether the validation succeeded.
             */
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
             * \brief Gets the x coordinate.
             * \return The x coordinate.
             */
            virtual double GetX() const = 0;

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

            /*!
             * \brief Gets the z coordinate.
             * \return The z coordinate.
             */
            virtual double GetZ() const = 0;
    };
}

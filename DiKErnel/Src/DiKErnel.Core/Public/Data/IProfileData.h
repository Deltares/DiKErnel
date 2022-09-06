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

#include <memory>
#include <vector>

#include "CharacteristicPoint.h"
#include "ProfilePoint.h"
#include "ProfileSegment.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Interface defining all profile data that is needed to perform a calculation.
     */
    class IProfileData
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~IProfileData() = default;

            /*!
             * \brief Performs validation on the data.
             * \return Whether the validation was successful.
             */
            [[nodiscard]]
            virtual bool Validate() const = 0;

            /*!
             * \brief Calculates the vertical height based on linear interpolation.
             * \param horizontalPosition
             *        The horizontal position.
             * \return The vertical height or INFINITY when the horizontal position cannot be
             *         fitted with the dike profile.
             */
            [[nodiscard]]
            virtual double InterpolationVerticalHeight(
                double horizontalPosition) const = 0;

            /*!
             * \brief Calculates the horizontal position based on linear interpolation.
             * \param verticalHeight
             *        The vertical height.
             * \return The horizontal position or INFINITY when the vertical height cannot be
             *         fitted with the dike profile.
             */
            [[nodiscard]]
            virtual double InterpolationHorizontalPosition(
                double verticalHeight) const = 0;

            /*!
             * \brief Gets the profile segment where the horizontal position is located on.
             * \param horizontalPosition
             *        The horizontal position.
             * \return The profile segment or nullptr when the horizontal position cannot be fitted
             *         on a profile segment.
             */
            [[nodiscard]]
            virtual std::unique_ptr<ProfileSegment> GetProfileSegment(
                double horizontalPosition) const = 0;

            /*!
             * \brief Gets the profile points to use in the calculation.
             * \return The profile points to use in the calculation.
             */
            [[nodiscard]]
            virtual const std::vector<std::reference_wrapper<ProfilePoint>>& GetProfilePoints() const = 0;

            /*!
             * \brief Gets the profile segments to use in the calculation.
             * \return The profile segments to use in the calculation.
             */
            [[nodiscard]]
            virtual const std::vector<std::reference_wrapper<ProfileSegment>>& GetProfileSegments() const = 0;

            /*!
             * \brief Gets the characteristic points to use in the calculation.
             * \return The characteristic points to use in the calculation.
             */
            [[nodiscard]]
            virtual const std::vector<std::reference_wrapper<CharacteristicPoint>>& GetCharacteristicPoints() const = 0;
    };
}

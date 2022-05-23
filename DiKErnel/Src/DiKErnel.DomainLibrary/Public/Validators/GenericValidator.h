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

#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that holds all generic validation routines.
     */
    class GenericValidator
    {
        public:
            /*!
             * \brief Validates whether the time steps are valid.
             * \param timeSteps
             *        The time steps.
             *        Unit = [s, s]
             * \return A validation issue when the time steps are not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> TimeSteps(
                const std::vector<std::pair<int, int>>& timeSteps);

            /*!
             * \brief Validates whether the number of locations is valid.
             * \param numberOfLocations
             *        The number of locations.
             *        Unit = [-]
             * \return A validation issue when the number of locations is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> NumberOfLocations(
                int numberOfLocations);
    };
}

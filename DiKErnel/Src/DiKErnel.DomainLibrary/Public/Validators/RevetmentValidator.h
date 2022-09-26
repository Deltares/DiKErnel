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

#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that holds all generic revetment validation routines.
     */
    class RevetmentValidator
    {
        public:
            /*!
             * \brief Validates the initial damage.
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return A validation issue when the initial damage is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> InitialDamage(
                double initialDamage);

            /*!
             * \brief Validates the failure number.
             * \param failureNumber
             *        The failure number.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return A validation issue when the failure number is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> FailureNumber(
                double failureNumber,
                double initialDamage);

            /*!
             * \brief Validates the Ctm coefficient.
             * \param averageNumberOfWavesCtm
             *        The Ctm coefficient.
             *        Unit = [-]
             * \return A validation issue when the Ctm coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> AverageNumberOfWavesCtm(
                double averageNumberOfWavesCtm);
    };
}

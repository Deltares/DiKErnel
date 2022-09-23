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
     * \brief Class that holds all grass revetment specific validation routines.
     */
    class GrassRevetmentValidator
    {
        public:
            /*!
             * \brief Validates the critical cumulative overload.
             * \param criticalCumulativeOverload
             *        The critical cumulative overload.
             *        Unit = [m^2/s^2]
             * \return A validation issue when the critical cumulative overload is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> CriticalCumulativeOverload(
                double criticalCumulativeOverload);

            /*!
             * \brief Validates the critical front velocity.
             * \param criticalFrontVelocity
             *        The critical front velocity.
             *        Unit = [m/s]
             * \return A validation issue when the critical front velocity is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> CriticalFrontVelocity(
                double criticalFrontVelocity);

            /*!
             * \brief Validates the fixed number of waves.
             * \param fixedNumberOfWaves
             *        The fixed number of waves.
             *        Unit = [-]
             * \return A validation issue when the fixed number of waves is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> FixedNumberOfWaves(
                int fixedNumberOfWaves);

            /*!
             * \brief Validates the alpha M coefficient.
             * \param increasedLoadTransitionAlphaM
             *        The alpha M coefficient.
             *        Unit = [-]
             * \return A validation issue when the alpha M coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> IncreasedLoadTransitionAlphaM(
                double increasedLoadTransitionAlphaM);

            /*!
             * \brief Validates the alpha S coefficient.
             * \param reducedStrengthTransitionAlphaS
             *        The alpha S coefficient.
             *        Unit = [-]
             * \return A validation issue when the alpha S coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> ReducedStrengthTransitionAlphaS(
                double reducedStrengthTransitionAlphaS);

        private:
            static std::unique_ptr<Util::ValidationIssue> ValidateEqualToOrLargerThanZero(
                double propertyToValidate,
                const std::string& propertyName);
    };
}

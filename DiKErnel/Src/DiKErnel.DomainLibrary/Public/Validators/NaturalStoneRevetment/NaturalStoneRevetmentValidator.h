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
     * \brief Class that holds all natural stone revetment specific validation routines.
     */
    class NaturalStoneRevetmentValidator
    {
        public:
            /*!
             * \brief Validates the relative density.
             * \param relativeDensity
             *        The relative density.
             *        Unit = [-]
             * \return A validation issue when the relative density is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> RelativeDensity(
                double relativeDensity);

            /*!
             * \brief Validates the thickness of the top layer.
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             *        Unit = [m]
             * \return A validation issue when the thickness of the top layer is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> ThicknessTopLayer(
                double thicknessTopLayer);

            /*!
             * \brief Validates the Aus coefficient.
             * \param slopeUpperLevelAus
             *        The Aus coefficient.
             *        Unit = [-]
             * \return A validation issue when the Aus coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> SlopeUpperLevelAus(
                double slopeUpperLevelAus);

            /*!
             * \brief Validates the Als coefficient.
             * \param slopeLowerLevelAls
             *        The Als coefficient.
             *        Unit = [-]
             * \return A validation issue when the Als coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> SlopeLowerLevelAls(
                double slopeLowerLevelAls);
    };
}

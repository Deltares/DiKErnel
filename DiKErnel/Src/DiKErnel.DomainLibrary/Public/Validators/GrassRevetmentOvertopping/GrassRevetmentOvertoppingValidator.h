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
     * \brief Class that holds all grass revetment overtopping validation routines.
     */
    class GrassRevetmentOvertoppingValidator
    {
        public:
            /*!
             * \brief Validates the alpha A coefficient.
             * \param accelerationAlphaA
             *        The alpha A coefficient.
             *        Unit = [-]
             * \return A validation issue when the alpha A coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> AccelerationAlphaA(
                double accelerationAlphaA);

            /*!
             * \brief Validates the Cwo coefficient.
             * \param frontVelocityCwo
             *        The Cwo coefficient.
             *        Unit = [-]
             * \return A validation issue when the Cwo coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> FrontVelocityCwo(
                double frontVelocityCwo);

            /*!
             * \brief Validates the water level.
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             * \return A validation issue when the water level is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> WaterLevel(
                double waterLevel,
                double dikeHeight);
    };
}

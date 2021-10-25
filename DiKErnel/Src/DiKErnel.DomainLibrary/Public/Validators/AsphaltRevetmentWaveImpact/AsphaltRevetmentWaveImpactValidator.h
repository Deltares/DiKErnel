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
#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that holds all asphalt revetment wave impact specific validation routines.
     */
    class AsphaltRevetmentWaveImpactValidator
    {
        public:
            /*!
             * \brief Validates the fatigue alpha coefficient.
             * \param fatigueAlpha
             *        The fatigue alpha coefficient.
             * \return A validation issue when the fatigue alpha coefficient is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> FatigueAlpha(
                double fatigueAlpha);

            /*!
             * \brief Validates the fatigue beta coefficient.
             * \param fatigueBeta
             *        The fatigue beta coefficient.
             * \return A validation issue when the fatigue beta coefficient is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> FatigueBeta(
                double fatigueBeta);
    };
}

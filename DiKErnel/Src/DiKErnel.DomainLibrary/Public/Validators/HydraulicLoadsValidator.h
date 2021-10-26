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

#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that holds all hydraulic loads validation routines.
     */
    class HydraulicLoadsValidator
    {
        public:
            /*!
             * \brief Validates the wave height Hm0.
             * \param waveHeightHm0
             *        The wave height Hm0.
             * \return A validation issue when the wave height Hm0 is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> WaveHeightHm0(
                double waveHeightHm0);

            /*!
             * \brief Validates the wave period Tm10.
             * \param wavePeriodTm10
             *        The wave period Tm10.
             * \return A validation issue when the wave period Tm10 is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> WavePeriodTm10(
                double wavePeriodTm10);

            /*!
             * \brief Validates the wave angle.
             * \param waveAngle
             *        The wave angle.
             * \return A validation issue when the wave angle is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> WaveAngle(
                double waveAngle);
    };
}

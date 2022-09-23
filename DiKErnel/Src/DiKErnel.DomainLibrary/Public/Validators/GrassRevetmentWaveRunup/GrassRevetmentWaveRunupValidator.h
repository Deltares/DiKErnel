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
     * \brief Class that holds all grass revetment wave run-up specific validation routines.
     */
    class GrassRevetmentWaveRunupValidator
    {
        public:
            /*!
             * \brief Validates the 2P Gammab coefficient.
             * \param representativeWaveRunup2PGammab
             *        The 2P Gammab coefficient.
             *        Unit = [-]
             * \return A validation issue when the 2P Gammab coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> RepresentativeWaveRunup2PGammab(
                double representativeWaveRunup2PGammab);

            /*!
             * \brief Validates the 2P Gammaf coefficient.
             * \param representativeWaveRunup2PGammaf
             *        The 2P Gammaf coefficient.
             *        Unit = [-]
             * \return A validation issue when the 2P Gammaf coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> RepresentativeWaveRunup2PGammaf(
                double representativeWaveRunup2PGammaf);

            /*!
             * \brief Validates the outer slope.
             * \param outerSlope
             *        The outer slope.
             *        Unit = [-]
             * \return A validation issue when the outer slope is not valid; nullptr otherwise.
             */
            static std::unique_ptr<Util::ValidationIssue> OuterSlope(
                double outerSlope);
    };
}

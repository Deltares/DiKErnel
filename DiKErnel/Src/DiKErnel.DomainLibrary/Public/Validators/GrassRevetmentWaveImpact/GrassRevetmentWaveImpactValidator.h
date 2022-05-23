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
     * \brief Class that holds all grass revetment wave impact specific validation routines.
     */
    class GrassRevetmentWaveImpactValidator
    {
        public:
            /*!
             * \brief Validates the Agwi coefficient.
             * \param timeLineAgwi
             *        The Agwi coefficient.
             *        Unit = [m]
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             *        Unit = [m]
             * \return A validation issue when the Agwi coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> TimeLineAgwi(
                double timeLineAgwi,
                double timeLineCgwi);

            /*!
             * \brief Validates the Bgwi coefficient.
             * \param timeLineBgwi
             *        The Bgwi coefficient.
             *        Unit = [s^-1]
             * \return A validation issue when the Bgwi coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> TimeLineBgwi(
                double timeLineBgwi);

            /*!
             * \brief Validates the Cgwi coefficient.
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             *        Unit = [m]
             * \return A validation issue when the Cgwi coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> TimeLineCgwi(
                double timeLineCgwi);

            /*!
             * \brief Validates the Temax coefficient.
             * \param minimumWaveHeightTemax
             *        The Temax coefficient.
             *        Unit = [s]
             * \return A validation issue when the Temax coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> MinimumWaveHeightTemax(
                double minimumWaveHeightTemax);

            /*!
             * \brief Validates the Temin coefficient.
             * \param maximumWaveHeightTemin
             *        The Temin coefficient.
             *        Unit = [s]
             * \return A validation issue when the Temin coefficient is not valid; nullptr
             *         otherwise.
             */
            static std::unique_ptr<ValidationIssue> MaximumWaveHeightTemin(
                double maximumWaveHeightTemin);

            /*!
             * \brief Validates the Nwa coefficient.
             * \param waveAngleImpactNwa
             *        The Nwa coefficient.
             *        Unit = [-]
             * \return A validation issue when the Nwa coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> WaveAngleImpactNwa(
                double waveAngleImpactNwa);

            /*!
             * \brief Validates the Qwa coefficient.
             * \param waveAngleImpactQwa
             *        The Qwa coefficient.
             *        Unit = [-]
             * \return A validation issue when the Qwa coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> WaveAngleImpactQwa(
                double waveAngleImpactQwa);

            /*!
             * \brief Validates the Rwa coefficient.
             * \param waveAngleImpactRwa
             *        The Rwa coefficient.
             *        Unit = [-]
             * \return A validation issue when the Rwa coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> WaveAngleImpactRwa(
                double waveAngleImpactRwa);

            /*!
             * \brief Validates the Aul coefficient.
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             *        Unit = [-]
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             *        Unit = [-]
             * \return A validation issue when the Aul coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> UpperLimitLoadingAul(
                double upperLimitLoadingAul,
                double lowerLimitLoadingAll);
    };
}

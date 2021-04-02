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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for grass revetment wave impact with open sod.
     */
    class GrassRevetmentWaveImpactOpenSodDefaults
    {
        public:
            /*!
             * \brief The default value of the Agwi coefficient.
             *        Unit = [m]
             */
            inline static const double TIME_LINE_AGWI = 0.8;

            /*!
             * \brief The default value of the Bgwi coefficient.
             *        Unit = [s^-1]
             */
            inline static const double TIME_LINE_BGWI = -0.00001944;

            /*!
             * \brief The default value of the Cgwi coefficient.
             *        Unit = [m]
             */
            inline static const double TIME_LINE_CGWI = 0.25;

            /*!
             * \brief The default value of the Temax coefficient.
             *        Unit = [s]
             */
            inline static const double MINIMUM_WAVE_HEIGHT_TEMAX = 3600000;

            /*!
             * \brief The default value of the Temin coefficient.
             *        Unit = [s]
             */
            inline static const double MAXIMUM_WAVE_HEIGHT_TEMIN = 3.6;

            /*!
             * \brief The default value of the Nwa coefficient.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_NWA = 2.0 / 3.0;

            /*!
             * \brief The default value of the Qwa coefficient.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_QWA = 0.35;

            /*!
             * \brief The default value of the Rwa coefficient.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_RWA = 10;

            /*!
             * \brief The default value of the Aul coefficient.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_AUL = 0;

            /*!
             * \brief The default value of the All coefficient.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_ALL = 0.5;
    };
}

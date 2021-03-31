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
             * \brief The default value of the time line Agwi.
             *        Unit = [-]
             */
            inline static const double TIME_LINE_AGWI = 0.8;

            /*!
             * \brief The default value of the time line Bgwi
             *        Unit = [-]
             */
            inline static const double TIME_LINE_BGWI = -0.00001944;

            /*!
             * \brief The default value of the time line Cgwi
             *        Unit = [-]
             */
            inline static const double TIME_LINE_CGWI = 0.25;

            /*!
             * \brief The default value of the minimum wave height Temax.
             *        Unit = [-]
             */
            inline static const double MINIMUM_WAVE_HEIGHT_TEMAX = 3600000;

            /*!
             * \brief The default value of the maximum wave height Temin.
             *        Unit = [-]
             */
            inline static const double MAXIMUM_WAVE_HEIGHT_TEMIN = 3.6;

            /*!
             * \brief The default value of the wave angle impact Nwa.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_NWA = 2.0/3.0;

            /*!
             * \brief The default value of the wave angle impact Qwa.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_QWA = 0.35;

            /*!
             * \brief The default value of the wave angle impact Rwa.
             *        Unit = [-]
             */
            inline static const double WAVE_ANGLE_IMPACT_RWA = 10.0;

            /*!
             * \brief The default value of the upper limit loading Aul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_AUL = 0.0;

            /*!
             * \brief The default value of the lower limit loading All.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_ALL = 0.5;
    };
}

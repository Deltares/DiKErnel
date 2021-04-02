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
     * \brief Class that contains default values for nordic stone revetments.
     */
    class NordicStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief The default value of the XIb coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_XIB = 2.9;

            /*!
             * \brief The default value of the Ap coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_AP = 4;

            /*!
             * \brief The default value of the Bp coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_BP = 0;

            /*!
             * \brief The default value of the Cp coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_CP = 0;

            /*!
             * \brief The default value of the Np coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_NP = -0.9;

            /*!
             * \brief The default value of the As coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_AS = 0.8;

            /*!
             * \brief The default value of the Bs coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_BS = 0;

            /*!
             * \brief The default value of the Cs coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_CS = 0;

            /*!
             * \brief The default value of the Ns coefficient.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_NS = 0.6;

            /*!
             * \brief The default value of the Aul coefficient.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_AUL = 0.1;

            /*!
             * \brief The default value of the Bul coefficient.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_BUL = 0.6;

            /*!
             * \brief The default value of the Cul coefficient.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_CUL = 4;

            /*!
             * \brief The default value of the All coefficient.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_ALL = 0.1;

            /*!
             * \brief The default value of the Bll coefficient.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_BLL = 0.2;

            /*!
             * \brief The default value of the Cll coefficient.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_CLL = 4;

            /*!
             * \brief The default value of the Asmax coefficient.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX = 0.42;

            /*!
             * \brief The default value of the Bsmax coefficient.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX = 0.9;

            /*!
             * \brief The default value of the Awi coefficient.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI = 0.96;

            /*!
             * \brief The default value of the Bwi coefficient.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI = 0.11;

            /*!
             * \brief The default value of the Betamax coefficient.
             *        Unit = [deg]
             */
            inline static const double WAVE_ANGLE_IMPACT_BETAMAX = 78;
    };
}

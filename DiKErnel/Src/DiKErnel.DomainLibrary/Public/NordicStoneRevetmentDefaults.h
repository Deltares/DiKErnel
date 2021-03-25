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
     * \brief Class that contains default values for natural stone revetment.
     */
    class NordicStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief The default value of the hydraulic load on nordic stone XIb.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB = 2.9;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Ap.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_AP = 4;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Bp.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_BP = 0;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Cp.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_CP = 0;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Np.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_NP = -0.9;

            /*!
             * \brief The default value of the hydraulic load on nordic stone As.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_AS = 0.8;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Bs.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_BS = 0;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Cs.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_CS = 0;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Ns.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_NS = 0.6;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Aul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL = 0.1;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Bul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL = 0.6;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Cul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL = 4;

            /*!
             * \brief The default value of the lower loading limit on nordic stone All.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL = 0.1;

            /*!
             * \brief The default value of the lower loading limit on nordic stone Bll.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL = 0.2;

            /*!
             * \brief The default value of the lower loading limit on nordic stone Cll.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL = 4;

            /*!
             * \brief The default value of the distance maximum wave elevation
             *        on nordic stone Asmax.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX = 0.42;

            /*!
             * \brief The default value of the distance maximum wave elevation
             *        on nordic stone Bsmax.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX = 0.9;

            /*!
             * \brief The default value of the normative width of wave impact
             *        on nordic stone Awi.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI = 0.96;

            /*!
             * \brief The default value of the normative width of wave impact
             *        on nordic stone Bwi.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI = 0.11;

            /*!
             * \brief The default value of the wave angle impact
             *        on nordic stone betamax.
             *        Unit = [°]
             */
            inline static const double WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETAMAX = 78;
    };
}

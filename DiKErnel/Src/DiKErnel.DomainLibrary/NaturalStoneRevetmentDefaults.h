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
    class NaturalStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief The default value of the similarity parameter threshold.
             *        Unit = [-]
             */
            static const double SIMILARITY_PARAMETER_THRESHOLD;

            /*!
             * \brief The default value of the A coefficient for plunging.
             *        Unit = [-]
             */
            static const double PLUNGING_COEFFICIENT_A;

            /*!
             * \brief The default value of the B coefficient for plunging.
             *        Unit = [-]
             */
            static const double PLUNGING_COEFFICIENT_B;

            /*!
             * \brief The default value of the C coefficient for plunging.
             *        Unit = [-]
             */
            static const double PLUNGING_COEFFICIENT_C;

            /*!
             * \brief The default value of the N coefficient for plunging.
             *        Unit = [-]
             */
            static const double PLUNGING_COEFFICIENT_N;

            /*!
             * \brief The default value of the A coefficient for surging.
             *        Unit = [-]
             */
            static const double SURGING_COEFFICIENT_A;

            /*!
             * \brief The default value of the B coefficient for surging.
             *        Unit = [-]
             */
            static const double SURGING_COEFFICIENT_B;

            /*!
             * \brief The default value of the C coefficient for surging.
             *        Unit = [-]
             */
            static const double SURGING_COEFFICIENT_C;

            /*!
             * \brief The default value of the N coefficient for surging.
             *        Unit = [-]
             */
            static const double SURGING_COEFFICIENT_N;

            /*!
             * \brief The default value of the hydraulic load on nordic stone XIb.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Ap.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_AP;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Bp.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_BP;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Cp.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_CP;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Np.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_NP;

            /*!
             * \brief The default value of the hydraulic load on nordic stone As.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_AS;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Bs.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_BS;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Cs.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_CS;

            /*!
             * \brief The default value of the hydraulic load on nordic stone Ns.
             *        Unit = [-]
             */
            static const double HYDRAULIC_LOAD_ON_NORDIC_STONE_NS;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Aul.
             *        Unit = [-]
             */
            static const double UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Bul.
             *        Unit = [-]
             */
            static const double UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL;

            /*!
             * \brief The default value of the upper loading limit on nordic stone Cul.
             *        Unit = [-]
             */
            static const double UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL;

            /*!
             * \brief The default value of the lower loading limit on nordic stone All.
             *        Unit = [-]
             */
            static const double LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL;

            /*!
             * \brief The default value of the lower loading limit on nordic stone Bll.
             *        Unit = [-]
             */
            static const double LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL;

            /*!
             * \brief The default value of the lower loading limit on nordic stone Cll.
             *        Unit = [-]
             */
            static const double LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL;

            /*!
             * \brief The default value of the distance maximum wave elevation
             * on nordic stone Asmax.
             *        Unit = [-]
             */
            static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX;

            /*!
             * \brief The default value of the distance maximum wave elevation
             * on nordic stone Bsmax.
             *        Unit = [-]
             */
            static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX;

            /*!
             * \brief The default value of the normative width of wave impact Awi.
             *        Unit = [-]
             */
            static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI;

            /*!
             * \brief The default value of the normative width of wave impact Bwi.
             *        Unit = [-]
             */
            static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI;
    };
}

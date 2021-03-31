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
     * \brief Class that contains default values for nordic stone revetment.
     */
    class NordicStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief The default value of the hydraulic load XIb.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_XIB = 2.9;

            /*!
             * \brief The default value of the hydraulic load Ap.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_AP = 4;

            /*!
             * \brief The default value of the hydraulic load Bp.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_BP = 0;

            /*!
             * \brief The default value of the hydraulic load Cp.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_CP = 0;

            /*!
             * \brief The default value of the hydraulic load Np.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_NP = -0.9;

            /*!
             * \brief The default value of the hydraulic load As.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_AS = 0.8;

            /*!
             * \brief The default value of the hydraulic load Bs.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_BS = 0;

            /*!
             * \brief The default value of the hydraulic load Cs.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_CS = 0;

            /*!
             * \brief The default value of the hydraulic load Ns.
             *        Unit = [-]
             */
            inline static const double HYDRAULIC_LOAD_NS = 0.6;

            /*!
             * \brief The default value of the upper limit loading Aul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_AUL = 0.1;

            /*!
             * \brief The default value of the upper limit loading Bul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_BUL = 0.6;

            /*!
             * \brief The default value of the upper limit loading Cul.
             *        Unit = [-]
             */
            inline static const double UPPER_LIMIT_LOADING_CUL = 4;

            /*!
             * \brief The default value of the lower limit loading All.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_ALL = 0.1;

            /*!
             * \brief The default value of the lower limit loading Bll.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_BLL = 0.2;

            /*!
             * \brief The default value of the lower limit loading Cll.
             *        Unit = [-]
             */
            inline static const double LOWER_LIMIT_LOADING_CLL = 4;

            /*!
             * \brief The default value of the distance maximum wave elevation Asmax.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX = 0.42;

            /*!
             * \brief The default value of the distance maximum wave elevation Bsmax.
             *        Unit = [-]
             */
            inline static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX = 0.9;

            /*!
             * \brief The default value of the normative width of wave impact Awi.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI = 0.96;

            /*!
             * \brief The default value of the normative width of wave impact Bwi.
             *        Unit = [-]
             */
            inline static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI = 0.11;

            /*!
             * \brief The default value of the wave angle impact betamax.
             *        Unit = [deg]
             */
            inline static const double WAVE_ANGLE_IMPACT_BETAMAX = 78;
    };
}

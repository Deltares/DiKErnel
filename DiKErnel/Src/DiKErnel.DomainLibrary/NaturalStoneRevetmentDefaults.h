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
     * \brief Class that contains all default values for natural stone revetment.
     */
    class NaturalStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief The relative density.
             */
            static const double RELATIVE_DENSITY;

            /*!
             * \brief The similarity parameter threshold.
             */
            static const double SIMILARITY_PARAMETER_THRESHOLD;

            /*!
             * \brief The coefficient plunging Ap.
             */
            static const double COEFFICIENT_PLUNGING_AP;

            /*!
             * \brief The coefficient plunging Bp.
             */
            static const double COEFFICIENT_PLUNGING_BP;

            /*!
             * \brief The coefficient plunging Cp.
             */
            static const double COEFFICIENT_PLUNGING_CP;

            /*!
             * \brief The coefficient plunging Np.
             */
            static const double COEFFICIENT_PLUNGING_NP;

            /*!
             * \brief The coefficient surging As.
             */
            static const double COEFFICIENT_SURGING_AS;

            /*!
             * \brief The coefficient surging Bs.
             */
            static const double COEFFICIENT_SURGING_BS;

            /*!
             * \brief The coefficient surging Cs.
             */
            static const double COEFFICIENT_SURGING_CS;

            /*!
             * \brief The coefficient surging Ns.
             */
            static const double COEFFICIENT_SURGING_NS;
    };
}

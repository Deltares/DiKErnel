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
             * \brief The default value of the relative density.
             *        Unit = [-]
             */
            static const double RELATIVE_DENSITY;

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
    };
}

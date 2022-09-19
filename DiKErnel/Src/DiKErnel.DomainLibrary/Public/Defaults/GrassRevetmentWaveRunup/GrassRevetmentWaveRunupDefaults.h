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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for grass revetment wave run-up.
     */
    class GrassRevetmentWaveRunupDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the representative 2P Aru coefficient.
             * \return The default value of the representative 2P Aru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetRepresentativeWaveRunup2PAru();

            /*!
             * \brief Gets the default value of the representative 2P Bru coefficient.
             * \return The default value of the representative 2P Bru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetRepresentativeWaveRunup2PBru();

            /*!
             * \brief Gets the default value of the representative 2P Cru coefficient.
             * \return The default value of the representative 2P Cru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetRepresentativeWaveRunup2PCru();

            /*!
             * \brief Gets the default value of the representative 2P Gammab coefficient.
             * \return The default value of the representative 2P Gammab coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetRepresentativeWaveRunup2PGammab();

            /*!
             * \brief Gets the default value of the representative 2P Gammaf coefficient.
             * \return The default value of the representative 2P Gammaf coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetRepresentativeWaveRunup2PGammaf();

            /*!
             * \brief Gets the default value of the Abeta coefficient.
             * \return The default value of the Abeta coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetWaveAngleImpactAbeta();

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetWaveAngleImpactBetamax();
    };
}

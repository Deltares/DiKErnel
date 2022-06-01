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
     * \brief Interface that contains default value definitions for grass revetment wave run-up.
     */
    class IGrassRevetmentWaveRunupDefaults
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~IGrassRevetmentWaveRunupDefaults() = default;

            /*!
             * \brief Gets the default value of the critical cumulative overload.
             * \return The default value of the critical cumulative overload.
             *         Unit = [m^2/s^2]
             */
            [[nodiscard]]
            virtual double GetCriticalCumulativeOverload() const = 0;

            /*!
             * \brief Gets the default value of the critical front velocity.
             * \return The default value of the critical front velocity.
             *         Unit = [m/s]
             */
            [[nodiscard]]
            virtual double GetCriticalFrontVelocity() const = 0;

            /*!
             * \brief Gets the default value of the increased load transition alpha M.
             * \return The default value of the increased load transition alpha M.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetIncreasedLoadTransitionAlphaM() const = 0;

            /*!
             * \brief Gets the default value of the reduced strength transition alpha S.
             * \return The default value of the reduced strength transition alpha S.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetReducedStrengthTransitionAlphaS() const = 0;

            /*!
             * \brief Gets the default value of the Ctm coefficient.
             * \return The default value of the Ctm coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetAverageNumberOfWavesCtm() const = 0;

            /*!
             * \brief Gets the default value of the representative 2P Aru coefficient.
             * \return The default value of the representative 2P Aru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetRepresentativeWaveRunup2PAru() const = 0;

            /*!
             * \brief Gets the default value of the representative 2P Bru coefficient.
             * \return The default value of the representative 2P Bru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetRepresentativeWaveRunup2PBru() const = 0;

            /*!
             * \brief Gets the default value of the representative 2P Cru coefficient.
             * \return The default value of the representative 2P Cru coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetRepresentativeWaveRunup2PCru() const = 0;

            /*!
             * \brief Gets the default value of the representative 2P Gammab coefficient.
             * \return The default value of the representative 2P Gammab coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetRepresentativeWaveRunup2PGammab() const = 0;

            /*!
             * \brief Gets the default value of the representative 2P Gammaf coefficient.
             * \return The default value of the representative 2P Gammaf coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetRepresentativeWaveRunup2PGammaf() const = 0;

            /*!
             * \brief Gets the default value of the Abeta coefficient.
             * \return The default value of the Abeta coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetWaveAngleImpactAbeta() const = 0;

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetWaveAngleImpactBetamax() const = 0;
    };
}

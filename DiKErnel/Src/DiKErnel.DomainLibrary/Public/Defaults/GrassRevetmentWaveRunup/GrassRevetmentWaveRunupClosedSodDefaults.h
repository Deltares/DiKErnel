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

#include "IGrassRevetmentWaveRunupDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for grass revetment wave run-up with closed sod.
     */
    class GrassRevetmentWaveRunupClosedSodDefaults : public virtual IGrassRevetmentWaveRunupDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the critical cumulative overload.
             * \return The default value of the critical cumulative overload.
             *         Unit = [m^2/s^2]
             */
            double GetCriticalCumulativeOverload() const override;

            /*!
             * \brief Gets the default value of the critical front velocity.
             * \return The default value of the critical front velocity.
             *         Unit = [m/s]
             */
            double GetCriticalFrontVelocity() const override;

            /*!
             * \brief Gets the default value of the increased load transition alpha M.
             * \return The default value of the increased load transition alpha M.
             *         Unit = [-]
             */
            double GetIncreasedLoadTransitionAlphaM() const override;

            /*!
             * \brief Gets the default value of the reduced strength transition alpha S.
             * \return The default value of the reduced strength transition alpha S.
             *         Unit = [-]
             */
            double GetReducedStrengthTransitionAlphaS() const override;

            /*!
             * \brief Gets the default value of the Ctm coefficient.
             * \return The default value of the Ctm coefficient.
             *         Unit = [-]
             */
            double GetAverageNumberOfWavesCtm() const override;

            /*!
             * \brief Gets the default value of the representative 2P Aru coefficient.
             * \return The default value of the representative 2P Aru coefficient.
             *         Unit = [-]
             */
            double GetRepresentativeWaveRunup2PAru() const override;

            /*!
             * \brief Gets the default value of the representative 2P Bru coefficient.
             * \return The default value of the representative 2P Bru coefficient.
             *         Unit = [-]
             */
            double GetRepresentativeWaveRunup2PBru() const override;

            /*!
             * \brief Gets the default value of the representative 2P Cru coefficient.
             * \return The default value of the representative 2P Cru coefficient.
             *         Unit = [-]
             */
            double GetRepresentativeWaveRunup2PCru() const override;

            /*!
             * \brief Gets the default value of the representative 2P Gammab coefficient.
             * \return The default value of the representative 2P Gammab coefficient.
             *         Unit = [-]
             */
            double GetRepresentativeWaveRunup2PGammab() const override;

            /*!
             * \brief Gets the default value of the representative 2P Gammaf coefficient.
             * \return The default value of the representative 2P Gammaf coefficient.
             *         Unit = [-]
             */
            double GetRepresentativeWaveRunup2PGammaf() const override;

            /*!
             * \brief Gets the default value of the Abeta coefficient.
             * \return The default value of the Abeta coefficient.
             *         Unit = [-]
             */
            double GetWaveAngleImpactAbeta() const override;

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [-]
             */
            double GetWaveAngleImpactBetamax() const override;
    };
}

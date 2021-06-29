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

#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a grass revetment wave impact location.
     */
    class GrassRevetmentWaveRunupRayleighTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param incrementDamage
             *        The increment damage.
             * \param damage
             *        The damage.
             * \param timeOfFailure
             *        The time of failure.
             * \param waveAngleImpact
             *        The wave angle impact.
             * \param representativeWaveRunup2P
             *        The representative wave run-up 2P.
             * \param cumulativeOverload
             *        The cumulative overload.
             */
            explicit GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure,
                double waveAngleImpact,
                double representativeWaveRunup2P,
                double cumulativeOverload);

            /*!
             * \brief Gets the wave angle impact.
             * \return The wave angle impact.
             */
            double GetWaveAngleImpact() const;

            /*!
             * \brief Gets the representative wave run-up 2P.
             * \return The representative wave run-up 2P.
             */
            double GetRepresentativeWaveRunup2P() const;

            /*!
             * \brief Gets the cumulative overload.
             * \return The cumulative overload.
             */
            double GetCumulativeOverload() const;

        private:
            const double _waveAngleImpact;
            const double _representativeWaveRunup2P;
            const double _cumulativeOverload;
    };
}

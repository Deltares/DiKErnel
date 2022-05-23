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

#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a grass revetment wave run-up location for the Rayleigh
     *        protocol.
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
             * \param verticalDistanceWaterLevelElevation
             *        The vertical distance water level elevation.
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
                double verticalDistanceWaterLevelElevation,
                std::unique_ptr<double> waveAngleImpact,
                std::unique_ptr<double> representativeWaveRunup2P,
                std::unique_ptr<double> cumulativeOverload);

            /*!
             * \brief Gets the vertical distance water level elevation.
             * \return The vertical distance water level elevation.
             */
            double GetVerticalDistanceWaterLevelElevation() const;

            /*!
             * \brief Gets the wave angle impact.
             * \return The wave angle impact.
             */
            const double* GetWaveAngleImpact() const;

            /*!
             * \brief Gets the representative wave run-up 2P.
             * \return The representative wave run-up 2P.
             */
            const double* GetRepresentativeWaveRunup2P() const;

            /*!
             * \brief Gets the cumulative overload.
             * \return The cumulative overload.
             */
            const double* GetCumulativeOverload() const;

        private:
            const double _verticalDistanceWaterLevelElevation;
            std::unique_ptr<double> _waveAngleImpact;
            std::unique_ptr<double> _representativeWaveRunup2P;
            std::unique_ptr<double> _cumulativeOverload;
    };
}

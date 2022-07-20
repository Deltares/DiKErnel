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

#include "GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties.h"
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
             * \param constructionProperties
             *        The construction properties.
             */
            explicit GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties& constructionProperties);

            /*!
             * \brief Gets the vertical distance water level elevation.
             * \return The vertical distance water level elevation.
             */
            [[nodiscard]]
            double GetVerticalDistanceWaterLevelElevation() const;

            /*!
             * \brief Gets the wave angle impact.
             * \return The wave angle impact.
             */
            [[nodiscard]]
            const double* GetWaveAngleImpact() const;

            /*!
             * \brief Gets the representative wave run-up 2P.
             * \return The representative wave run-up 2P.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2P() const;

            /*!
             * \brief Gets the cumulative overload.
             * \return The cumulative overload.
             */
            [[nodiscard]]
            const double* GetCumulativeOverload() const;

        private:
            std::unique_ptr<double> _verticalDistanceWaterLevelElevation;
            std::unique_ptr<double> _waveAngleImpact;
            std::unique_ptr<double> _representativeWaveRunup2P;
            std::unique_ptr<double> _cumulativeOverload;
    };
}

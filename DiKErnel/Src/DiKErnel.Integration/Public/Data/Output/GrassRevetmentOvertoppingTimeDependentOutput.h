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

#include "GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a grass revetment overtopping location.
     */
    class GrassRevetmentOvertoppingTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param constructionProperties
             *        The construction properties.
             * \exception InvalidTimeDependentOutputException
             *            Thrown when mandatory properties are nullptr.
             */
            explicit GrassRevetmentOvertoppingTimeDependentOutput(
                GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties& constructionProperties);

            /*!
             * \brief Gets the vertical distance water level elevation.
             * \return The vertical distance water level elevation.
             */
            [[nodiscard]]
            double GetVerticalDistanceWaterLevelElevation() const;

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
            std::unique_ptr<double> _verticalDistanceWaterLevelElevation = nullptr;
            std::unique_ptr<double> _waveAngleImpact = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2P = nullptr;
            std::unique_ptr<double> _cumulativeOverload = nullptr;
    };
}

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

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Input for a grass revetment overtopping cumulative overload calculation.
     */
    struct GrassRevetmentOvertoppingCumulativeOverloadInput
    {
        /*!
         * \brief The average number of waves.
         *        Unit = [-]
         */
        double _averageNumberOfWaves{};

        /*!
         * \brief The representative wave run-up (2 percent).
         *        Unit = [m]
         */
        double _representativeWaveRunup2P{};

        /*!
         * \brief The fixed number of waves.
         *        Unit = [-]
         */
        int _fixedNumberOfWaves{};

        /*!
         * \brief The vertical distance of the water elevation.
         *        Unit = [m]
         */
        double _verticalDistanceWaterLevelElevation{};

        /*!
         * \brief The critical front velocity.
         *        Unit = [m/s]
         */
        double _criticalFrontVelocity{};

        /*!
         * \brief The AlphaM value.
         *        Unit = [-]
         */
        double _increasedLoadTransitionAlphaM{};

        /*!
         * \brief The AlphaS value.
         *        Unit = [-]
         */
        double _reducedStrengthTransitionAlphaS{};

        /*!
         * \brief The Cu coefficient.
         *        Unit = [-]
         */
        double _frontVelocityCu{};

        /*!
         * \brief The gravitational acceleration.
         *        Unit = [m/s^2]
         */
        double _gravitationalAcceleration{};
    };
}

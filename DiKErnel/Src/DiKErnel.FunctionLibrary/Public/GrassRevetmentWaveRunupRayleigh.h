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

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all grass revetment wave run-up specific calculation routines for
     *        the Rayleigh protocol.
     */
    class GrassRevetmentWaveRunupRayleigh
    {
        public:
            /*!
             * \brief Calculates the cumulative overload.
             * \param averageNumberOfWaves
             *        The average number of waves.
             *        Unit = [-]
             * \param frontVelocity
             *        The front velocity.
             *        Unit = [m/s]
             * \param criticalFrontVelocity
             *        The critical front velocity.
             *        Unit = [m/s]
             * \param increasedLoadTransitionAlphaM
             *        The AlphaM value.
             *        Unit = [-]
             * \param reducedStrengthTransitionAlphaS
             *        The AlphaS value.
             *        Unit = [-]
             * \param cumulativeOverloadNf
             *        The Nf value.
             *        Unit = [-]
             * \return The cumulative overload.
             *         Unit = [m^2/s^2]
             */
            static double CumulativeOverload(
                double averageNumberOfWaves,
                double frontVelocity,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                int cumulativeOverloadNf
            );
    };
}

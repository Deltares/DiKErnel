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
             * \param representativeWaveRunup2P
             *        The representative wave run-up (2 percent).
             *        Unit = [m]
             * \param fixedNumberOfWaves
             *        The fixed number of waves.
             *        Unit = [-]
             * \param positionZ
             *        The vertical position.
             *        Unit = [m]
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param criticalFrontVelocity
             *        The critical front velocity.
             *        Unit = [m/s]
             * \param increasedLoadTransitionAlphaM
             *        The AlphaM value.
             *        Unit = [-]
             * \param reducedStrengthTransitionAlphaS
             *        The AlphaS value.
             *        Unit = [-]
             * \param frontVelocityCu
             *        The Cu coefficient.
             *        Unit = [-]
             * \param gravitationalAcceleration
             *        The gravitational acceleration.
             *        Unit = [m/s^2]
             * \return The cumulative overload.
             *         Unit = [m^2/s^2]
             */
            static double CumulativeOverload(
                double averageNumberOfWaves,
                double representativeWaveRunup2P,
                int fixedNumberOfWaves,
                double positionZ,
                double waterLevel,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                double frontVelocityCu,
                double gravitationalAcceleration);

        private:
            static double FrontVelocity(
                double waveRunup,
                double positionZ,
                double waterLevel,
                double frontVelocityCu,
                double gravitationalAcceleration);

            static double WaveRunup(
                double representativeWaveRunup2P,
                int fixedNumberOfWaves,
                int waveNumber);
    };
}

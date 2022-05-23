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
     * \brief Class that holds all grass revetment wave run-up specific calculation routines.
     */
    class GrassRevetmentWaveRunupFunctions
    {
        public:
            /*!
             * \brief Calculates the increment of damage.
             * \param cumulativeOverload
             *        The cumulative overload.
             *        Unit = [m^2/s^2]
             * \param criticalCumulativeOverload
             *        The critical cumulative overload.
             *        Unit = [m^2/s^2]
             * \return The increment of damage.
             *         Unit = [-]
             */
            static double IncrementDamage(
                double cumulativeOverload,
                double criticalCumulativeOverload);

            /*!
             * \brief Calculates the representative wave run-up (2 percent).
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waveAngleImpact
             *        The wave impact with respect to the wave angle.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param representativeWaveRunup2PGammab
             *        The Gammab value.
             *        Unit = [-]
             * \param representativeWaveRunup2PGammaf
             *        The Gammaf value.
             *        Unit = [-]
             * \param representativeWaveRunup2PAru
             *        The Aru coefficient.
             *        Unit = [-]
             * \param representativeWaveRunup2PBru
             *        The Bru coefficient.
             *        Unit = [-]
             * \param representativeWaveRunup2PCru
             *        The Cru coefficient.
             *        Unit = [-]
             * \return The representative wave run-up (2 percent).
             *         Unit = [m]
             */
            static double RepresentativeWaveRunup2P(
                double surfSimilarityParameter,
                double waveAngleImpact,
                double waveHeightHm0,
                double representativeWaveRunup2PGammab,
                double representativeWaveRunup2PGammaf,
                double representativeWaveRunup2PAru,
                double representativeWaveRunup2PBru,
                double representativeWaveRunup2PCru);

            /*!
             * \brief Calculates the wave impact with respect to the wave angle.
             * \param waveAngle
             *        The wave angle.
             *        Unit = [deg]
             * \param waveAngleImpactAbeta
             *        The Abeta coefficient.
             *        Unit = [-]
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             *        Unit = [-]
             * \return The wave impact with respect to the wave angle.
             *         Unit = [-]
             */
            static double WaveAngleImpact(
                double waveAngle,
                double waveAngleImpactAbeta,
                double waveAngleImpactBetamax);
    };
}

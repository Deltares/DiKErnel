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

#include <cmath>
#include <algorithm>

#include "GrassRevetmentCumulativeOverloadInput.h"

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all generic grass revetment calculation routines.
     */
    class GrassRevetmentFunctions
    {
        friend class GrassRevetmentOvertoppingFunctions;
        friend class GrassRevetmentWaveRunupRayleighFunctions;

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
            [[nodiscard]]
            static double IncrementDamage(
                double cumulativeOverload,
                double criticalCumulativeOverload);

        private:
            template <typename T>
            [[nodiscard]]
            static double CumulativeOverload(
                const GrassRevetmentCumulativeOverloadInput& input,
                const T& getFrontVelocity)
            {
                auto cumulativeFrontVelocity = 0.0;

                const double cumulativeFrontVelocityPartial = input._criticalFrontVelocity * input._criticalFrontVelocity;

                for (auto k = 1; k <= input._fixedNumberOfWaves; ++k)
                {
                    const auto waveRunup = WaveRunup(input._representativeWaveRunup2P, input._fixedNumberOfWaves, k);
                    const auto frontVelocity = getFrontVelocity(waveRunup);

                    cumulativeFrontVelocity += std::max(0.0, input._increasedLoadTransitionAlphaM * frontVelocity * frontVelocity
                                                        - input._reducedStrengthTransitionAlphaS * cumulativeFrontVelocityPartial);
                }

                return input._averageNumberOfWaves / input._fixedNumberOfWaves * cumulativeFrontVelocity;
            }

            [[nodiscard]]
            static double WaveRunup(
                double representativeWaveRunup2P,
                int fixedNumberOfWaves,
                int waveNumber);

            static double _waveRunupPartial;
    };
}

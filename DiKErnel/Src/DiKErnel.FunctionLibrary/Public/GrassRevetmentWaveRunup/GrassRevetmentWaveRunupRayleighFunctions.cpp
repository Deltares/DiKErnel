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

#include "GrassRevetmentWaveRunupRayleighFunctions.h"

#include <algorithm>
#include <cmath>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(
        const double averageNumberOfWaves,
        const double representativeWaveRunup2P,
        const int fixedNumberOfWaves,
        const double verticalDistanceWaterLevelElevation,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double frontVelocityCu,
        const double gravitationalAcceleration)
    {
        auto cumulativeFrontVelocity = 0.0;

        for (auto k = 1; k <= fixedNumberOfWaves; ++k)
        {
            const auto waveRunup = WaveRunup(representativeWaveRunup2P, fixedNumberOfWaves, k);
            const auto frontVelocity = FrontVelocity(waveRunup, verticalDistanceWaterLevelElevation, frontVelocityCu, gravitationalAcceleration);

            cumulativeFrontVelocity += max(0.0, increasedLoadTransitionAlphaM * pow(frontVelocity, 2.0)
                                           - reducedStrengthTransitionAlphaS * pow(criticalFrontVelocity, 2.0));
        }

        return averageNumberOfWaves / fixedNumberOfWaves * cumulativeFrontVelocity;
    }

    double GrassRevetmentWaveRunupRayleighFunctions::FrontVelocity(
        const double waveRunup,
        const double verticalDistanceWaterLevelElevation,
        const double frontVelocityCu,
        const double gravitationalAcceleration)
    {
        return frontVelocityCu * sqrt(gravitationalAcceleration * waveRunup)
                * max(0.0, min(1.0, (waveRunup - verticalDistanceWaterLevelElevation) / (0.25 * waveRunup)));
    }

    double GrassRevetmentWaveRunupRayleighFunctions::WaveRunup(
        const double representativeWaveRunup2P,
        const int fixedNumberOfWaves,
        const int waveNumber)
    {
        return representativeWaveRunup2P * sqrt(log(1.0 - waveNumber / (fixedNumberOfWaves + 1.0)) / log(0.02));
    }
}

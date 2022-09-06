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

#include "GrassRevetmentOvertoppingFunctions.h"

#include <algorithm>
#include <cmath>

#include "GrassRevetmentFunctions.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentOvertoppingFunctions::CumulativeOverload(
        const GrassRevetmentOvertoppingCumulativeOverloadInput& input)
    {
        auto cumulativeFrontVelocity = 0.0;

        for (auto k = 1; k <= input._fixedNumberOfWaves; ++k)
        {
            const auto waveRunup = GrassRevetmentFunctions::WaveRunup(input._representativeWaveRunup2P, input._fixedNumberOfWaves, k);
            const auto frontVelocity = FrontVelocity(waveRunup, input._verticalDistanceWaterLevelElevation, input._frontVelocityCu,
                                                     input._gravitationalAcceleration);

            cumulativeFrontVelocity += max(0.0, input._increasedLoadTransitionAlphaM * pow(frontVelocity, 2.0)
                                           - input._reducedStrengthTransitionAlphaS * pow(input._criticalFrontVelocity, 2.0));
        }

        return input._averageNumberOfWaves / input._fixedNumberOfWaves * cumulativeFrontVelocity;
    }

    double GrassRevetmentOvertoppingFunctions::FrontVelocity(
        const double waveRunup,
        const double verticalDistanceWaterLevelElevation,
        const double frontVelocityCu,
        const double gravitationalAcceleration)
    {
        return frontVelocityCu * sqrt(gravitationalAcceleration * waveRunup)
                * max(0.0, min(1.0, (waveRunup - verticalDistanceWaterLevelElevation) / (0.25 * waveRunup)));
    }
}

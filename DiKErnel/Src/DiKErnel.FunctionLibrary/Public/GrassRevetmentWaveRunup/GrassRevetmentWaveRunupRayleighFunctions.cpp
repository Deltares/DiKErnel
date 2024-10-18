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

#include "GrassRevetmentWaveRunupRayleighFunctions.h"

#include <algorithm>
#include <cmath>
#include <functional>

#include "GrassRevetmentFunctions.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(
        const GrassRevetmentWaveRunupRayleighCumulativeOverloadInput& input)
    {
        const function getFrontVelocity = [&input](
            const double waveRunup)
        {
            return FrontVelocity(waveRunup, input._verticalDistanceWaterLevelElevation, input._frontVelocityCu, input._gravitationalAcceleration);
        };

        return GrassRevetmentFunctions::CumulativeOverload(input, getFrontVelocity);
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
}
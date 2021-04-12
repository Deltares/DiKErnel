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

#include "GrassRevetmentWaveRunupRayleigh.h"

#include <algorithm>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveRunupRayleigh::CumulativeOverload(
        const double averageNumberOfWaves,
        const double frontVelocity,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const int cumulativeOverloadNf)
    {
        auto sum = 0.0;

        for (auto i = 1; i <= cumulativeOverloadNf; ++i)
        {
            sum += max(increasedLoadTransitionAlphaM * pow(frontVelocity, 2.0)
                       - reducedStrengthTransitionAlphaS * pow(criticalFrontVelocity, 2.0), 0.0);
        }

        return averageNumberOfWaves / cumulativeOverloadNf * sum;
    }
}

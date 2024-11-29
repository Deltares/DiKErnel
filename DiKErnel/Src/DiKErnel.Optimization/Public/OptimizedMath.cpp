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

#include "OptimizedMath.h"

namespace DiKErnel::Optimization
{
    using namespace std;

    double OptimizedMath::OptimizedPow(
        double x,
        double y)
    {
        return pow(x, y);
    }

    double OptimizedMath::OptimizedImpactFactorAccumulation(
        const double fatigueAlpha,
        const double fatigueBeta,
        const double averageNumberOfWaves,
        const double logFailureTension,
        const double bendingStress,
        const std::vector<std::pair<double, double>>& impactFactors,
        const vector<double>& impactNumberLookup)
    {
        auto result = 0.0;

        for (int i = 0; i < impactFactors.size(); i++)
        {
            const auto logTension = log10(impactNumberLookup[i] * bendingStress);

            const auto fatigue = pow(10.0, -fatigueBeta * pow(max(0.0, logFailureTension - logTension), fatigueAlpha));

            result += impactFactors[i].second * averageNumberOfWaves * fatigue;
        }

        return result;
    }
}

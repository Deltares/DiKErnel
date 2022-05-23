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

#include "GrassRevetmentWaveRunupFunctions.h"

#include <algorithm>
#include <cmath>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveRunupFunctions::IncrementDamage(
        const double cumulativeOverload,
        const double criticalCumulativeOverload)
    {
        return cumulativeOverload / criticalCumulativeOverload;
    }

    double GrassRevetmentWaveRunupFunctions::RepresentativeWaveRunup2P(
        const double surfSimilarityParameter,
        const double waveAngleImpact,
        const double waveHeightHm0,
        const double representativeWaveRunup2PGammab,
        const double representativeWaveRunup2PGammaf,
        const double representativeWaveRunup2PAru,
        const double representativeWaveRunup2PBru,
        const double representativeWaveRunup2PCru)
    {
        return waveHeightHm0 * min(representativeWaveRunup2PAru * representativeWaveRunup2PGammab * representativeWaveRunup2PGammaf
                                   * waveAngleImpact * surfSimilarityParameter, representativeWaveRunup2PGammaf * waveAngleImpact
                                   * (representativeWaveRunup2PBru - representativeWaveRunup2PCru / sqrt(surfSimilarityParameter)));
    }

    double GrassRevetmentWaveRunupFunctions::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactAbeta,
        const double waveAngleImpactBetamax)
    {
        return 1.0 - waveAngleImpactAbeta * min(abs(waveAngle), waveAngleImpactBetamax);
    }
}

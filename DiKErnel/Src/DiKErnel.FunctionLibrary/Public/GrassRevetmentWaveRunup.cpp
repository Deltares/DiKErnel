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

#include "GrassRevetmentWaveRunup.h"

#include <algorithm>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveRunup::IncrementDamage(
        const double cumulativeOverload,
        const double criticalCumulativeOverload)
    {
        return cumulativeOverload / criticalCumulativeOverload;
    }

    double GrassRevetmentWaveRunup::AverageNumberOfWaves(
        const double incrementTime,
        const double wavePeriodTm10,
        const double averageNumberOfWavesCtm)
    {
        return incrementTime / (averageNumberOfWavesCtm * wavePeriodTm10);
    }

    double GrassRevetmentWaveRunup::RepresentativeWaveRunup2p(
        const double surfSimilarityParameter,
        const double waveAngleImpact,
        const double waveHeightHm0,
        const double representativeWaveRunup2pGammab,
        const double representativeWaveRunup2pGammaf,
        const double representativeWaveRunup2pAru,
        const double representativeWaveRunup2pBru,
        const double representativeWaveRunup2pCru)
    {
        return waveHeightHm0 * min(representativeWaveRunup2pAru * representativeWaveRunup2pGammab * representativeWaveRunup2pGammaf
                                   * waveAngleImpact * surfSimilarityParameter, representativeWaveRunup2pGammaf * waveAngleImpact
                                   * (representativeWaveRunup2pBru - representativeWaveRunup2pCru / sqrt(surfSimilarityParameter)));
    }

    double GrassRevetmentWaveRunup::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactAbeta,
        const double waveAngleImpactBetamax)
    {
        return 1.0 - waveAngleImpactAbeta * min(abs(waveAngle), waveAngleImpactBetamax);
    }
}

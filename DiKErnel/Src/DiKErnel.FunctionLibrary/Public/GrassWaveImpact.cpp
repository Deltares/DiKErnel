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

#include "GrassWaveImpact.h"

#include <algorithm>
#include <cmath>

#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassWaveImpact::IncrementDamage(
        const double incrementTime,
        const double failureTime,
        const double loadingOfRevetment)
    {
        return incrementTime / failureTime * loadingOfRevetment;
    }

    double GrassWaveImpact::FailureTime(
        const double waveHeight,
        const double failureTimeAgwi,
        const double failureTimeBgwi,
        const double failureTimeCgwi)
    {
        return 1 / failureTimeBgwi * log((waveHeight - failureTimeCgwi) / failureTimeAgwi);
    }

    double GrassWaveImpact::WaveHeight(
        const double minimumWaveHeight,
        const double maximumWaveHeight,
        const double waveAngleImpact,
        const double waveHeightHm0)
    {
        return min(maximumWaveHeight, max(waveAngleImpact * waveHeightHm0, minimumWaveHeight));
    }

    double GrassWaveImpact::MinimumWaveHeight(
        const double failureTimeAgwi,
        const double failureTimeBgwi,
        const double failureTimeCgwi,
        const double minimumWaveHeightTemax)
    {
        return failureTimeAgwi * exp(failureTimeBgwi * minimumWaveHeightTemax) + failureTimeCgwi;
    }

    double GrassWaveImpact::MaximumWaveHeight(
        const double failureTimeAgwi,
        const double failureTimeBgwi,
        const double failureTimeCgwi,
        const double minimumWaveHeightTemin)
    {
        return failureTimeAgwi * exp(failureTimeBgwi * minimumWaveHeightTemin) + failureTimeCgwi;
    }

    double GrassWaveImpact::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactNwa,
        const double waveAngleImpactQwa,
        const double waveAngleImpactRwa)
    {
        if (abs(waveAngle) <= 90.0)
        {
            return max(pow(cos(Generic::Radians(waveAngle)), waveAngleImpactNwa), waveAngleImpactQwa);
        }

        return max(waveAngleImpactQwa * ((90.0 + waveAngleImpactRwa - abs(waveAngle)) / waveAngleImpactRwa), 0.0);
    }
}

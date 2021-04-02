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

#include "GrassRevetmentWaveImpact.h"

#include <algorithm>
#include <cmath>

#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveImpact::IncrementDamage(
        const double incrementTime,
        const double timeLine)
    {
        return incrementTime / timeLine;
    }

    double GrassRevetmentWaveImpact::TimeLine(
        const double waveHeight,
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi)
    {
        return 1.0 / timeLineBgwi * log((waveHeight - timeLineCgwi) / timeLineAgwi);
    }

    double GrassRevetmentWaveImpact::WaveHeight(
        const double minimumWaveHeight,
        const double maximumWaveHeight,
        const double waveAngleImpact,
        const double waveHeightHm0)
    {
        return min(maximumWaveHeight, max(waveAngleImpact * waveHeightHm0, minimumWaveHeight));
    }

    double GrassRevetmentWaveImpact::MinimumWaveHeight(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double minimumWaveHeightTemax)
    {
        return timeLineAgwi * exp(timeLineBgwi * minimumWaveHeightTemax) + timeLineCgwi;
    }

    double GrassRevetmentWaveImpact::MaximumWaveHeight(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double maximumWaveHeightTemin)
    {
        return timeLineAgwi * exp(timeLineBgwi * maximumWaveHeightTemin) + timeLineCgwi;
    }

    double GrassRevetmentWaveImpact::WaveAngleImpact(
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

    double GrassRevetmentWaveImpact::UpperLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingAul)
    {
        return waterLevel - upperLimitLoadingAul * waveHeightHm0;
    }

    double GrassRevetmentWaveImpact::LowerLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingAll)
    {
        return waterLevel - lowerLimitLoadingAll * waveHeightHm0;
    }

    double GrassRevetmentWaveImpact::DurationInTimeStepFailure(
        const double timeLine,
        const double failureNumber,
        const double initialDamage)
    {
        return (failureNumber - initialDamage) * timeLine;
    }
}

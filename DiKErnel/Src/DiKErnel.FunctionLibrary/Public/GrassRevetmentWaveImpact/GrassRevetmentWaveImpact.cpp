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

#include "GenericFunctions.h"

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
        const double waveHeightImpact,
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi)
    {
        return 1.0 / timeLineBgwi * log((waveHeightImpact - timeLineCgwi) / timeLineAgwi);
    }

    double GrassRevetmentWaveImpact::WaveHeightImpact(
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
        return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, minimumWaveHeightTemax);
    }

    double GrassRevetmentWaveImpact::MaximumWaveHeight(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double maximumWaveHeightTemin)
    {
        return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, maximumWaveHeightTemin);
    }

    double GrassRevetmentWaveImpact::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactNwa,
        const double waveAngleImpactQwa,
        const double waveAngleImpactRwa)
    {
        if (abs(waveAngle) <= 90.0)
        {
            return max(pow(cos(GenericFunctions::Radians(waveAngle)), waveAngleImpactNwa), waveAngleImpactQwa);
        }

        return max(waveAngleImpactQwa * ((90.0 + waveAngleImpactRwa - abs(waveAngle)) / waveAngleImpactRwa), 0.0);
    }

    double GrassRevetmentWaveImpact::UpperLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingAul)
    {
        return LimitLoading(waterLevel, waveHeightHm0, upperLimitLoadingAul);
    }

    double GrassRevetmentWaveImpact::LowerLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingAll)
    {
        return LimitLoading(waterLevel, waveHeightHm0, lowerLimitLoadingAll);
    }

    double GrassRevetmentWaveImpact::WaveHeightBoundary(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double waveHeightCoefficient)
    {
        return timeLineAgwi * exp(timeLineBgwi * waveHeightCoefficient) + timeLineCgwi;
    }

    double GrassRevetmentWaveImpact::LimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double coefficientA)
    {
        return waterLevel - coefficientA * waveHeightHm0;
    }
}

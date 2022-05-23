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

#include "GrassRevetmentWaveImpactFunctions.h"

#include <algorithm>
#include <cmath>

#include "GenericFunctions.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double GrassRevetmentWaveImpactFunctions::IncrementDamage(
        const double incrementTime,
        const double timeLine)
    {
        return incrementTime / timeLine;
    }

    double GrassRevetmentWaveImpactFunctions::TimeLine(
        const double waveHeightImpact,
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi)
    {
        return 1.0 / timeLineBgwi * log((waveHeightImpact - timeLineCgwi) / timeLineAgwi);
    }

    double GrassRevetmentWaveImpactFunctions::WaveHeightImpact(
        const double minimumWaveHeight,
        const double maximumWaveHeight,
        const double waveAngleImpact,
        const double waveHeightHm0)
    {
        return min(maximumWaveHeight, max(waveAngleImpact * waveHeightHm0, minimumWaveHeight));
    }

    double GrassRevetmentWaveImpactFunctions::MinimumWaveHeight(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double minimumWaveHeightTemax)
    {
        return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, minimumWaveHeightTemax);
    }

    double GrassRevetmentWaveImpactFunctions::MaximumWaveHeight(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double maximumWaveHeightTemin)
    {
        return WaveHeightBoundary(timeLineAgwi, timeLineBgwi, timeLineCgwi, maximumWaveHeightTemin);
    }

    double GrassRevetmentWaveImpactFunctions::WaveAngleImpact(
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

    double GrassRevetmentWaveImpactFunctions::UpperLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingAul)
    {
        return LimitLoading(waterLevel, waveHeightHm0, upperLimitLoadingAul);
    }

    double GrassRevetmentWaveImpactFunctions::LowerLimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingAll)
    {
        return LimitLoading(waterLevel, waveHeightHm0, lowerLimitLoadingAll);
    }

    double GrassRevetmentWaveImpactFunctions::WaveHeightBoundary(
        const double timeLineAgwi,
        const double timeLineBgwi,
        const double timeLineCgwi,
        const double waveHeightCoefficient)
    {
        return timeLineAgwi * exp(timeLineBgwi * waveHeightCoefficient) + timeLineCgwi;
    }

    double GrassRevetmentWaveImpactFunctions::LimitLoading(
        const double waterLevel,
        const double waveHeightHm0,
        const double coefficientA)
    {
        return waterLevel - coefficientA * waveHeightHm0;
    }
}

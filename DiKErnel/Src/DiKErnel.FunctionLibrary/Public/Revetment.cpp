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

#include "Revetment.h"

#include <cmath>

#include "Constants.h"
#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace DomainLibrary;

    int Revetment::NumberOfTimeSteps(
        const int numberOfTimeStamps)
    {
        return numberOfTimeStamps - 1;
    }

    double Revetment::IncrementOfTime(
        const double startTime,
        const double endTime)
    {
        return endTime - startTime;
    }

    double Revetment::Damage(
        const double incrementOfDamage,
        const double initialDamage)
    {
        return initialDamage + incrementOfDamage;
    }

    bool Revetment::FailureOfRevetment(
        const double damage,
        const double failureNumber)
    {
        return damage >= failureNumber;
    }

    double Revetment::SlopeAngle(
        const double tanA)
    {
        return atan(Generic::Radians(tanA));
    }

    bool Revetment::LoadingOfRevetment(
        const double upperLimitLoadingOfRevetment,
        const double lowerLimitLoadingOfRevetment,
        const double positionZ)
    {
        return positionZ >= lowerLimitLoadingOfRevetment && positionZ <= upperLimitLoadingOfRevetment;
    }

    double Revetment::SurfSimilarityParameter(
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10)
    {
        return tanA / sqrt(2.0 * Constants::PI * waveHeightHm0 / (Constants::GRAVITATIONAL_ACCELERATION * pow(wavePeriodTm10, 2.0)));
    }

    double Revetment::WaveSteepnessDeepWater(
        const double waveHeightHm0,
        const double wavePeriodTm10)
    {
        return waveHeightHm0 / (Constants::GRAVITATIONAL_ACCELERATION / (2.0 * Constants::PI) * pow(wavePeriodTm10, 2.0));
    }
}

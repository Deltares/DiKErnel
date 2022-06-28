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

#include "RevetmentFunctions.h"

#include <cmath>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    int RevetmentFunctions::IncrementTime(
        const int beginTime,
        const int endTime)
    {
        return endTime - beginTime;
    }

    double RevetmentFunctions::AverageNumberOfWaves(
        const double incrementTime,
        const double wavePeriodTm10,
        const double averageNumberOfWavesCtm)
    {
        return incrementTime / (averageNumberOfWavesCtm * wavePeriodTm10);
    }

    double RevetmentFunctions::Damage(
        const double incrementDamage,
        const double initialDamage)
    {
        return initialDamage + incrementDamage;
    }

    bool RevetmentFunctions::FailureRevetment(
        const double damage,
        const double initialDamage,
        const double failureNumber)
    {
        return initialDamage < failureNumber && damage >= failureNumber;
    }

    double RevetmentFunctions::DurationInTimeStepFailure(
        const double incrementTime,
        const double incrementDamage,
        const double failureNumber,
        const double initialDamage)
    {
        return (failureNumber - initialDamage) / incrementDamage * incrementTime;
    }

    int RevetmentFunctions::TimeOfFailure(
        const double durationInTimeStepFailure,
        const double beginTime)
    {
        return static_cast<int>(ceil(durationInTimeStepFailure + beginTime));
    }
}

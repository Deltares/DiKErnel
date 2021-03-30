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

namespace DiKErnel::FunctionLibrary
{
    int Revetment::NumberOfTimeSteps(
        const int numberOfTimeStamps)
    {
        return numberOfTimeStamps - 1;
    }

    int Revetment::IncrementTime(
        const int startTime,
        const int endTime)
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
        const double initialDamage,
        const double failureNumber)
    {
        return initialDamage < failureNumber && damage >= failureNumber;
    }
}

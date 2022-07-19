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

#include "TimeDependentOutput.h"

#include "InvalidTimeDependentOutputException.h"

namespace DiKErnel::Core
{
    using namespace std;

    TimeDependentOutput::TimeDependentOutput(
        const double incrementDamage,
        const double damage,
        unique_ptr<int> timeOfFailure)
        : _incrementDamage(make_unique<double>(incrementDamage)),
          _damage(make_unique<double>(damage)),
          _timeOfFailure(move(timeOfFailure)) {}

    TimeDependentOutput::TimeDependentOutput(
        TimeDependentOutputConstructionProperties& constructionProperties)
        : _incrementDamage(move(constructionProperties._incrementDamage)),
          _damage(move(constructionProperties._damage)),
          _timeOfFailure(move(constructionProperties._timeOfFailure))
    {
        ThrowExceptionWhenPropertyIsNullPtr(_incrementDamage.get(), "incrementDamage");
        ThrowExceptionWhenPropertyIsNullPtr(_damage.get(), "damage");
    }

    double TimeDependentOutput::GetIncrementDamage() const
    {
        return *_incrementDamage;
    }

    double TimeDependentOutput::GetDamage() const
    {
        return *_damage;
    }

    const int* TimeDependentOutput::GetTimeOfFailure() const
    {
        return _timeOfFailure.get();
    }

    template <typename T>
    void TimeDependentOutput::ThrowExceptionWhenPropertyIsNullPtr(
        const T* propertyValue,
        const string& propertyName)
    {
        if (propertyValue == nullptr)
        {
            throw InvalidTimeDependentOutputException(propertyName + " must be set.");
        }
    }
}

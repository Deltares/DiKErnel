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

#include "CalculationInput.h"

#include "InvalidCalculationDataException.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    CalculationInput::CalculationInput(
        vector<unique_ptr<LocationDependentInput>> locationDependentInputItems,
        vector<unique_ptr<TimeDependentInput>> timeDependentInputItems,
        const double maximumWaveAngle)
        : _locationDependentInputItems(move(locationDependentInputItems)),
          _timeDependentInputItems(move(timeDependentInputItems)),
          _maximumWaveAngle(maximumWaveAngle)
    {
        auto previousEndTime = INT_MIN;
        for (const auto& timeDependentInput : _timeDependentInputItems)
        {
            if (previousEndTime != INT_MIN && timeDependentInput->GetBeginTime() != previousEndTime)
            {
                throw InvalidCalculationDataException("The begin time of an element must connect to the end time of the previous element.");
            }

            previousEndTime = timeDependentInput->GetEndTime();

            _timeDependentInputItemReferences.emplace_back(*timeDependentInput);
        }

        for (const auto& locationDependentInput : _locationDependentInputItems)
        {
            _locationDependentInputItemReferences.emplace_back(*locationDependentInput);
        }
    }

    const vector<reference_wrapper<ILocationDependentInput>>& CalculationInput::GetLocationDependentInputItems() const
    {
        return _locationDependentInputItemReferences;
    }

    const vector<reference_wrapper<ITimeDependentInput>>& CalculationInput::GetTimeDependentInputItems() const
    {
        return _timeDependentInputItemReferences;
    }

    double CalculationInput::GetMaximumWaveAngle() const
    {
        return _maximumWaveAngle;
    }
}

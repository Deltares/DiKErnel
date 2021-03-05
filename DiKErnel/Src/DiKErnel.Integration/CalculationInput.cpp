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
        vector<unique_ptr<LocationDependentData>> locationDependentDataItems,
        vector<unique_ptr<TimeDependentData>> timeDependentDataItems,
        const double maximumWaveAngle)
        : _locationDependentDataItems(move(locationDependentDataItems)),
          _timeDependentDataItems(move(timeDependentDataItems)),
          _maximumWaveAngle(maximumWaveAngle)
    {
        auto previousEndTime = INT_MIN;
        for (const auto& timeDependentData : _timeDependentDataItems)
        {
            if (previousEndTime != INT_MIN && timeDependentData->GetBeginTime() != previousEndTime)
            {
                throw Core::InvalidCalculationDataException("The begin time of an element must connect to the end time of the previous element.");
            }
            previousEndTime = timeDependentData->GetEndTime();

            _timeDependentDataItemReferences.emplace_back(*timeDependentData);
        }

        for (const auto& locationDependentData : _locationDependentDataItems)
        {
            _locationDependentDataItemReferences.emplace_back(*locationDependentData);
        }
    }

    const vector<reference_wrapper<ILocationDependentData>>& CalculationInput::GetLocationDependentDataItems() const
    {
        return _locationDependentDataItemReferences;
    }

    const vector<reference_wrapper<ITimeDependentData>>& CalculationInput::GetTimeDependentDataItems() const
    {
        return _timeDependentDataItemReferences;
    }

    double CalculationInput::GetMaximumWaveAngle() const
    {
        return _maximumWaveAngle;
    }
}

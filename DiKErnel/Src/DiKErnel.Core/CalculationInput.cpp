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

namespace DiKErnel::Core
{
    using namespace std;

    CalculationInput::CalculationInput(
        vector<unique_ptr<LocationDependentData>> locationDependentDataItems,
        vector<unique_ptr<TimeDependentData>> timeDependentDataItems,
        const double maximumWaveAngle)
        : locationDependentDataItems(move(locationDependentDataItems)),
          timeDependentDataItems(move(timeDependentDataItems)),
          maximumWaveAngle(maximumWaveAngle)
    {
        auto previousEndTime = INT_MIN;
        for (const auto& timeDependentData : this->timeDependentDataItems)
        {
            if(previousEndTime != INT_MIN && timeDependentData->GetBeginTime() != previousEndTime)
            {
                throw InvalidCalculationDataException("The begin time of an element must connect to the end time of the previous element.");
            }
            previousEndTime = timeDependentData->GetEndTime();

            timeDependentDataItemReferences.emplace_back(*timeDependentData);
        }


        for (const auto& locationDependentData : this->locationDependentDataItems)
        {
            locationDependentDataItemReferences.emplace_back(*locationDependentData);
        }
    }

    const vector<reference_wrapper<LocationDependentData>>& CalculationInput::GetLocationDependentDataItems() const
    {
        return locationDependentDataItemReferences;
    }

    const vector<reference_wrapper<TimeDependentData>>& CalculationInput::GetTimeDependentDataItems() const
    {
        return timeDependentDataItemReferences;
    }

    double CalculationInput::GetMaximumWaveAngle() const
    {
        return maximumWaveAngle;
    }
}

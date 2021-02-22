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

namespace DiKErnel::Core
{
    using namespace std;

    CalculationInput::CalculationInput(
        vector<unique_ptr<ILocationDependentData>> locationDependentDataItems,
        vector<unique_ptr<TimeStep>> timeSteps)
        : locationDependentDataItems(move(locationDependentDataItems)),
          timeSteps(move(timeSteps))
    {
        for (const auto& locationDependentData : this->locationDependentDataItems)
        {
            locationDependentDataItemReferences.emplace_back(*locationDependentData);
        }

        for (const auto& timeStep : this->timeSteps)
        {
            timeStepsReferences.emplace_back(*timeStep);
        }
    }

    const vector<reference_wrapper<ILocationDependentData>>& CalculationInput::GetLocationDependentDataItems() const
    {
        return locationDependentDataItemReferences;
    }

    const vector<reference_wrapper<TimeStep>>& CalculationInput::GetTimeSteps() const
    {
        return timeStepsReferences;
    }
}

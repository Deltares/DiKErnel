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
        vector<unique_ptr<ILocationCalculationInput>> locations,
        vector<unique_ptr<TimeStep>> timeSteps)
        : locations(move(locations)),
          timeSteps(move(timeSteps))
    {
        for (const auto& location : this->locations)
        {
            locationsReferences.emplace_back(*location);
        }

        for (const auto& timeStep : this->timeSteps)
        {
            timeStepsReferences.emplace_back(*timeStep);
        }
    }

    const vector<reference_wrapper<ILocationCalculationInput>>& CalculationInput::GetLocations() const
    {
        return locationsReferences;
    }

    const vector<reference_wrapper<TimeStep>>& CalculationInput::GetTimeSteps() const
    {
        return timeStepsReferences;
    }
}

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

#include "CalculationInput.h"

#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;
    using namespace Util;

    CalculationInput::CalculationInput(
        unique_ptr<IProfileData> profileData,
        vector<unique_ptr<ILocationDependentInput>> locationDependentInputItems,
        vector<unique_ptr<ITimeDependentInput>> timeDependentInputItems)
        : _profileData(move(profileData)),
          _locationDependentInputItems(move(locationDependentInputItems)),
          _timeDependentInputItems(move(timeDependentInputItems))
    {
        for (const auto& timeDependentInput : _timeDependentInputItems)
        {
            _timeDependentInputItemReferences.emplace_back(*timeDependentInput);
        }

        for (const auto& locationDependentInput : _locationDependentInputItems)
        {
            _locationDependentInputItemReferences.emplace_back(*locationDependentInput);
        }
    }

    const IProfileData& CalculationInput::GetProfileData() const
    {
        return *_profileData;
    }

    const vector<reference_wrapper<ILocationDependentInput>>& CalculationInput::GetLocationDependentInputItems() const
    {
        return _locationDependentInputItemReferences;
    }

    const vector<reference_wrapper<ITimeDependentInput>>& CalculationInput::GetTimeDependentInputItems() const
    {
        return _timeDependentInputItemReferences;
    }
}

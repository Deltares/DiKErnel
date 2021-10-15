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

#include "LocationDependentOutput.h"

#include <utility>

namespace DiKErnel::Core
{
    using namespace std;

    LocationDependentOutput::LocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
        : _timeDependentOutputItems(move(timeDependentOutputItems))
    {
        for (const auto& timeDependentOutput : _timeDependentOutputItems)
        {
            _timeDependentOutputItemReferences.emplace_back(*timeDependentOutput);
        }

        for (const auto& timeDependentOutput : _timeDependentOutputItems)
        {
            _damages.push_back(timeDependentOutput->GetDamage());

            if (timeDependentOutput->GetTimeOfFailure() != nullptr)
            {
                _timeOfFailure = make_unique<int>(*timeDependentOutput->GetTimeOfFailure());
            }
        }
    }

    const vector<double>& LocationDependentOutput::GetDamages() const
    {
        return _damages;
    }

    const int* LocationDependentOutput::GetTimeOfFailure() const
    {
        return _timeOfFailure.get();
    }

    const vector<reference_wrapper<TimeDependentOutput>>& LocationDependentOutput::GetTimeDependentOutputItems() const
    {
        return _timeDependentOutputItemReferences;
    }
}

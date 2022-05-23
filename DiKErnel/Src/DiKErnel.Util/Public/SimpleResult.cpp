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

#include "SimpleResult.h"

namespace DiKErnel::Util
{
    using namespace std;

    SimpleResult::SimpleResult(
        const bool successful,
        vector<unique_ptr<Event>> events)
        : _successful(successful),
          _events(move(events))
    {
        for (const auto& event : _events)
        {
            _eventReferences.emplace_back(*event);
        }
    }

    bool SimpleResult::GetSuccessful() const
    {
        return _successful;
    }

    const vector<reference_wrapper<Event>>& SimpleResult::GetEvents() const
    {
        return _eventReferences;
    }
}

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

#include "EventRegistry.h"

namespace DiKErnel::Util
{
    using namespace std;

    thread_local EventRegistry* EventRegistry::_eventRegistry;

    void EventRegistry::Register(
        unique_ptr<Event> event)
    {
        auto& eventRegistryInstance = GetInstance();

        eventRegistryInstance._events.push_back(move(event));
        eventRegistryInstance._eventReferences.emplace_back(*eventRegistryInstance._events.back());
    }

    const vector<reference_wrapper<Event>>& EventRegistry::GetEvents()
    {
        return GetInstance()._eventReferences;
    }

    void EventRegistry::Flush()
    {
        auto& eventRegistryInstance = GetInstance();

        eventRegistryInstance._events.clear();
        eventRegistryInstance._eventReferences.clear();
    }

    EventRegistry& EventRegistry::GetInstance()
    {
        if (_eventRegistry == nullptr)
        {
            _eventRegistry = new EventRegistry();
        }

        return *_eventRegistry;
    }
}

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

#include "EventRegistryTestHelper.h"

#include "EventRegistry.h"

namespace DiKErnel::Util::TestUtil
{
    using namespace std;

    EventRegistryTestHelper::EventRegistryTestHelper(
        int numberOfEventsToRegister)
    {
        _thread = jthread(
            &EventRegistryTestHelper::PerformTest,
            this,
            numberOfEventsToRegister,
            ref(_registeredEvents),
            ref(_registeredEventReferences));
    }

    void EventRegistryTestHelper::WaitForCompletion()
    {
        if (_thread.joinable())
        {
            _thread.join();
        }
    }

    const vector<reference_wrapper<Event>>& EventRegistryTestHelper::GetRegisteredEvents() const
    {
        return _registeredEventReferences;
    }

    void EventRegistryTestHelper::PerformTest(
        const int numberOfEventsToRegister,
        vector<unique_ptr<Event>>& registeredEvents,
        vector<reference_wrapper<Event>>& registeredEventReferences) const
    {
        for (auto i = 0; i < numberOfEventsToRegister; ++i)
        {
            EventRegistry::Register(make_unique<Event>("Event " + to_string(i), EventType::Error));
        }

        for (unique_ptr<Event>& registeredEvent : EventRegistry::Flush())
        {
            registeredEvents.push_back(move(registeredEvent));
            registeredEventReferences.emplace_back(*registeredEvents.back());
        }
    }
}

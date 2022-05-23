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

#pragma once

#include <memory>
#include <thread>
#include <vector>

#include "Event.h"

namespace DiKErnel::Util::TestUtil
{
    class EventRegistryTestHelper
    {
        public:
            explicit EventRegistryTestHelper(
                int numberOfEventsToRegister);

            void WaitForCompletion();

            const std::vector<std::reference_wrapper<Event>>& GetRegisteredEvents() const;

        private:
            std::thread _thread;
            std::vector<std::unique_ptr<Event>> _registeredEvents = std::vector<std::unique_ptr<Event>>();
            std::vector<std::reference_wrapper<Event>> _registeredEventReferences = std::vector<std::reference_wrapper<Event>>();

            void PerformTest(
                int numberOfEventsToRegister,
                std::vector<std::unique_ptr<Event>>& registeredEvents,
                std::vector<std::reference_wrapper<Event>>& registeredEventReferences) const;
    };
}

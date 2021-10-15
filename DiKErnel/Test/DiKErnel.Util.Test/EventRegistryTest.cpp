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

#include <thread>

#include <gtest/gtest.h>

#include "EventRegistry.h"
#include "EventRegistryTestHelper.h"

namespace DiKErnel::Util::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct EventRegistryTest : Test
    {
        /*!
         * \brief Creates a new instance.
         * \remarks This makes sure that the event registry is always flushed before a test is done
         *          to prevent interference from other tests.
         */
        explicit EventRegistryTest()
        {
            EventRegistry::Flush();
        }
    };

    TEST_F(EventRegistryTest, GivenEventRegistryWithoutEventsRegistered_WhenGetEvents_ThenReturnsEmptyCollection)
    {
        // When
        const auto& registeredEvents = EventRegistry::GetEvents();

        // Then
        ASSERT_EQ(0, registeredEvents.size());
    }

    TEST_F(EventRegistryTest, GivenEventRegistryWithEventsRegistered_WhenGetEvents_ThenReturnsRegisteredEvents)
    {
        // Given
        const auto message1 = "Warning message";
        const auto eventType1 = EventType::Warning;
        const auto message2 = "Error message";
        const auto eventType2 = EventType::Error;

        EventRegistry::Register(make_unique<Event>(message1, eventType1));
        EventRegistry::Register(make_unique<Event>(message2, eventType2));

        // When
        const auto& registeredEvents = EventRegistry::GetEvents();

        // Then
        ASSERT_EQ(2, registeredEvents.size());

        const auto& registeredEvent1 = registeredEvents.at(0).get();
        ASSERT_EQ(message1, registeredEvent1.GetMessage());
        ASSERT_EQ(eventType1, registeredEvent1.GetEventType());

        const auto& registeredEvent2 = registeredEvents.at(1).get();
        ASSERT_EQ(message2, registeredEvent2.GetMessage());
        ASSERT_EQ(eventType2, registeredEvent2.GetEventType());
    }

    TEST_F(EventRegistryTest, GivenEventRegistryWithEventsRegisteredOnDifferentThreads_WhenGetEvents_ThenReturnsDifferentEventsPerThread)
    {
        // Given
        EventRegistryTestHelper testHelperThread1(10000);
        testHelperThread1.WaitForCompletion();
        EventRegistryTestHelper testHelperThread2(20000);
        testHelperThread2.WaitForCompletion();

        // When
        const auto& registeredEvents1 = testHelperThread1.GetRegisteredEvents();
        const auto& registeredEvents2 = testHelperThread2.GetRegisteredEvents();

        // Then
        ASSERT_EQ(10000, registeredEvents1.size());
        ASSERT_EQ(20000, registeredEvents2.size());
        ASSERT_EQ(0, EventRegistry::GetEvents().size());
    }

    TEST_F(EventRegistryTest, GivenEventRegistryWithEventsRegistered_WhenFlush_ThenRegisteredEventsCleared)
    {
        // Given
        EventRegistry::Register(make_unique<Event>("Warning message", EventType::Warning));
        EventRegistry::Register(make_unique<Event>("Error message", EventType::Error));

        // Precondition
        ASSERT_EQ(2, EventRegistry::GetEvents().size());

        // When
        EventRegistry::Flush();

        // Then
        ASSERT_EQ(0, EventRegistry::GetEvents().size());
    }
}

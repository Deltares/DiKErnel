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

#include "EventAssertHelper.h"
#include "EventRegistry.h"
#include "EventRegistryTestHelper.h"

namespace DiKErnel::Util::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(EventRegistryTest, GivenEventRegistryWithoutEventsRegistered_WhenFlush_ThenReturnsEmptyCollection)
    {
        // When
        const auto& registeredEvents = EventRegistry::Flush();

        // Then
        ASSERT_EQ(0, registeredEvents.size());
    }

    TEST(EventRegistryTest, GivenEventRegistryWithEventsRegistered_WhenFlush_ThenReturnsRegisteredEvents)
    {
        // Given
        constexpr auto message1 = "Warning message";
        constexpr auto eventType1 = EventType::Warning;
        constexpr auto message2 = "Error message";
        constexpr auto eventType2 = EventType::Error;

        EventRegistry::Register(make_unique<Event>(message1, eventType1));
        EventRegistry::Register(make_unique<Event>(message2, eventType2));

        // When
        const auto& registeredEvents = EventRegistry::Flush();

        // Then
        ASSERT_EQ(2, registeredEvents.size());

        EventAssertHelper::AssertEvent(eventType1, message1, *registeredEvents.at(0));
        EventAssertHelper::AssertEvent(eventType2, message2, *registeredEvents.at(1));
    }

    TEST(EventRegistryTest, GivenEventRegistryWithEventsRegisteredOnDifferentThreads_WhenFlush_ThenReturnsDifferentEventsPerThread)
    {
        // Given
        EventRegistryTestHelper testHelperThread1(10000);
        testHelperThread1.WaitForCompletion();
        EventRegistryTestHelper testHelperThread2(20000);
        testHelperThread2.WaitForCompletion();

        // When
        const auto& registeredEvents1 = testHelperThread1.GetRegisteredEvents();
        const auto& registeredEvents2 = testHelperThread2.GetRegisteredEvents();
        const auto& registeredEvents3 = EventRegistry::Flush();

        // Then
        ASSERT_EQ(10000, registeredEvents1.size());
        ASSERT_EQ(20000, registeredEvents2.size());
        ASSERT_EQ(0, registeredEvents3.size());
    }

    TEST(EventRegistryTest, GivenEventRegistryWithEventsRegisteredAndFlushed_WhenFlush_ThenNoRegisteredEvents)
    {
        // Given
        EventRegistry::Register(make_unique<Event>("Warning message", EventType::Warning));
        EventRegistry::Register(make_unique<Event>("Error message", EventType::Error));

        // Precondition
        ASSERT_EQ(2, EventRegistry::Flush().size());

        // When
        const auto& registeredEvents = EventRegistry::Flush();

        // Then
        ASSERT_EQ(0, registeredEvents.size());
    }
}

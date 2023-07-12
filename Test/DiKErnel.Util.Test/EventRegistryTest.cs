// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using System.Linq;
using DiKErnel.Util.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Util.Test
{
    public class EventRegistryTest
    {
        [Test]
        public void GivenEventRegistryWithoutEventsRegistered_WhenFlush_ThenReturnsEmptyCollection()
        {
            // When
            IEnumerable<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.IsEmpty(registeredEvents);
        }

        [Test]
        public void GivenEventRegistryWithEventsRegistered_WhenFlush_ThenReturnsRegisteredEvents()
        {
            // Given
            const string message1 = "Warning message";
            const EventType eventType1 = EventType.Warning;
            const string message2 = "Error message";
            const EventType eventType2 = EventType.Error;

            EventRegistry.Register(new Event(message1, eventType1));
            EventRegistry.Register(new Event(message2, eventType2));

            // When
            IEnumerable<Event> registeredEvents = EventRegistry.Flush().ToList();

            // Then
            Assert.AreEqual(2, registeredEvents.Count());

            EventAssertHelper.AssertEvent(eventType1, message1, registeredEvents.ElementAt(0));
            EventAssertHelper.AssertEvent(eventType2, message2, registeredEvents.ElementAt(1));
        }

        [Test]
        public void GivenEventRegistryWithEventsRegisteredOnDifferentThreads_WhenFlush_ThenReturnsDifferentEventsPerThread()
        {
            // Given
            var testHelperThread1 = new EventRegistryTestHelper(10000);
            testHelperThread1.WaitForCompletion();
            var testHelperThread2 = new EventRegistryTestHelper(20000);
            testHelperThread2.WaitForCompletion();

            // When
            IEnumerable<Event> registeredEvents1 = testHelperThread1.GetRegisteredEvents();
            IEnumerable<Event> registeredEvents2 = testHelperThread2.GetRegisteredEvents();
            IEnumerable<Event> registeredEvents3 = EventRegistry.Flush();

            // Then
            Assert.AreEqual(10000, registeredEvents1.Count());
            Assert.AreEqual(20000, registeredEvents2.Count());
            Assert.IsEmpty(registeredEvents3);
        }

        [Test]
        public void GivenEventRegistryWithEventsRegisteredAndFlushed_WhenFlush_ThenNoRegisteredEvents()
        {
            // Given
            EventRegistry.Register(new Event("Warning message", EventType.Warning));
            EventRegistry.Register(new Event("Error message", EventType.Error));

            // Precondition
            Assert.AreEqual(2, EventRegistry.Flush().Count());

            // When
            IEnumerable<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.IsEmpty(registeredEvents);
        }
    }
}
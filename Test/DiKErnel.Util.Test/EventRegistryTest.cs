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
            var event1 = new Event("Warning message", EventType.Warning);
            var event2 = new Event("Error message", EventType.Error);

            EventRegistry.Register(event1);
            EventRegistry.Register(event2);

            // When
            IEnumerable<Event> registeredEvents = EventRegistry.Flush().ToList();

            // Then
            Assert.AreEqual(2, registeredEvents.Count());
            Assert.AreSame(event1, registeredEvents.ElementAt(0));
            Assert.AreSame(event2, registeredEvents.ElementAt(1));
        }

        [Test]
        public void GivenEventRegistryWithEventsRegisteredOnDifferentThreads_WhenFlush_ThenReturnsDifferentEventsPerThread()
        {
            // Given
            var testHelperThread1 = new EventRegistryTestHelper(10000);
            var testHelperThread2 = new EventRegistryTestHelper(20000);

            // When
            testHelperThread1.WaitForCompletion();
            testHelperThread2.WaitForCompletion();
            IEnumerable<Event> registeredEventsOnMainThread = EventRegistry.Flush();

            // Then
            Assert.AreEqual(10000, testHelperThread1.RegisteredEvents.Count());
            Assert.AreEqual(20000, testHelperThread2.RegisteredEvents.Count());
            Assert.IsEmpty(registeredEventsOnMainThread);
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
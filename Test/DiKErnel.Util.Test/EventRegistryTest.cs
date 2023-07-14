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

using System;
using System.Collections.Generic;
using System.Linq;
using DiKErnel.TestUtil;
using DiKErnel.Util.TestUtil;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

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
            var event1 = new Event(Random.NextString(), Random.NextEnumValue<EventType>());
            var event2 = new Event(Random.NextString(), Random.NextEnumValue<EventType>());

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
            var registeredEventsOnMainThread = new List<Event>();
            int numberOfEventsToRegisterOnFirstThread = Random.Next(0, 10000);
            int numberOfEventsToRegisterOnSecondThread = Random.Next(10000, 20000);
            var testHelperThread1 = new EventRegistryTestHelper(numberOfEventsToRegisterOnFirstThread);
            var testHelperThread2 = new EventRegistryTestHelper(numberOfEventsToRegisterOnSecondThread);

            // When
            registeredEventsOnMainThread.AddRange(EventRegistry.Flush());
            testHelperThread1.WaitForCompletion();
            registeredEventsOnMainThread.AddRange(EventRegistry.Flush());
            testHelperThread2.WaitForCompletion();
            registeredEventsOnMainThread.AddRange(EventRegistry.Flush());

            // Then
            Assert.AreEqual(numberOfEventsToRegisterOnFirstThread, testHelperThread1.RegisteredEvents.Count());
            Assert.AreEqual(numberOfEventsToRegisterOnSecondThread, testHelperThread2.RegisteredEvents.Count());
            Assert.IsEmpty(registeredEventsOnMainThread);
        }

        [Test]
        public void GivenEventRegistryWithEventsRegisteredAndFlushed_WhenFlush_ThenNoRegisteredEvents()
        {
            // Given
            EventRegistry.Register(new Event(Random.NextString(), Random.NextEnumValue<EventType>()));
            EventRegistry.Register(new Event(Random.NextString(), Random.NextEnumValue<EventType>()));

            // Precondition
            Assert.AreEqual(2, EventRegistry.Flush().Count());

            // When
            IEnumerable<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.IsEmpty(registeredEvents);
        }
    }
}
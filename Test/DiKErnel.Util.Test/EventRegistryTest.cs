// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.TestUtil;
using DiKErnel.Util.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Util.Test
{
    [TestFixture]
    internal sealed class EventRegistryTest
    {
        [Test]
        public void GivenEventRegistryWithoutEventsRegistered_WhenFlush_ThenReturnsEmptyCollection()
        {
            // When
            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.That(registeredEvents, Is.Empty);
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
            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.That(registeredEvents, Has.Count.EqualTo(2));
            Assert.That(registeredEvents[0], Is.SameAs(event1));
            Assert.That(registeredEvents[1], Is.SameAs(event2));
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
            Assert.That(testHelperThread1.RegisteredEvents, Has.Count.EqualTo(numberOfEventsToRegisterOnFirstThread));
            Assert.That(testHelperThread2.RegisteredEvents, Has.Count.EqualTo(numberOfEventsToRegisterOnSecondThread));
            Assert.That(registeredEventsOnMainThread, Is.Empty);
        }

        [Test]
        public void GivenEventRegistryWithEventsRegisteredAndFlushed_WhenFlush_ThenNoRegisteredEvents()
        {
            // Given
            EventRegistry.Register(new Event(Random.NextString(), Random.NextEnumValue<EventType>()));
            EventRegistry.Register(new Event(Random.NextString(), Random.NextEnumValue<EventType>()));

            // Precondition
            Assert.That(EventRegistry.Flush(), Has.Count.EqualTo(2));

            // When
            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();

            // Then
            Assert.That(registeredEvents, Is.Empty);
        }
    }
}
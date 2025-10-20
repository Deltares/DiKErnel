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
using System.Threading;

namespace DiKErnel.Util.TestUtil
{
    public class EventRegistryTestHelper
    {
        private readonly Thread thread;
        private readonly List<Event> registeredEvents;

        public EventRegistryTestHelper(int numberOfEventsToRegister)
        {
            registeredEvents = new List<Event>();
            thread = new Thread(() => PerformTest(numberOfEventsToRegister));
            thread.Start();
        }

        public IReadOnlyList<Event> RegisteredEvents => registeredEvents;

        public void WaitForCompletion()
        {
            if (Thread.CurrentThread != thread)
            {
                thread.Join();
            }
        }

        private void PerformTest(int numberOfEventsToRegister)
        {
            for (var i = 0; i < numberOfEventsToRegister; i++)
            {
                EventRegistry.Register(new Event($"Event {i}", EventType.Error));
            }

            registeredEvents.AddRange(EventRegistry.Flush());
        }
    }
}
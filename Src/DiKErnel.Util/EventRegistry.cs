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

namespace DiKErnel.Util
{
    /// <summary>
    /// Class where events can be registered and tracked on a per thread basis.
    /// </summary>
    public class EventRegistry
    {
        private static readonly EventRegistry instance = new EventRegistry();
        private readonly List<Event> events = new List<Event>();

        /// <summary>
        /// Registers an event.
        /// </summary>
        /// <param name="inEvent">The event to register.</param>
        public static void Register(Event inEvent)
        {
            instance.events.Add(inEvent);
        }

        /// <summary>
        /// Flushes all registered events.
        /// </summary>
        /// <returns>The registered events.</returns>
        public static IEnumerable<Event> Flush()
        {
            List<Event> tempEvents = instance.events.ToList();
            instance.events.Clear();

            return tempEvents;
        }
    }
}
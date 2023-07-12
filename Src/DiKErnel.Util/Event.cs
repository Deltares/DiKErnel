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

namespace DiKErnel.Util
{
    /// <summary>
    /// Class containing event data.
    /// </summary>
    public class Event
    {
        private readonly string message;
        private readonly EventType eventType;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="eventType">The event type.</param>
        public Event(string message, EventType eventType)
        {
            this.message = message;
            this.eventType = eventType;
        }

        /// <summary>
        /// Gets the message.
        /// </summary>
        /// <returns>The message.</returns>
        public string GetMessage()
        {
            return message;
        }

        /// <summary>
        /// Gets the event type.
        /// </summary>
        /// <returns>The event type.</returns>
        public EventType GetEventType()
        {
            return eventType;
        }
    }
}
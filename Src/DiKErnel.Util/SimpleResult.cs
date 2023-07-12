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

namespace DiKErnel.Util
{
    /// <summary>
    /// Class that holds information about the result of an operation and the events that occurred.
    /// </summary>
    public class SimpleResult
    {
        private readonly bool successful;
        private readonly IEnumerable<Event> events;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="successful">Whether the operation was successful.</param>
        /// <param name="events">The events that occurred.</param>
        public SimpleResult(bool successful, IEnumerable<Event> events)
        {
            this.successful = successful;
            this.events = events;
        }

        /// <summary>
        /// Gets whether the operation was successful.
        /// </summary>
        /// <returns>Whether the operation was successful.</returns>
        public bool GetSuccessful()
        {
            return successful;
        }

        /// <summary>
        /// Gets the events.
        /// </summary>
        /// <returns>The events.</returns>
        public IEnumerable<Event> GetEvents()
        {
            return events;
        }
    }
}
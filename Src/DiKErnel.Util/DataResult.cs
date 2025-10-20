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

namespace DiKErnel.Util
{
    /// <summary>
    /// Class that holds information about the result of an operation, the events that
    /// occurred and the data that was produced.
    /// </summary>
    /// <typeparam name="T">The type of the data that was produced.</typeparam>
    public class DataResult<T> : SimpleResult
    {
        /// <summary>
        /// Creates a new instance in case the operation was not successful.
        /// </summary>
        /// <param name="events">The events that occurred.</param>
        public DataResult(IReadOnlyList<Event> events) : base(false, events)
        {
            Data = default;
        }

        /// <summary>
        /// Creates a new instance in case the operation was successful.
        /// </summary>
        /// <param name="data">The data that was produced.</param>
        /// <param name="events">The events that occurred.</param>
        public DataResult(T data, IReadOnlyList<Event> events) : base(true, events)
        {
            Data = data;
        }

        /// <summary>
        /// Gets the data that was produced.
        /// </summary>
        public T Data { get; }
    }
}
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
    [TestFixture]
    public class DataResultTest
    {
        [Test]
        public void Constructor_WithData_ExpectedValues()
        {
            // Setup
            const int data = 45;
            const string message = "Test message";
            const EventType eventType = EventType.Error;

            var events = new List<Event>
            {
                new Event(message, eventType)
            };

            // Call
            var result = new DataResult<int>(data, events);

            // Assert
            Assert.True(result.GetSuccessful());

            Assert.AreEqual(1, result.GetEvents().Count());
            EventAssertHelper.AssertEvent(eventType, message, result.GetEvents().ElementAt(0));

            Assert.AreEqual(data, result.GetData());
        }
    }
}
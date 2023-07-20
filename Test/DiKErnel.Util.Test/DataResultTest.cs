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
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Util.Test
{
    [TestFixture]
    public class DataResultTest
    {
        [Test]
        public void ConstructorForValueType_WithData_ExpectedValues()
        {
            // Setup
            int data = Random.Next();
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<int>(data, events);

            // Assert
            Assert.True(result.Successful);
            Assert.AreSame(events, result.Events);
            Assert.AreEqual(data, result.Data);
        }

        [Test]
        public void ConstructorForValueType_WithoutData_ExpectedValues()
        {
            // Setup
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<int>(events);

            // Assert
            Assert.IsFalse(result.Successful);
            Assert.AreSame(events, result.Events);
            Assert.AreEqual(0, result.Data);
        }

        [Test]
        public void ConstructorForReferenceType_WithData_ExpectedValues()
        {
            // Setup
            var data = new object();
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<object>(data, events);

            // Assert
            Assert.True(result.Successful);
            Assert.AreSame(events, result.Events);
            Assert.AreSame(data, result.Data);
        }

        [Test]
        public void ConstructorForReferenceType_WithoutData_ExpectedValues()
        {
            // Setup
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<object>(events);

            // Assert
            Assert.IsFalse(result.Successful);
            Assert.AreSame(events, result.Events);
            Assert.IsNull(result.Data);
        }
    }
}
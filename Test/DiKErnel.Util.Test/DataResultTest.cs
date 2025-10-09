// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using System;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Util.Test
{
    [TestFixture]
    internal sealed class DataResultTest
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
            Assert.That(result.Successful, Is.True);
            Assert.That(result.Events, Is.SameAs(events));
            Assert.That(result.Data, Is.EqualTo(data));
        }

        [Test]
        public void ConstructorForValueType_WithoutData_ExpectedValues()
        {
            // Setup
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<int>(events);

            // Assert
            Assert.That(result.Successful, Is.False);
            Assert.That(result.Events, Is.SameAs(events));
            Assert.That(result.Data, Is.EqualTo(0));
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
            Assert.That(result.Successful, Is.True);
            Assert.That(result.Events, Is.SameAs(events));
            Assert.That(result.Data, Is.SameAs(data));
        }

        [Test]
        public void ConstructorForReferenceType_WithoutData_ExpectedValues()
        {
            // Setup
            Event[] events = Array.Empty<Event>();

            // Call
            var result = new DataResult<object>(events);

            // Assert
            Assert.That(result.Successful, Is.False);
            Assert.That(result.Events, Is.SameAs(events));
            Assert.That(result.Data, Is.Null);
        }
    }
}
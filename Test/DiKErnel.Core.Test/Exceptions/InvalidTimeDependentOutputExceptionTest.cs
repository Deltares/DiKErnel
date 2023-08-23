﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using DiKErnel.Core.Exceptions;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test.Exceptions
{
    [TestFixture]
    public class InvalidTimeDependentOutputExceptionTest
    {
        [Test]
        public void ConstructorExpectedValues()
        {
            // Setup
            string propertyName = Random.NextString();

            // Call
            var exception = new InvalidTimeDependentOutputException(propertyName);

            // Assert
            Assert.IsInstanceOf<Exception>(exception);
            Assert.AreEqual($"{propertyName} must be set.", exception.Message);
        }
    }
}
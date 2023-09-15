﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Converters;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test.Data.Generic.Converters
{
    [TestFixture]
    public class JsonInputLocationDataConverterTest
    {
        [Test]
        public void CanWrite_Always_ReturnsFalse()
        {
            // Setup
            var converter = new JsonInputLocationDataConverter();

            // Call
            bool canWrite = converter.CanWrite;

            // Assert
            Assert.IsFalse(canWrite);
        }

        [Test]
        public void WriteJson_Always_ThrowsNotSupportedException()
        {
            // Setup
            var converter = new JsonInputLocationDataConverter();

            // Call
            void Call() => converter.WriteJson(null, null, null);

            // Assert
            Assert.Throws<NotSupportedException>(Call);
        }
    }
}
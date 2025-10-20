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

using System;
using NUnit.Framework;

namespace DiKErnel.TestUtil
{
    public static class AssertHelper
    {
        public static void AssertException<T>(TestDelegate call, string expectedMessage) where T : Exception
        {
            Assert.That(call, Throws.TypeOf<T>().With.Message.EqualTo(expectedMessage));
        }

        public static void AssertInnerException<T>(TestDelegate call, string expectedMessage) where T : Exception
        {
            Assert.That(call, Throws.Exception.With.InnerException.TypeOf<T>().And.InnerException.Message.EqualTo(expectedMessage));
        }
    }
}
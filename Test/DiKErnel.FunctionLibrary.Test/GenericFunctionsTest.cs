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

using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    internal sealed class GenericFunctionsTest
    {
        [Test]
        public void Radians_ValidInput_ExpectedValue()
        {
            // Setup
            const double degrees = 123.45;

            // Call
            double radians = GenericFunctions.Radians(degrees);

            // Assert
            AssertHelper.AreEqual(2.15460896158699, radians);
        }

        [Test]
        public void Degrees_ValidInput_ExpectedValue()
        {
            // Setup
            const double radians = 1.2345;

            // Call 
            double degrees = GenericFunctions.Degrees(radians);

            // Assert
            AssertHelper.AreEqual(70.73163980890012, degrees);
        }
    }
}
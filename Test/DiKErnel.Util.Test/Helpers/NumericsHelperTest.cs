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

using DiKErnel.Util.Helpers;
using NUnit.Framework;

namespace DiKErnel.Util.Test.Helpers
{
    [TestFixture]
    internal sealed class NumericsHelperTest
    {
        private const double tolerance = 1e-16;

        [Test]
        public void AreEqual_EqualValue_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1);

            // Assert
            Assert.That(areEqual, Is.True);
        }

        [Test]
        public void AreEqual_SecondValueDiffersWithTolerance_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1 + tolerance);

            // Assert
            Assert.That(areEqual, Is.True);
        }

        [Test]
        public void AreEqual_FirstValueDiffersWithTolerance_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1 + tolerance, 0.1);

            // Assert
            Assert.That(areEqual, Is.True);
        }

        [Test]
        public void AreEqual_SecondValueDiffersWithTwoTimesTolerance_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1 + tolerance * 2);

            // Assert
            Assert.That(areEqual, Is.False);
        }

        [Test]
        public void AreEqual_FirstValueDiffersWithTwoTimesTolerance_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1 + tolerance * 2, 0.1);

            // Assert
            Assert.That(areEqual, Is.False);
        }

        [Test]
        public void AreEqual_SecondValueLargerThanFirstValue_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.11);

            // Assert
            Assert.That(areEqual, Is.False);
        }

        [Test]
        public void AreEqual_SecondValueSmallerThanFirstValue_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.11, 0.1);

            // Assert
            Assert.That(areEqual, Is.False);
        }

        [Test]
        public void ToString_Always_ReturnsExpectedValue()
        {
            // Call
            var string1 = NumericsHelper.ToString(0.3);
            var string2 = NumericsHelper.ToString(1e-6);
            var string3 = NumericsHelper.ToString(0.001);
            var string4 = NumericsHelper.ToString(1);
            var string5 = NumericsHelper.ToString(0.123456789);

            // Assert
            Assert.That(string1, Is.EqualTo("0.3"));
            Assert.That(string2, Is.EqualTo("1e-06"));
            Assert.That(string3, Is.EqualTo("0.001"));
            Assert.That(string4, Is.EqualTo("1"));
            Assert.That(string5, Is.EqualTo("0.123457"));
        }
    }
}
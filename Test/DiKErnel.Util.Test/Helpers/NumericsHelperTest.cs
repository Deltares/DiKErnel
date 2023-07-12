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

using DiKErnel.Util.Helpers;
using NUnit.Framework;

namespace DiKErnel.Util.Test.Helpers
{
    [TestFixture]
    public class NumericsHelperTest
    {
        private const double maxDeviation = 10E-16;

        [Test]
        public void AreEqual_EqualValue_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1);

            // Assert
            Assert.True(areEqual);
        }

        [Test]
        public void AreEqual_SecondValueDiffersWithEpsilon_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1 + maxDeviation);

            // Assert
            Assert.True(areEqual);
        }

        [Test]
        public void FirstValueDiffersWithEpsilon_ReturnsTrue()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1 + maxDeviation, 0.1);

            // Assert
            Assert.True(areEqual);
        }

        [Test]
        public void AreEqual_SecondValueDiffersWithTwoTimesEpsilon_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.1 + maxDeviation * 2);

            // Assert
            Assert.False(areEqual);
        }

        [Test]
        public void AreEqual_FirstValueDiffersWithTwoTimesEpsilon_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1 + maxDeviation * 2, 0.1);

            // Assert
            Assert.False(areEqual);
        }

        [Test]
        public void AreEqual_SecondValueLargerThanFirstValue_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.1, 0.11);

            // Assert
            Assert.False(areEqual);
        }

        [Test]
        public void AreEqual_SecondValueSmallerThanFirstValue_ReturnsFalse()
        {
            // Call
            bool areEqual = NumericsHelper.AreEqual(0.11, 0.1);

            // Assert
            Assert.False(areEqual);
        }

        [Test]
        public void ToString_Always_ReturnsExpectedValue()
        {
            // Call
            string string1 = NumericsHelper.ToString(0.3);
            string string2 = NumericsHelper.ToString(1e-6);
            string string3 = NumericsHelper.ToString(0.001);
            string string4 = NumericsHelper.ToString(1);

            //Assert
            Assert.AreEqual("0.3", string1);
            Assert.AreEqual("1E-06", string2);
            Assert.AreEqual("0.001", string3);
            Assert.AreEqual("1", string4);
        }
    }
}
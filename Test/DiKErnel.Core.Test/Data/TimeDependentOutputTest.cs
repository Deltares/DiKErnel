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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;
using DiKErnel.TestUtil;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    internal sealed class TimeDependentOutputTest
    {
        [Test]
        public void Constructor_ConstructionPropertiesWithValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();

            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();
            constructionProperties.IncrementDamage = incrementDamage;

            // Call
            var timeDependentOutput = Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            Assert.That(timeDependentOutput.IncrementDamage, Is.EqualTo(incrementDamage));
        }

        [Test]
        public void Constructor_IncrementDamageNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();

            // Call
            void Call() => Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            AssertHelper.AssertInnerException<InvalidTimeDependentOutputException>(Call, "IncrementDamage must be set.");
        }
    }
}
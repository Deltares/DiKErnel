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
using System.Reflection;
using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    public class TimeDependentOutputTest
    {
        [Test]
        public void Constructor_ConstructionPropertiesWithValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();

            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();
            constructionProperties.IncrementDamage = incrementDamage;
            constructionProperties.Damage = damage;
            constructionProperties.TimeOfFailure = timeOfFailure;

            // Call
            var timeDependentOutput = Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            Assert.AreEqual(incrementDamage, timeDependentOutput.IncrementDamage);
            Assert.AreEqual(damage, timeDependentOutput.Damage);
            Assert.AreEqual(timeOfFailure, timeDependentOutput.TimeOfFailure);
        }

        [Test]
        public void Constructor_IncrementDamageNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();
            constructionProperties.Damage = Random.NextDouble();
            constructionProperties.TimeOfFailure = Random.Next();

            // Call
            void Call() => Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            Exception exception = Assert.Throws<TargetInvocationException>(Call)?.InnerException as InvalidTimeDependentOutputException;
            Assert.IsNotNull(exception);
            Assert.AreEqual("IncrementDamage must be set.", exception.Message);
        }

        [Test]
        public void Constructor_DamageNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();
            constructionProperties.IncrementDamage = Random.NextDouble();
            constructionProperties.TimeOfFailure = Random.Next();

            // Call
            void Call() => Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            Exception exception = Assert.Throws<TargetInvocationException>(Call)?.InnerException as InvalidTimeDependentOutputException;
            Assert.IsNotNull(exception);
            Assert.AreEqual("Damage must be set.", exception.Message);
        }

        [Test]
        public void Constructor_TimeOfFailureNull_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();

            var constructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();
            constructionProperties.IncrementDamage = incrementDamage;
            constructionProperties.Damage = damage;

            // Call
            var timeDependentOutput = Substitute.For<TimeDependentOutput>(constructionProperties);

            // Assert
            Assert.AreEqual(incrementDamage, timeDependentOutput.IncrementDamage);
            Assert.AreEqual(damage, timeDependentOutput.Damage);
            Assert.IsNull(timeDependentOutput.TimeOfFailure);
        }
    }
}
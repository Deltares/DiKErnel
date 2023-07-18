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

using DiKErnel.Core.Data;
using DiKErnel.TestUtil;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    public class TimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithTimeOfFailure_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();

            // Call
            var timeDependentOutput = Substitute.For<TimeDependentOutput>(incrementDamage, damage, timeOfFailure);

            // Assert
            Assert.AreEqual(incrementDamage, timeDependentOutput.IncrementDamage);
            Assert.AreEqual(damage, timeDependentOutput.Damage);
            Assert.AreEqual(timeOfFailure, timeDependentOutput.TimeOfFailure);
        }

        [Test]
        public void Constructor_WithoutTimeOfFailure_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();

            // Call
            var timeDependentOutput = Substitute.For<TimeDependentOutput>(incrementDamage, damage, null);

            // Assert
            Assert.AreEqual(incrementDamage, timeDependentOutput.IncrementDamage);
            Assert.AreEqual(damage, timeDependentOutput.Damage);
            Assert.IsNull(timeDependentOutput.TimeOfFailure);
        }
    }
}
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

using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    internal sealed class RevetmentFunctionsTest
    {
        [Test]
        public void IncrementTime_ValidInput_ExpectedValue()
        {
            // Setup
            const double beginTime = 12.3;
            const double endTime = 45.6;

            // Call
            double incrementTime = RevetmentFunctions.IncrementTime(beginTime, endTime);

            // Assert
            AssertHelper.AreEqual(33.3, incrementTime);
        }

        [Test]
        public void AverageNumberOfWaves_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 900;
            const double wavePeriodTm10 = 1.2;
            const double averageNumberOfWavesCtm = 6.5;

            // Call
            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime, wavePeriodTm10,
                                                                                  averageNumberOfWavesCtm);

            // Assert
            AssertHelper.AreEqual(115.38461538461539, averageNumberOfWaves);
        }

        [Test]
        public void Damage_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementDamage = 0.12;
            const double initialDamage = 0.23;

            // Call
            double damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

            // Assert
            AssertHelper.AreEqual(0.35, damage);
        }

        [Test]
        public void FailureRevetment_DamageAndInitialDamageSmallerThanFailureNumber_ExpectedFalse()
        {
            // Setup
            const double initialDamage = 0.1;
            const double damage = 0.2;
            const double failureNumber = 0.3;

            // Call
            bool failureRevetment = RevetmentFunctions.FailureRevetment(damage, initialDamage, failureNumber);

            // Assert
            Assert.That(failureRevetment, Is.False);
        }

        [Test]
        public void FailureRevetment_InitialDamageEqualToFailureNumber_ExpectedFalse()
        {
            // Setup
            const double initialDamage = 0.3;
            const double damage = 0.4;
            const double failureNumber = 0.3;

            // Call
            bool failureRevetment = RevetmentFunctions.FailureRevetment(damage, initialDamage, failureNumber);

            // Assert
            Assert.That(failureRevetment, Is.False);
        }

        [Test]
        public void FailureRevetment_DamageEqualToFailureNumber_ExpectedTrue()
        {
            // Setup
            const double initialDamage = 0.2;
            const double damage = 0.3;
            const double failureNumber = 0.3;

            // Call
            bool failureRevetment = RevetmentFunctions.FailureRevetment(damage, initialDamage, failureNumber);

            // Assert
            Assert.That(failureRevetment, Is.True);
        }

        [Test]
        public void FailureRevetment_DamageLargerAndInitialDamageSmallerThanFailureNumber_ExpectedTrue()
        {
            // Setup
            const double initialDamage = 0.2;
            const double damage = 0.4;
            const double failureNumber = 0.3;

            // Call
            bool failureRevetment = RevetmentFunctions.FailureRevetment(damage, initialDamage, failureNumber);

            // Assert
            Assert.That(failureRevetment, Is.True);
        }

        [Test]
        public void FailureRevetment_DamageAndInitialDamageLargerThanFailureNumber_ExpectedFalse()
        {
            // Setup
            const double initialDamage = 0.4;
            const double damage = 0.5;
            const double failureNumber = 0.3;

            // Call
            bool failureRevetment = RevetmentFunctions.FailureRevetment(damage, initialDamage, failureNumber);

            // Assert
            Assert.That(failureRevetment, Is.False);
        }

        [Test]
        public void DurationInTimeStepFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 550;
            const double incrementDamage = 0.234;
            const double failureNumber = 1;
            const double initialDamage = 0.836;

            // Call
            double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(incrementTime, incrementDamage,
                                                                                            failureNumber, initialDamage);

            // Assert
            AssertHelper.AreEqual(385.47008547008551, durationInTimeStepFailure);
        }

        [Test]
        public void TimeOfFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double durationInTimeStepFailure = 12.3;
            const double beginTime = 45.6;

            // Call
            double timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure, beginTime);

            // Assert
            AssertHelper.AreEqual(57.9, timeOfFailure);
        }
    }
}
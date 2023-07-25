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

using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    public class RevetmentFunctionsTest
    {
        [Test]
        public void IncrementTime_ValidInput_ExpectedValue()
        {
            // Setup
            const int beginTime = 1200;
            const int endTime = 1500;

            // Call
            double incrementTime = RevetmentFunctions.IncrementTime(beginTime, endTime);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(300, incrementTime);
        }

        [Test]
        public void AverageNumberOfWaves_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 900.0;
            const double wavePeriodTm10 = 1.2;
            const double averageNumberOfWavesCtm = 6.5;

            // Call
            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime, wavePeriodTm10,
                                                                                  averageNumberOfWavesCtm);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(115.38461538461539, averageNumberOfWaves);
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
            AssertHelper.AssertAreEqualWithinTolerance(0.35, damage);
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
            Assert.IsFalse(failureRevetment);
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
            Assert.IsFalse(failureRevetment);
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
            Assert.IsTrue(failureRevetment);
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
            Assert.IsTrue(failureRevetment);
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
            Assert.IsFalse(failureRevetment);
        }

        [Test]
        public void TimeOfFailure_ValidUnroundedInput_ExpectedValue()
        {
            // Setup
            const double durationInTimeStepFailure = 254.001;
            const double beginTime = 1568;

            // Call
            double timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure, beginTime);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(1823, timeOfFailure);
        }

        [Test]
        public void DurationInTimeStepFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 550.0;
            const double incrementDamage = 0.234;
            const double failureNumber = 1.0;
            const double initialDamage = 0.836;

            // Call
            double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(incrementTime, incrementDamage,
                                                                                            failureNumber, initialDamage);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(385.47008547008551, durationInTimeStepFailure);
        }

        [Test]
        public void TimeOfFailure_ValidRoundedInput_ExpectedValue()
        {
            // Setup
            const double durationInTimeStepFailure = 254.0;
            const double beginTime = 1568.0;

            // Call
            int timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure, beginTime);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(1822, timeOfFailure);
        }
    }
}
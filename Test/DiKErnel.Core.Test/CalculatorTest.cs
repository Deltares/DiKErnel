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
using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Util;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    public class CalculatorTest
    {
        [Test]
        public void GivenCalculator_WhenWaitForCompletion_ThenCalculationPerformed()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            // When
            calculator.WaitForCompletion();

            // Then
            Assert.AreEqual(CalculationState.FinishedSuccessfully, calculator.CalculationState);
            Assert.AreEqual(100, calculator.Progress);
        }

        [Test]
        [TestCase(true)]
        [TestCase(false)]
        public void GivenCalculator_WhenCalculationPerformed_ThenReturnsResultWithExpectedOutput(bool withTimeOfFailure)
        {
            // Given
            double damage = Random.NextDouble();
            int? timeOfFailure = withTimeOfFailure ? Random.Next() : (int?) null;

            ICalculationInput calculationInput = CreateCalculationInput(damage, timeOfFailure);

            var calculator = new Calculator(calculationInput);

            // When
            calculator.WaitForCompletion();

            // Then
            Assert.IsNotNull(calculator.Result);

            CalculationOutput output = calculator.Result.Data;
            Assert.AreEqual(1, output.LocationDependentOutputItems.Count);

            LocationDependentOutput locationDependentOutput = output.LocationDependentOutputItems.ElementAt(0);
            IEnumerable<double> damages = locationDependentOutput.GetDamages().ToArray();
            Assert.AreEqual(3, damages.Count());
            Assert.IsTrue(damages.All(d => d.Equals(damage)));
            Assert.AreEqual(timeOfFailure, locationDependentOutput.GetTimeOfFailure());
        }

        [Test]
        public void GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            // When
            calculator.Cancel();
            calculator.WaitForCompletion();

            // Then
            Assert.AreEqual(CalculationState.Cancelled, calculator.CalculationState);
            Assert.AreNotEqual(100, calculator.Progress);
        }

        [Test]
        public void GivenCalculatorWithFinishedCalculation_WhenCancelCalled_ThenCalculationNotCancelled()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            calculator.WaitForCompletion();

            // When
            calculator.Cancel();

            // Then
            Assert.AreEqual(CalculationState.FinishedSuccessfully, calculator.CalculationState);
            Assert.AreEqual(100, calculator.Progress);
        }

        [Test]
        public void GivenCalculatorWithRunningCalculation_WhenGetCalculationState_ThenReturnsExpectedResult()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            // When
            CalculationState calculationState = calculator.CalculationState;

            // Then
            Assert.AreEqual(CalculationState.Running, calculationState);

            calculator.WaitForCompletion();
        }

        [Test]
        public void GivenCalculatorWithRunningCalculation_WhenGetResult_ThenReturnsNull()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            // When
            DataResult<CalculationOutput> result = calculator.Result;

            // Then
            Assert.IsNull(result);

            calculator.WaitForCompletion();
        }

        [Test]
        public void GivenCalculatorWithCancelledCalculation_WhenGetCalculationState_ThenExpectedResult()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            calculator.Cancel();
            calculator.WaitForCompletion();

            // When
            CalculationState calculationState = calculator.CalculationState;

            // Then
            Assert.AreEqual(CalculationState.Cancelled, calculationState);
        }

        [Test]
        public void GivenCalculatorWithCancelledCalculation_WhenGetResult_ThenReturnsResultWithSuccessfulFalse()
        {
            // Given
            var calculator = new Calculator(CreateCalculationInput());

            calculator.Cancel();
            calculator.WaitForCompletion();

            // When
            DataResult<CalculationOutput> result = calculator.Result;

            // Then
            Assert.IsFalse(result.Successful);
        }

        [Test]
        public void GivenCalculatorWithExceptionDuringCalculation_WhenGetCalculationState_ThenExpectedResult()
        {
            // Given
            ICalculationInput calculationInput = CreateCalculationInput();

            ILocationDependentInput locationDependentInput = calculationInput.LocationDependentInputItems[1];
            ((TestLocationDependentCalculationInput) locationDependentInput).ExceptionMessage = Random.NextString();

            var calculator = new Calculator(calculationInput);

            calculator.WaitForCompletion();

            // When
            CalculationState calculationState = calculator.CalculationState;

            // Then
            Assert.AreEqual(CalculationState.FinishedInError, calculationState);
        }

        [Test]
        public void GivenCalculatorWithExceptionDuringCalculation_WhenGetResult_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            ICalculationInput calculationInput = CreateCalculationInput();

            string exceptionMessage = Random.NextString();
            ILocationDependentInput locationDependentInput = calculationInput.LocationDependentInputItems[1];
            ((TestLocationDependentCalculationInput) locationDependentInput).ExceptionMessage = exceptionMessage;

            var calculator = new Calculator(calculationInput);

            calculator.WaitForCompletion();

            // When
            DataResult<CalculationOutput> result = calculator.Result;

            // Then
            Assert.IsFalse(result.Successful);
            Assert.AreEqual(1, result.Events.Count());

            Event exceptionEvent = result.Events.ElementAt(0);
            Assert.AreEqual(EventType.Error, exceptionEvent.Type);
            Assert.AreEqual("An unhandled error occurred while performing the calculation. See stack trace for more " +
                            $"information:\n{exceptionMessage}", exceptionEvent.Message);
        }

        private static ICalculationInput CreateCalculationInput(double damage = 0, int? timeOfFailure = null)
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput(damage, timeOfFailure),
            });

            calculationInput.TimeDependentInputItems.Returns(new[]
            {
                Substitute.For<ITimeDependentInput>(),
                Substitute.For<ITimeDependentInput>(),
                Substitute.For<ITimeDependentInput>()
            });

            return calculationInput;
        }

        private sealed class TestLocationDependentCalculationInput : ILocationDependentInput
        {
            private readonly double damage;
            private readonly int? timeOfFailure;

            public TestLocationDependentCalculationInput(double damage, int? timeOfFailure = null)
            {
                this.damage = damage;
                this.timeOfFailure = timeOfFailure;
            }

            public string ExceptionMessage { get; set; }

            public double X => 0;

            public double Z => 0;

            public double InitialDamage => 0;

            public double FailureNumber => 1;

            public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData)
            {
                return true;
            }

            public TimeDependentOutput Calculate(double initialDamage, ITimeDependentInput timeDependentInput, IProfileData profileData)
            {
                if (!string.IsNullOrEmpty(ExceptionMessage))
                {
                    throw new InvalidOperationException(ExceptionMessage);
                }

                return Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage, timeOfFailure);
            }

            public LocationDependentOutput GetLocationDependentOutput(IEnumerable<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(timeDependentOutputItems);
            }
        }
    }
}
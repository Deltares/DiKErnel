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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    public class CalculatorTest
    {
        private readonly double damageOfFirstLocation = Random.NextDouble();
        private readonly double timeOfFailureOfFirstLocation = Random.NextDouble();
        private readonly double damageOfSecondLocation = Random.NextDouble();

        [TestFixture]
        public class GivenValidCalculationInput : CalculatorTest
        {
            private ICalculationInput calculationInput;

            [SetUp]
            public virtual void Arrange()
            {
                calculationInput = CreateCalculationInput();
            }

            [Test]
            public void WhenCalculate_ThenReturnsSuccessResultWithExpectedCalculationOutput()
            {
                // When
                ICalculationResult result = Calculator.Calculate(calculationInput);

                // Then
                Assert.That(result, Is.InstanceOf<SuccessResult>());

                CalculationOutput output = ((SuccessResult) result).CalculationOutput;
                Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(2));

                LocationDependentOutput locationDependentOutput = output.LocationDependentOutputItems[0];
                IReadOnlyList<double> damages = locationDependentOutput.GetDamages();
                Assert.That(damages, Has.Count.EqualTo(3));
                Assert.That(damages.All(d => d.Equals(damageOfFirstLocation)), Is.True);
                Assert.That(locationDependentOutput.GetTimeOfFailure(), Is.EqualTo(timeOfFailureOfFirstLocation));

                locationDependentOutput = output.LocationDependentOutputItems[1];
                damages = locationDependentOutput.GetDamages();
                Assert.That(damages, Has.Count.EqualTo(3));
                Assert.That(damages.All(d => d.Equals(damageOfSecondLocation)), Is.True);
                Assert.That(locationDependentOutput.GetTimeOfFailure(), Is.Null);
            }

            [Test]
            public void GivenLogHandler_WhenCalculate_ThenExpectedMessagesLogged()
            {
                // Given
                var logHandler = Substitute.For<ILogHandler>();
                var calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler
                };

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
            }

            [Test]
            public void GivenProgressHandler_WhenCalculate_ThenExpectedProgressReported()
            {
                // Given
                var progressHandler = Substitute.For<IProgress<int>>();
                var calculatorSettings = new CalculatorSettings
                {
                    ProgressHandler = progressHandler
                };

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(7));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(17);
                    progressHandler.Report(33);
                    progressHandler.Report(50);
                    progressHandler.Report(67);
                    progressHandler.Report(83);
                    progressHandler.Report(100);
                });
            }
        }

        [TestFixture]
        public class GivenInvalidCalculationInput : CalculatorTest
        {
            private ICalculationInput calculationInput;
            private string exceptionMessageForSecondLocation;

            [SetUp]
            public void Arrange()
            {
                exceptionMessageForSecondLocation = Random.NextString();

                calculationInput = CreateCalculationInput(exceptionMessageForSecondLocation);
            }

            [Test]
            public void WhenCalculate_ThenReturnsFailureResult()
            {
                // When
                ICalculationResult result = Calculator.Calculate(calculationInput);

                // Then
                Assert.That(result, Is.InstanceOf<FailureResult>());
            }
        }

        private ICalculationInput CreateCalculationInput(string exceptionMessageForSecondLocation = null)
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput(damageOfFirstLocation, timeOfFailureOfFirstLocation),
                new TestLocationDependentCalculationInput(damageOfSecondLocation, null, exceptionMessageForSecondLocation)
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
            private readonly double? timeOfFailure;
            private readonly string exceptionMessage;

            public TestLocationDependentCalculationInput(double damage, double? timeOfFailure = null, string exceptionMessage = null)
            {
                this.damage = damage;
                this.timeOfFailure = timeOfFailure;
                this.exceptionMessage = exceptionMessage;
            }

            public double X => 0;

            public double Z => 0;

            public double InitialDamage => 0;

            public double FailureNumber => 1;

            public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData)
            {
                return true;
            }

            public TimeDependentOutput Calculate(double initialDamage, ITimeDependentInput timeDependentInput,
                                                 IProfileData profileData)
            {
                if (!string.IsNullOrEmpty(exceptionMessage))
                {
                    throw new InvalidOperationException(exceptionMessage);
                }

                Thread.Sleep(10);

                var timeDependentOutputConstructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();

                timeDependentOutputConstructionProperties.IncrementDamage = Random.NextDouble();
                timeDependentOutputConstructionProperties.Damage = damage;
                timeDependentOutputConstructionProperties.TimeOfFailure = timeOfFailure;

                return Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties);
            }

            public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(timeDependentOutputItems);
            }
        }
    }
}
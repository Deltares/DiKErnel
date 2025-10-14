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
using DiKErnel.Core.Data;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    internal class CalculatorTest
    {
        [TestFixture]
        internal class GivenValidCalculationInput : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;

            [SetUp]
            public void Arrange()
            {
                calculationInput = CreateCalculationInput();
                logHandler = Substitute.For<ILogHandler>();
                progressHandler = Substitute.For<IProgress<int>>();
                calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler,
                    ProgressHandler = progressHandler
                };
            }

            [Test, Combinatorial]
            public void
                GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenReturnsSuccessResultWithExpectedCalculationOutput(
                    [Values(false, true)] bool calculateLocationsInParallel,
                    [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                ICalculationResult result = Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(result, Is.InstanceOf<SuccessResult>());

                CalculationOutput output = ((SuccessResult) result).CalculationOutput;
                Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(2));
                Assert.That(output.LocationDependentOutputItems[0].TimeDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[1].TimeDependentOutputItems, Has.Count.EqualTo(3));
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenLogsExpectedMessages(
                [Values(false, true)] bool calculateLocationsInParallel,
                [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
            }

            [Test]
            public void GivenCalculatorSettingsWithoutParallelization_WhenCalculate_ThenReportsExpectedProgress()
            {
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

            [Test]
            public void GivenCalculatorSettingsWithParallelizationForLocations_WhenCalculate_ThenReportsExpectedProgress()
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = true;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(2));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(100);
                });
            }

            [Test]
            public void GivenCalculatorSettingsWithParallelizationForTimeSteps_WhenCalculate_ThenReportsExpectedProgress()
            {
                // Given
                calculatorSettings.CalculateTimeStepsInParallel = true;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(3));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(50);
                    progressHandler.Report(100);
                });
            }
        }

        [TestFixture]
        internal class GivenValidCalculationInputAndCancelCondition : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;

            [SetUp]
            public void Arrange()
            {
                calculationInput = CreateCalculationInput();

                var secondLocation = (TestLocationDependentCalculationInput) calculationInput.LocationDependentInputItems[1];

                logHandler = Substitute.For<ILogHandler>();
                progressHandler = Substitute.For<IProgress<int>>();
                calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler,
                    ProgressHandler = progressHandler,
                    ShouldCancel = () => secondLocation.NumberOfPerformedTimeSteps == 1
                };
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenReturnsCancellationResult(
                [Values(false, true)] bool calculateLocationsInParallel,
                [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                ICalculationResult result = Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(result, Is.InstanceOf<CancellationResult>());
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenLogsExpectedMessages(
                [Values(false, true)] bool calculateLocationsInParallel,
                [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
            }

            [Test]
            public void GivenCalculatorSettingsWithoutParallelization_WhenCalculate_ThenReportsExpectedProgress()
            {
                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(5));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(17);
                    progressHandler.Report(33);
                    progressHandler.Report(50);
                    progressHandler.Report(67);
                });
            }

            [Test]
            public void GivenCalculatorSettingsWithParallelizationForLocations_WhenCalculate_ThenReportsExpectedProgress()
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = true;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(1));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                });
            }

            [Test]
            public void GivenCalculatorSettingsWithParallelizationForTimeSteps_WhenCalculate_ThenReportsExpectedProgress()
            {
                // Given
                calculatorSettings.CalculateTimeStepsInParallel = true;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(2));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(50);
                });
            }
        }

        [TestFixture]
        internal class GivenInvalidCalculationInput : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;
            private string exceptionMessageForSecondLocation;

            [SetUp]
            public virtual void Arrange()
            {
                exceptionMessageForSecondLocation = Random.NextString();
                calculationInput = CreateCalculationInput(exceptionMessageForSecondLocation);
                logHandler = Substitute.For<ILogHandler>();
                progressHandler = Substitute.For<IProgress<int>>();
                calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler,
                    ProgressHandler = progressHandler
                };
            }

            [TestFixture]
            internal sealed class WhenCalculate : GivenInvalidCalculationInput
            {
                private ICalculationResult result;

                [Test]
                public void ThenReturnsFailureResult()
                {
                    Assert.That(result, Is.InstanceOf<FailureResult>());
                }

                [Test]
                public void ThenLogsExpectedMessages()
                {
                    Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(1));

                    Received.InOrder(() =>
                    {
                        logHandler.LogError(Arg.Is<string>(s => s.Equals("An unhandled error occurred while performing the calculation. " +
                                                                         $"See stack trace for more information:{Environment.NewLine}" +
                                                                         $"{exceptionMessageForSecondLocation}",
                                                                         StringComparison.Ordinal)));
                    });
                }

                [Test]
                public void ThenReportsExpectedProgress()
                {
                    Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(4));

                    Received.InOrder(() =>
                    {
                        progressHandler.Report(0);
                        progressHandler.Report(17);
                        progressHandler.Report(33);
                        progressHandler.Report(50);
                    });
                }

                public override void Arrange()
                {
                    base.Arrange();

                    result = Calculator.Calculate(calculationInput, calculatorSettings);
                }
            }
        }

        private static ICalculationInput CreateCalculationInput(string exceptionMessageForSecondLocation = null)
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput(),
                new TestLocationDependentCalculationInput(exceptionMessageForSecondLocation)
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
            private readonly string exceptionMessage;

            public TestLocationDependentCalculationInput(string exceptionMessage = null)
            {
                this.exceptionMessage = exceptionMessage;
            }

            public int NumberOfPerformedTimeSteps { get; private set; }

            public double X => 0;

            public double Z => 0;

            public double InitialDamage => 0;

            public double FailureNumber => 1;

            public bool CalculateIsStateful => false;

            public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData)
            {
                return true;
            }

            public void Initialize(IProfileData profileData) {}

            public TimeDependentOutput Calculate(ITimeDependentInput timeDependentInput, IProfileData profileData)
            {
                if (!string.IsNullOrEmpty(exceptionMessage))
                {
                    throw new InvalidOperationException(exceptionMessage);
                }

                var timeDependentOutputConstructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();

                timeDependentOutputConstructionProperties.IncrementDamage = Random.NextDouble();

                NumberOfPerformedTimeSteps++;

                return Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties);
            }

            public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(timeDependentOutputItems);
            }
        }
    }
}
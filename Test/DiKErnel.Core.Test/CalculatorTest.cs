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
        internal sealed class GivenValidCalculationInput : CalculatorTest
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
                Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[0].TimeDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[1].TimeDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[2].TimeDependentOutputItems, Has.Count.EqualTo(3));
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenLogsNoMessages(
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
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(10));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(11);
                    progressHandler.Report(22);
                    progressHandler.Report(33);
                    progressHandler.Report(44);
                    progressHandler.Report(56);
                    progressHandler.Report(67);
                    progressHandler.Report(78);
                    progressHandler.Report(89);
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
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(4));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(33);
                    progressHandler.Report(67);
                    progressHandler.Report(100);
                });
            }
        }

        [TestFixture]
        internal sealed class GivenValidCalculationInputAndCancelCondition : CalculatorTest
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
                    ShouldCancel = () => secondLocation.NumberOfPerformedTimeSteps >= 1
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
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenLogsNoMessages(
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
                    progressHandler.Report(11);
                    progressHandler.Report(22);
                    progressHandler.Report(33);
                    progressHandler.Report(44);
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
                    progressHandler.Report(33);
                });
            }
        }

        [TestFixture]
        internal sealed class GivenValidCalculationInputWithStatefulLocation : CalculatorTest
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

                secondLocation.CalculateIsStateful = true;

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
                Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[0].TimeDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[1].TimeDependentOutputItems, Has.Count.EqualTo(3));
                Assert.That(output.LocationDependentOutputItems[2].TimeDependentOutputItems, Has.Count.EqualTo(3));
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithoutParallelizationForTimeSteps_WhenCalculate_ThenLogsNoMessages(
                [Values(false, true)] bool calculateLocationsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithParallelizationForTimeSteps_WhenCalculate_ThenLogsExpectedMessage(
                [Values(false, true)] bool calculateLocationsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = true;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(1));

                Received.InOrder(() =>
                {
                    logHandler.LogWarning(Arg.Is<string>(s => s.Equals("The calculation is configured to run time steps in parallel but " +
                                                                       "for on or more locations this is not possible; the output of " +
                                                                       "previous time steps is used as input for the next time step, so " +
                                                                       "these calculations are forced to be performed chronologically.",
                                                                       StringComparison.Ordinal)));
                });
            }

            [Test]
            public void GivenCalculatorSettingsWithoutParallelization_WhenCalculate_ThenReportsExpectedProgress()
            {
                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(10));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(11);
                    progressHandler.Report(22);
                    progressHandler.Report(33);
                    progressHandler.Report(44);
                    progressHandler.Report(56);
                    progressHandler.Report(67);
                    progressHandler.Report(78);
                    progressHandler.Report(89);
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
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(6));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(33);
                    progressHandler.Report(44);
                    progressHandler.Report(56);
                    progressHandler.Report(67);
                    progressHandler.Report(100);
                });
            }
        }

        [TestFixture]
        internal sealed class GivenValidCalculationInputWithManyTimeSteps : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;

            [SetUp]
            public void Arrange()
            {
                calculationInput = CreateCalculationInput(10000);
                logHandler = Substitute.For<ILogHandler>();
                progressHandler = Substitute.For<IProgress<int>>();
                calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler,
                    ProgressHandler = progressHandler
                };
            }

            [Test]
            public void GivenCalculatorSettingsWithoutParallelization_WhenCalculate_ThenReportsExpectedProgress()
            {
                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(101));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(1);
                    progressHandler.Report(2);
                    progressHandler.Report(3);
                    progressHandler.Report(4);
                    progressHandler.Report(5);
                    progressHandler.Report(95);
                    progressHandler.Report(96);
                    progressHandler.Report(97);
                    progressHandler.Report(98);
                    progressHandler.Report(99);
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
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(4));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(33);
                    progressHandler.Report(67);
                    progressHandler.Report(100);
                });
            }
        }

        [TestFixture]
        internal sealed class GivenInvalidCalculationInput : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;
            private string exceptionMessageForSecondLocation;

            [SetUp]
            public void Arrange()
            {
                calculationInput = CreateCalculationInput();

                var secondLocation = (TestLocationDependentCalculationInput) calculationInput.LocationDependentInputItems[1];

                exceptionMessageForSecondLocation = Random.NextString();
                secondLocation.SetExceptionMessage(exceptionMessageForSecondLocation);

                logHandler = Substitute.For<ILogHandler>();
                progressHandler = Substitute.For<IProgress<int>>();
                calculatorSettings = new CalculatorSettings
                {
                    LogHandler = logHandler,
                    ProgressHandler = progressHandler
                };
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenReturnsFailureResult(
                [Values(false, true)] bool calculateLocationsInParallel,
                [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                ICalculationResult result = Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(result, Is.InstanceOf<FailureResult>());
            }

            [Test, Combinatorial]
            public void GivenCalculatorSettingsWithAnyParallelizationConfiguration_WhenCalculate_ThenLogsExpectedMessage(
                [Values(false, true)] bool calculateLocationsInParallel,
                [Values(false, true)] bool calculateTimeStepsInParallel)
            {
                // Given
                calculatorSettings.CalculateLocationsInParallel = calculateLocationsInParallel;
                calculatorSettings.CalculateTimeStepsInParallel = calculateTimeStepsInParallel;

                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(1));

                Received.InOrder(() =>
                {
                    logHandler.LogError(Arg.Is<string>(s => s.Contains("An unhandled error occurred while performing the calculation. " +
                                                                       $"See stack trace for more information:{Environment.NewLine}",
                                                                       StringComparison.Ordinal)
                                                            && s.Contains(exceptionMessageForSecondLocation, StringComparison.Ordinal)));
                });
            }

            [Test]
            public void GivenCalculatorSettingsWithoutParallelization_WhenCalculate_ThenReportsExpectedProgress()
            {
                // When
                Calculator.Calculate(calculationInput, calculatorSettings);

                // Then
                Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(4));

                Received.InOrder(() =>
                {
                    progressHandler.Report(0);
                    progressHandler.Report(11);
                    progressHandler.Report(22);
                    progressHandler.Report(33);
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
                    progressHandler.Report(33);
                });
            }
        }

        private static ICalculationInput CreateCalculationInput(int numberOfTimeSteps = 3)
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput(),
                new TestLocationDependentCalculationInput(),
                new TestLocationDependentCalculationInput()
            });

            var timeDependentInputs = new List<ITimeDependentInput>();

            for (var i = 0; i < numberOfTimeSteps; i++)
            {
                timeDependentInputs.Add(Substitute.For<ITimeDependentInput>());
            }

            calculationInput.TimeDependentInputItems.Returns(timeDependentInputs);

            return calculationInput;
        }

        private sealed class TestLocationDependentCalculationInput : ILocationDependentInput
        {
            private string exceptionMessage;

            public int NumberOfPerformedTimeSteps { get; private set; }

            public double X => Random.NextDouble();

            public double Z => Random.NextDouble();

            public double InitialDamage => Random.NextDouble();

            public double FailureNumber => Random.NextDouble();

            public bool CalculateIsStateful { get; set; }

            public void SetExceptionMessage(string message)
            {
                exceptionMessage = message;
            }

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

            public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                                      IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(InitialDamage, FailureNumber, timeDependentInputItems,
                                                               timeDependentOutputItems);
            }
        }
    }
}
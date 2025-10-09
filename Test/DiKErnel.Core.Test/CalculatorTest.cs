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
    internal class CalculatorTest
    {
        private readonly double damageOfFirstLocation = Random.NextDouble();
        private readonly double timeOfFailureOfFirstLocation = Random.NextDouble();
        private readonly double damageOfSecondLocation = Random.NextDouble();

        [TestFixture]
        internal class GivenValidCalculationInput : CalculatorTest
        {
            private ILogHandler logHandler;
            private IProgress<int> progressHandler;
            private ICalculationInput calculationInput;
            private CalculatorSettings calculatorSettings;

            [SetUp]
            public virtual void Arrange()
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

            [TestFixture]
            internal sealed class WhenCalculate : GivenValidCalculationInput
            {
                private ICalculationResult result;

                [Test]
                public void ThenReturnsSuccessResultWithExpectedCalculationOutput()
                {
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
                public void ThenLogsExpectedMessages()
                {
                    Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
                }

                [Test]
                public void ThenReportsExpectedProgress()
                {
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

                public override void Arrange()
                {
                    base.Arrange();

                    result = Calculator.Calculate(calculationInput, calculatorSettings);
                }
            }

            [TestFixture]
            internal sealed class WhenCalculateWithCancel : GivenValidCalculationInput
            {
                private ICalculationResult result;

                [Test]
                public void ThenReturnsCancellationResult()
                {
                    Assert.That(result, Is.InstanceOf<CancellationResult>());
                }

                [Test]
                public void ThenLogsExpectedMessages()
                {
                    Assert.That(logHandler.ReceivedCalls().Count(), Is.EqualTo(0));
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

                    calculatorSettings.ShouldCancel = () => progressHandler.ReceivedCalls().Count() == 4;

                    result = Calculator.Calculate(calculationInput, calculatorSettings);
                }
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
                        logHandler.Error(Arg.Is<string>(s => s.Equals("An unhandled error occurred while performing the calculation. See " +
                                                                      $"stack trace for more information:{Environment.NewLine}" +
                                                                      $"{exceptionMessageForSecondLocation}", StringComparison.Ordinal)));
                    });
                }

                [Test]
                public void ThenReportsExpectedProgress()
                {
                    Assert.That(progressHandler.ReceivedCalls().Count(), Is.EqualTo(2));

                    Received.InOrder(() =>
                    {
                        progressHandler.Report(0);
                        progressHandler.Report(17);
                    });
                }

                public override void Arrange()
                {
                    base.Arrange();

                    result = Calculator.Calculate(calculationInput, calculatorSettings);
                }
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

                return Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties);
            }

            public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(timeDependentOutputItems);
            }
        }
    }
}
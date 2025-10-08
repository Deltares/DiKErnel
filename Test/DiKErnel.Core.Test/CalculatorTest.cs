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
        [Test]
        public void GivenCalculator_WhenCalculate_ThenCalculationPerformed()
        {
            // Given
            var progressHandler = Substitute.For<IProgress<int>>();
            var calculator = new Calculator(new CalculatorSettings
            {
                ProgressHandler = progressHandler
            });
            ICalculationInput calculationInput = CreateCalculationInput();

            // When
            calculator.Calculate(calculationInput);

            // Then
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
        [TestCase(true)]
        [TestCase(false)]
        public void GivenCalculator_WhenCalculate_ThenReturnsSuccessResultWithExpectedOutput(bool withTimeOfFailure)
        {
            // Given
            double damage = Random.NextDouble();
            double? timeOfFailure = withTimeOfFailure ? Random.NextDouble() : (double?) null;

            ICalculationInput calculationInput = CreateCalculationInput(damage, timeOfFailure);

            var calculator = new Calculator();

            // When
            ICalculationResult result = calculator.Calculate(calculationInput);

            // Then
            Assert.That(result, Is.InstanceOf<SuccessResult>());

            CalculationOutput output = ((SuccessResult) result).CalculationOutput;
            Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(2));

            LocationDependentOutput locationDependentOutput = output.LocationDependentOutputItems[0];
            IReadOnlyList<double> damages = locationDependentOutput.GetDamages();
            Assert.That(damages, Has.Count.EqualTo(3));
            Assert.That(damages.All(d => d.Equals(damage)), Is.True);
            Assert.That(locationDependentOutput.GetTimeOfFailure(), Is.EqualTo(timeOfFailure));
        }

        [Test]
        public void GivenCalculator_WhenCalculateWithException_ThenLogsErrorMessageAndReturnsFailureResult()
        {
            // Given
            ICalculationInput calculationInput = CreateCalculationInput();

            string exceptionMessage = Random.NextString();
            ILocationDependentInput locationDependentInput = calculationInput.LocationDependentInputItems[0];
            ((TestLocationDependentCalculationInput) locationDependentInput).ExceptionMessage = exceptionMessage;

            var logHandler = Substitute.For<ILogHandler>();

            var calculator = new Calculator(new CalculatorSettings
            {
                LogHandler = logHandler
            });

            // When
            ICalculationResult result = calculator.Calculate(calculationInput);

            // Then
            Received.InOrder(() =>
            {
                logHandler.Error(Arg.Is<string>(s => s.Equals("An unhandled error occurred while performing the " +
                                                              "calculation. See stack trace for more information:" +
                                                              $"{Environment.NewLine}{exceptionMessage}")));
            });

            Assert.That(result, Is.InstanceOf<FailureResult>());
        }

        private static ICalculationInput CreateCalculationInput(double damage = 0, double? timeOfFailure = null)
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput(damage, timeOfFailure),
                new TestLocationDependentCalculationInput(damage, timeOfFailure)
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

            public TestLocationDependentCalculationInput(double damage, double? timeOfFailure = null)
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

            public TimeDependentOutput Calculate(double initialDamage, ITimeDependentInput timeDependentInput,
                                                 IProfileData profileData)
            {
                if (!string.IsNullOrEmpty(ExceptionMessage))
                {
                    throw new InvalidOperationException(ExceptionMessage);
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
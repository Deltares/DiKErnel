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
using System.Threading;
using DiKErnel.Core.Data;
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
        public void GivenCalculationInput_WhenCalculationPerformedSuccessfully_ThenReturnsResultWithExpectedOutput()
        {
            // Given
            ICalculationInput calculationInput = CreateCalculationInput();

            // When
            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput);

            // Then
            Assert.That(result, Is.Not.Null);
            Assert.That(result.Successful, Is.True);
            Assert.That(result.Events, Has.Count.EqualTo(0));

            Assert.That(result.Data, Is.Not.Null);

            CalculationOutput output = result.Data;
            Assert.That(output.LocationDependentOutputItems, Has.Count.EqualTo(1));
        }

        [Test]
        public void GivenCalculationInput_WhenExceptionDuringCalculation_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            ICalculationInput calculationInput = CreateCalculationInput();

            string exceptionMessage = Random.NextString();
            ILocationDependentInput locationDependentInput = calculationInput.LocationDependentInputItems[0];
            ((TestLocationDependentCalculationInput) locationDependentInput).ExceptionMessage = exceptionMessage;

            // When
            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput, CalculationMode.Sequential, CalculationMode.Sequential);

            // Then
            Assert.That(result, Is.Not.Null);
            Assert.That(result.Successful, Is.False);
            Assert.That(result.Data, Is.Null);

            Assert.That(result.Events, Has.Count.EqualTo(1));

            Event exceptionEvent = result.Events[0];
            Assert.That(exceptionEvent.Type, Is.EqualTo(EventType.Error));
            Assert.That(exceptionEvent.Message, Is.EqualTo("An unhandled error occurred while performing the " +
                                                           "calculation. See stack trace for more information:" +
                                                           $"{Environment.NewLine}{exceptionMessage}"));
        }

        private static ICalculationInput CreateCalculationInput()
        {
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                new TestLocationDependentCalculationInput()
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
            public string ExceptionMessage { get; set; }

            public double X => 0;

            public double Z => 0;

            public double InitialDamage => 0;

            public double FailureNumber => 1;

            public bool RequiresDamageAtStartOfCalculation => false;

            public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData)
            {
                return true;
            }

            public void InitializeDerivedLocationDependentInput(IProfileData profileData) {}

            public TimeDependentOutput Calculate(ITimeDependentInput timeDependentInput, IProfileData profileData,
                                                 double damageAtStartOfCalculation = double.NaN)
            {
                if (!string.IsNullOrEmpty(ExceptionMessage))
                {
                    throw new InvalidOperationException(ExceptionMessage);
                }

                Thread.Sleep(10);

                var timeDependentOutputConstructionProperties = Substitute.For<TimeDependentOutputConstructionProperties>();

                timeDependentOutputConstructionProperties.IncrementDamage = Random.NextDouble();

                return Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties);
            }

            public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
            {
                return Substitute.For<LocationDependentOutput>(timeDependentOutputItems);
            }
        }
    }
}
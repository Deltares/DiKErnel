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
using DiKErnel.Util;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    public class ValidatorTest
    {
        [Test, Combinatorial]
        public void Validate_ValidOrInvalidData_ReturnsExpectedResult([Values(true, false)] bool profileDataValid,
                                                                      [Values(true, false)] bool locationDependentInputValid,
                                                                      [Values(true, false)] bool timeDependentInputValid)
        {
            // Setup
            var profileData = Substitute.For<IProfileData>();
            profileData.Validate()
                       .Returns(profileDataValid)
                       .AndDoes(callInfo => EventRegistry.Register(new Event(string.Empty, profileDataValid
                                                                                               ? EventType.Warning
                                                                                               : EventType.Error)));

            var locationDependentInput = Substitute.For<ILocationDependentInput>();
            locationDependentInput.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                  .Returns(locationDependentInputValid)
                                  .AndDoes(callInfo => EventRegistry.Register(new Event(string.Empty, locationDependentInputValid
                                                                                                          ? EventType.Warning
                                                                                                          : EventType.Error)));

            var timeDependentInput = Substitute.For<ITimeDependentInput>();
            timeDependentInput.Validate()
                              .Returns(timeDependentInputValid)
                              .AndDoes(callInfo => EventRegistry.Register(new Event(string.Empty, timeDependentInputValid
                                                                                                      ? EventType.Warning
                                                                                                      : EventType.Error)));

            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(profileData);

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                locationDependentInput
            });

            calculationInput.TimeDependentInputItems.Returns(new[]
            {
                timeDependentInput
            });

            // Call
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput);

            // Assert
            ValidationResultType expectedValidationResultType = profileDataValid
                                                                && locationDependentInputValid
                                                                && timeDependentInputValid
                                                                    ? ValidationResultType.Successful
                                                                    : ValidationResultType.Failed;

            Assert.IsTrue(validationResult.Successful);
            Assert.AreEqual(expectedValidationResultType, validationResult.Data);
            Assert.AreEqual(3, validationResult.Events.Count());
        }

        [Test]
        public void Validate_ExceptionOccurred_ReturnsExpectedResult()
        {
            // Setup
            const string exceptionMessage = "Exception message";
            const string validationMessage = "Validation message";

            var profileData = Substitute.For<IProfileData>();
            profileData.Validate()
                       .Returns(false)
                       .AndDoes(callInfo => EventRegistry.Register(new Event(validationMessage, EventType.Error)));

            var locationDependentInput = Substitute.For<ILocationDependentInput>();
            locationDependentInput.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                  .Returns(true)
                                  .AndDoes(callInfo => throw new InvalidOperationException(exceptionMessage));

            var timeDependentInput = Substitute.For<ITimeDependentInput>();
            timeDependentInput.Validate().Returns(true);

            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(profileData);

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                locationDependentInput
            });

            calculationInput.TimeDependentInputItems.Returns(new[]
            {
                timeDependentInput
            });

            // Call
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput);

            // Assert
            Assert.IsFalse(validationResult.Successful);
            Assert.AreEqual(2, validationResult.Events.Count());

            Event validationEvent = validationResult.Events.ElementAt(0);
            Assert.AreEqual(validationMessage, validationEvent.Message);
            Assert.AreEqual(EventType.Error, validationEvent.Type);

            Event exceptionEvent = validationResult.Events.ElementAt(1);
            Assert.AreEqual("An unhandled error occurred while validating the calculation input. See stack trace for more" +
                            "information:\n" + exceptionMessage, exceptionEvent.Message);
            Assert.AreEqual(EventType.Error, exceptionEvent.Type);
        }
    }
}
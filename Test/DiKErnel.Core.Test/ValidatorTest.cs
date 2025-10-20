// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
using DiKErnel.Core.Data;
using DiKErnel.Util;
using NSubstitute;
using NSubstitute.ExceptionExtensions;
using NUnit.Framework;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    internal sealed class ValidatorTest
    {
        [Test, Combinatorial]
        public void Validate_ValidOrInvalidData_ReturnsExpectedResult([Values(true, false)] bool profileDataValid,
                                                                      [Values(true, false)] bool locationDependentInputValid,
                                                                      [Values(true, false)] bool timeDependentInputValid)
        {
            // Setup
            var timeDependentInput1 = Substitute.For<ITimeDependentInput>();
            timeDependentInput1.Validate().Returns(true);

            var timeDependentInput2 = Substitute.For<ITimeDependentInput>();
            timeDependentInput2.Validate().Returns(timeDependentInputValid);

            var timeDependentInput3 = Substitute.For<ITimeDependentInput>();
            timeDependentInput3.Validate().Returns(true);

            var profileData = Substitute.For<IProfileData>();
            profileData.Validate().Returns(profileDataValid);

            var locationDependentInput1 = Substitute.For<ILocationDependentInput>();
            locationDependentInput1.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                   .Returns(true);

            var locationDependentInput2 = Substitute.For<ILocationDependentInput>();
            locationDependentInput2.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                   .Returns(locationDependentInputValid);

            var locationDependentInput3 = Substitute.For<ILocationDependentInput>();
            locationDependentInput3.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                   .Returns(true);

            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.TimeDependentInputItems.Returns(new[]
            {
                timeDependentInput1,
                timeDependentInput2,
                timeDependentInput3
            });

            calculationInput.ProfileData.Returns(profileData);

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                locationDependentInput1,
                locationDependentInput2,
                locationDependentInput3
            });

            // Call
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput);

            // Assert
            timeDependentInput1.Received(1).Validate();
            timeDependentInput2.Received(1).Validate();
            timeDependentInput3.Received(1).Validate();
            profileData.Received(1).Validate();
            locationDependentInput1.ReceivedWithAnyArgs(1).Validate(null, null);
            locationDependentInput2.ReceivedWithAnyArgs(1).Validate(null, null);
            locationDependentInput3.ReceivedWithAnyArgs(1).Validate(null, null);

            ValidationResultType expectedValidationResultType = profileDataValid
                                                                && locationDependentInputValid
                                                                && timeDependentInputValid
                                                                    ? ValidationResultType.Successful
                                                                    : ValidationResultType.Failed;

            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(expectedValidationResultType));
        }

        [Test]
        public void Validate_ExceptionOccurred_ReturnsExpectedResult()
        {
            // Setup
            const string exceptionMessage = "Exception message";

            var profileData = Substitute.For<IProfileData>();
            profileData.Validate().Returns(true);

            var locationDependentInput = Substitute.For<ILocationDependentInput>();
            locationDependentInput.Validate(Arg.Any<IReadOnlyList<ITimeDependentInput>>(), Arg.Any<IProfileData>())
                                  .ThrowsForAnyArgs(new InvalidOperationException(exceptionMessage));

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
            Assert.That(validationResult.Successful, Is.False);
            Assert.That(validationResult.Events, Has.Count.EqualTo(1));

            Event exceptionEvent = validationResult.Events[0];
            Assert.That(exceptionEvent.Message, Is.EqualTo("An unhandled error occurred while validating the " +
                                                           "calculation input. See stack trace for more information:" +
                                                           $"{Environment.NewLine}{exceptionMessage}"));
            Assert.That(exceptionEvent.Type, Is.EqualTo(EventType.Error));
        }
    }
}
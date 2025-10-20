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
using DiKErnel.Integration.Helpers;
using DiKErnel.TestUtil;
using DiKErnel.Util;
using DiKErnel.Util.Validation;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Integration.Test.Helpers
{
    [TestFixture]
    internal sealed class ValidationHelperTest
    {
        [Test]
        public void GivenValidationIssuesOfNonErrorTypes_WhenRegisterValidationIssues_ThenExpectedResult()
        {
            // Given
            var validationIssue1 = new ValidationIssue(ValidationIssueType.Warning, Random.NextString());
            var validationIssue2 = new ValidationIssue(ValidationIssueType.Warning, Random.NextString());

            // When
            bool validationSuccessful = ValidationHelper.RegisterValidationIssues(new List<ValidationIssue>
            {
                validationIssue1,
                validationIssue2
            });

            // Then
            Assert.That(validationSuccessful, Is.True);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.That(registeredEvents, Has.Count.EqualTo(2));
            Assert.That(registeredEvents[0].Type, Is.EqualTo(EventType.Warning));
            Assert.That(registeredEvents[0].Message, Is.EqualTo(validationIssue1.Message));
            Assert.That(registeredEvents[1].Type, Is.EqualTo(EventType.Warning));
            Assert.That(registeredEvents[1].Message, Is.EqualTo(validationIssue2.Message));
        }

        [Test]
        public void GivenAtLeastOneValidationIssueOfErrorType_WhenRegisterValidationIssues_ThenExpectedResult()
        {
            // Given
            var validationIssue1 = new ValidationIssue(ValidationIssueType.Warning, Random.NextString());
            var validationIssue2 = new ValidationIssue(ValidationIssueType.Error, Random.NextString());

            // When
            bool validationSuccessful = ValidationHelper.RegisterValidationIssues(new List<ValidationIssue>
            {
                validationIssue1,
                validationIssue2
            });

            // Then
            Assert.That(validationSuccessful, Is.False);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.That(registeredEvents, Has.Count.EqualTo(2));
            Assert.That(registeredEvents[0].Type, Is.EqualTo(EventType.Warning));
            Assert.That(registeredEvents[0].Message, Is.EqualTo(validationIssue1.Message));
            Assert.That(registeredEvents[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(registeredEvents[1].Message, Is.EqualTo(validationIssue2.Message));
        }

        [Test]
        public void GivenValidationIssueWithInvalidValidationIssueType_WhenRegisterValidationIssues_ThenThrowsNotSupportedException()
        {
            // Given
            var validationIssue = new ValidationIssue((ValidationIssueType) 99, "Message");

            // When
            void Call() => ValidationHelper.RegisterValidationIssues(new List<ValidationIssue>
            {
                validationIssue
            });

            // Then
            AssertHelper.AssertException<NotSupportedException>(Call,
                                                                "Unsupported ValidationIssueType.");
        }
    }
}
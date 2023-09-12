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
using DiKErnel.Integration.Helpers;
using DiKErnel.Util;
using DiKErnel.Util.Validation;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Integration.Test.Helpers
{
    [TestFixture]
    public class ValidationHelperTest
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
            Assert.IsTrue(validationSuccessful);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.AreEqual(2, registeredEvents.Count);
            Assert.AreEqual(EventType.Warning, registeredEvents[0].Type);
            Assert.AreEqual(validationIssue1.Message, registeredEvents[0].Message);
            Assert.AreEqual(EventType.Warning, registeredEvents[1].Type);
            Assert.AreEqual(validationIssue2.Message, registeredEvents[1].Message);
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
            Assert.IsFalse(validationSuccessful);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.AreEqual(2, registeredEvents.Count);
            Assert.AreEqual(EventType.Warning, registeredEvents[0].Type);
            Assert.AreEqual(validationIssue1.Message, registeredEvents[0].Message);
            Assert.AreEqual(EventType.Error, registeredEvents[1].Type);
            Assert.AreEqual(validationIssue2.Message, registeredEvents[1].Message);
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
            Assert.Throws<NotSupportedException>(Call, "Unsupported ValidationIssueType.");
        }
    }
}
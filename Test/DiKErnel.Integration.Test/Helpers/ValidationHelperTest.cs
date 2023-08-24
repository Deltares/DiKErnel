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

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Helpers
{
    [TestFixture]
    public class ValidationHelperTest
    {
        
    }

    struct ValidationHelperTest : Test
    {
        static void RegisterValidationIssueWithInvalidValidationIssueType()
        {
            var validationIssues = vector<unique_ptr<ValidationIssue>>();
            validationIssues.emplace_back(make_unique<ValidationIssue>(static_cast<ValidationIssueType>(99), "Message"));

            ValidationHelper::RegisterValidationIssues(validationIssues);
        }
    };

        [Test]
    public void GivenValidationIssueWithInvalidValidationIssueType_WhenRegisterValidationIssues_ThenThrowsOutOfRangeException()
    {
        // Given & When
        const var action = &RegisterValidationIssueWithInvalidValidationIssueType;

        // Then
        AssertHelper::AssertThrowsWithMessage<out_of_range>(action, "Invalid ValidationIssueType.");
    }
}

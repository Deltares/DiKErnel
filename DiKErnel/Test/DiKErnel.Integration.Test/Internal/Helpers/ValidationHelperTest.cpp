// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include <gtest/gtest.h>

#include "AssertHelper.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;
    using namespace Util;

    struct ValidationHelperTest : Test
    {
        static void RegisterValidationIssueWithInvalidValidationIssueType()
        {
            auto validationIssues = vector<unique_ptr<ValidationIssue>>();
            validationIssues.emplace_back(make_unique<ValidationIssue>(static_cast<ValidationIssueType>(99), "Message"));

            ValidationHelper::RegisterValidationIssues(validationIssues);
        }
    };

    TEST_F(ValidationHelperTest, GivenValidationIssueWithInvalidValidationIssueType_WhenRegisterValidationIssues_ThenThrowsOutOfRangeException)
    {
        // Given & When
        const auto action = &RegisterValidationIssueWithInvalidValidationIssueType;

        // Then
        AssertHelper::AssertThrowsWithMessage<out_of_range>(action, "Invalid ValidationIssueType.");
    }
}

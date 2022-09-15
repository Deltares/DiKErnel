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

#include "GenericValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace Util;
    using namespace TestUtil;

    TEST(GenericValidatorTest, TimeSteps_NoTimeSteps_ReturnsExpectedValidationIssue)
    {
        // Call
        const auto validationIssue = GenericValidator::TimeSteps(vector<pair<int, int>>());

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("At least 1 time step must be defined.", validationIssue->GetMessage());
    }

    TEST(GenericValidatorTest, TimeSteps_TimeStepsNotSuccessive_ReturnsExpectedValidationIssue)
    {
        // Setup
        const auto timeSteps = vector
        {
            pair(0, 100),
            pair(200, 100)
        };

        // Call
        const auto validationIssue = GenericValidator::TimeSteps(timeSteps);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("The begin time of a successive element must equal the end time of the previous element.", validationIssue->GetMessage());
    }

    TEST(GenericValidatorTest, TimeSteps_ValidTimeSteps_ReturnsNullPtr)
    {
        // Setup
        const auto timeSteps = vector
        {
            pair(0, 100),
            pair(100, 200)
        };

        // Call
        const auto validationIssue = GenericValidator::TimeSteps(timeSteps);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }
}

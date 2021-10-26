// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "TimeStepValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct TimeStepValidatorTest : Test
    {
        static unique_ptr<ValidationIssue> IncrementOfTime(
            const int beginTime)
        {
            return TimeStepValidator::IncrementOfTime(beginTime, 100);
        }
    };

    TEST_F(TimeStepValidatorTest, IncrementOfTime_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = IncrementOfTime;

        constexpr auto errorMessage = "BeginTime must be smaller than EndTime.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::INTEGER_MIN);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 99);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 100, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 101, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::INTEGER_MAX, ValidationIssueType::Error, errorMessage);
    }
}

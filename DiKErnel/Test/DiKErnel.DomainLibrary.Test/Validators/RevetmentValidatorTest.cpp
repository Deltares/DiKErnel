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

#include "RevetmentValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
    using namespace Util;
    using namespace TestUtil;

    struct RevetmentValidatorTest : Test
    {
        static unique_ptr<ValidationIssue> FailureNumber(
            const double failureNumber)
        {
            return RevetmentValidator::FailureNumber(failureNumber, 0);
        }
    };

    TEST_F(RevetmentValidatorTest, InitialDamage_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = RevetmentValidator::InitialDamage;

        constexpr auto errorMessage = "InitialDamage must be equal to 0 or larger.";
        constexpr auto warningMessage = "InitialDamage should be in range [0, 1}.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Warning, warningMessage);
    }

    TEST_F(RevetmentValidatorTest, FailureNumber_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = FailureNumber;

        constexpr auto errorMessage = "FailureNumber must be equal to InitialDamage or larger.";

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(RevetmentValidatorTest, AverageNumberOfWavesCtm_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = RevetmentValidator::AverageNumberOfWavesCtm;

        constexpr auto errorMessage = "AverageNumberOfWavesCtm must be larger than 0.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }
}

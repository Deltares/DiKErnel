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

#include "GrassRevetmentValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace Util;
    using namespace TestUtil;

    TEST(GrassRevetmentValidatorTest, CriticalCumulativeOverload_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentValidator::CriticalCumulativeOverload;

        constexpr auto errorMessage = "CriticalCumulativeOverload must be larger than 0.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(GrassRevetmentValidatorTest, FixedNumberOfWaves_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentValidator::FixedNumberOfWaves;

        constexpr auto errorMessage = "FixedNumberOfWaves must be larger than 0.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::INTEGER_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, -1, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 1);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::INTEGER_MAX);
    }

    TEST(GrassRevetmentValidatorTest, CriticalFrontVelocity_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentValidator::CriticalFrontVelocity;

        constexpr auto errorMessage = "CriticalFrontVelocity must be equal to 0 or larger.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(GrassRevetmentValidatorTest, IncreasedLoadTransitionAlphaM_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentValidator::IncreasedLoadTransitionAlphaM;

        constexpr auto errorMessage = "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(GrassRevetmentValidatorTest, ReducedStrengthTransitionAlphaS_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentValidator::ReducedStrengthTransitionAlphaS;

        constexpr auto errorMessage = "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }
}

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

#include "GrassRevetmentOvertoppingValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace Util;
    using namespace testing;
    using namespace TestUtil;

    struct GrassRevetmentOvertoppingValidatorTest : Test
    {
        static unique_ptr<ValidationIssue> WaterLevel(
            const double waterLevel)
        {
            return GrassRevetmentOvertoppingValidator::WaterLevel(waterLevel, 3.33);
        }
    };

    TEST_F(GrassRevetmentOvertoppingValidatorTest, FixedNumberOfWaves_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentOvertoppingValidator::AccelerationAlphaA;

        constexpr auto errorMessage = "AccelerationAlphaA must be equal to 0 or larger.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(GrassRevetmentOvertoppingValidatorTest, FrontVelocityCwo_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentOvertoppingValidator::FrontVelocityCwo;

        constexpr auto errorMessage = "FrontVelocityCwo must be larger than 0.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(GrassRevetmentOvertoppingValidatorTest, WaterLevel_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = WaterLevel;

        constexpr auto warningMessage = "WaterLevel should be smaller than the dike height.";

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MIN);

        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 3.37, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 3.37 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Warning,
                                                   warningMessage);

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Warning, warningMessage);
    }
}

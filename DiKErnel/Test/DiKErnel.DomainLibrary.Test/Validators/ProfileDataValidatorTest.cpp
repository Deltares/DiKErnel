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

#include "ProfileDataValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
    using namespace Util;
    using namespace TestUtil;

    struct ProfileDataValidatorTest : Test
    {
        static unique_ptr<ValidationIssue> RoughnessCoefficient(
            const double roughnessCoefficient)
        {
            return ProfileDataValidator::RoughnessCoefficient(roughnessCoefficient);
        }
    };

    TEST_F(ProfileDataValidatorTest, RoughnessCoefficient_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = RoughnessCoefficient;

        constexpr auto errorMessage = "Roughness coefficient should be in range [0.5, 1].";

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.5 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.5);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 0.5 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue<double>(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 1.0);
        ValidatorAssertHelper::AssertValue<double>(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue<double>(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }
}

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

#include <limits>

#include <gtest/gtest.h>

#include "GrassRevetmentWaveRunupRayleighValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupRayleighValidatorTest, FixedNumberOfWaves_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveRunupRayleighValidator::FixedNumberOfWaves;

        constexpr auto errorMessage = "FixedNumberOfWaves must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::INTEGER_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::INTEGER_MAX);
    }

    TEST(GrassRevetmentWaveRunupRayleighValidatorTest, FrontVelocityCu_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveRunupRayleighValidator::FrontVelocityCu;

        constexpr auto errorMessage = "FrontVelocityCu must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }
}

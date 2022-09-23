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

#include "GrassRevetmentWaveRunupValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace Util;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupValidatorTest, RepresentativeWaveRunup2PGammab_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammab;

        constexpr auto errorMessage = "RepresentativeWaveRunup2PGammab must be in range [0.6, 1].";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.6 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.6);
        ValidatorAssertHelper::AssertValue(validateAction, 0.6 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST(GrassRevetmentWaveRunupValidatorTest, RepresentativeWaveRunup2PGammaf_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammaf;

        constexpr auto errorMessage = "RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.5 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.5);
        ValidatorAssertHelper::AssertValue(validateAction, 0.5 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST(GrassRevetmentWaveRunupValidatorTest, OuterSlope_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveRunupValidator::OuterSlope;

        constexpr auto errorMessage = "OuterSlope must be in range {0, 1}.";

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertValue(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertValue(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertValue(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }
}

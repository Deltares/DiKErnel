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

#include "RevetmentValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
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

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 1);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 1, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Warning, warningMessage);
    }

    TEST_F(RevetmentValidatorTest, FailureNumber_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = FailureNumber;

        constexpr auto errorMessage = "FailureNumber must be larger than InitialDamage.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity());
    }

    TEST_F(RevetmentValidatorTest, AverageNumberOfWavesCtm_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = RevetmentValidator::AverageNumberOfWavesCtm;

        constexpr auto errorMessage = "AverageNumberOfWavesCtm must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity());
    }
}

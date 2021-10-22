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

#include "NaturalStoneRevetmentValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = NaturalStoneRevetmentValidator::RelativeDensity;

        constexpr auto errorMessage = "RelativeDensity must be in range {0, 10}.";
        constexpr auto warningMessage = "RelativeDensity should be in range [0.1, 5].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.1);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.1);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 5);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 5);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 5, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 10, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 10, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 10, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Error, errorMessage);
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = NaturalStoneRevetmentValidator::ThicknessTopLayer;

        constexpr auto errorMessage = "ThicknessTopLayer must be in range {0, 1}.";
        constexpr auto warningMessage = "ThicknessTopLayer should be in range [0.04, 0.6].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.04, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.04);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.04);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.6);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.6);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.6, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 1, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Error, errorMessage);
    }

    TEST(NaturalStoneRevetmentValidatorTest, SlopeUpperLevelAus_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = NaturalStoneRevetmentValidator::SlopeUpperLevelAus;

        constexpr auto errorMessage = "SlopeUpperLevelAus must be above 0.";
        constexpr auto warningMessage = "SlopeUpperLevelAus should be in range [0.01, 0.2].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.01, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.01);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.01);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.2);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.2);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.2, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Warning, warningMessage);
    }

    TEST(NaturalStoneRevetmentValidatorTest, SlopeLowerLevelAls_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = NaturalStoneRevetmentValidator::SlopeLowerLevelAls;

        constexpr auto errorMessage = "SlopeLowerLevelAls must be above 0.";
        constexpr auto warningMessage = "SlopeLowerLevelAls should be in range [1, 2].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 1);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 2);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 2);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 2, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Warning, warningMessage);
    }
}

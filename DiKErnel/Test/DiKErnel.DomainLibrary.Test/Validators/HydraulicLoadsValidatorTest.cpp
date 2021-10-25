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

#include "HydraulicLoadsValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace TestUtil;
    using namespace std;

    TEST(HydraulicLoadsTest, WaveHeightHm0_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = HydraulicLoadsValidator::WaveHeightHm0;

        constexpr auto errorMessage = "WaveHeightHm0 must be larger than 0.";
        constexpr auto warningMessage = "WaveHeightHm0 should be in range {0.1, 10}.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.1, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.1);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 10);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 10, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 10, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Warning, warningMessage);
    }

    TEST(HydraulicLoadsTest, WavePeriodTm10_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = HydraulicLoadsValidator::WavePeriodTm10;

        constexpr auto errorMessage = "WavePeriodTm10 must be larger than 0.";
        constexpr auto warningMessage = "WavePeriodTm10 should be in range {0.5, 25}.";
        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 0.5, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.5, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 0.5);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 25);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 25, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 25, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Warning, warningMessage);
    }

    TEST(HydraulicLoadsTest, WaveAngle_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = HydraulicLoadsValidator::WaveAngle;

        constexpr auto errorMessage = "WaveAngle must be in range {-180, 180}.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, -1 * numeric_limits<double>::infinity(), ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertBelowBound(validateAction, -180, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, -180, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, -180);

        ValidatorAssertHelper::AssertBelowBound(validateAction, 180);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 180, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertAboveBound(validateAction, 180, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, numeric_limits<double>::infinity(), ValidationIssueType::Error, errorMessage);
    }
}

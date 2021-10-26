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

#include "GrassRevetmentWaveImpactValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct GrassRevetmentWaveImpactValidatorTest : Test
    {
        static unique_ptr<ValidationIssue> TimeLineAgwi(
            const double timeLineAgwi)
        {
            return GrassRevetmentWaveImpactValidator::TimeLineAgwi(timeLineAgwi, 3);
        }

        static unique_ptr<ValidationIssue> UpperLimitLoadingAul(
            const double upperLimitLoadingAul)
        {
            return GrassRevetmentWaveImpactValidator::UpperLimitLoadingAul(upperLimitLoadingAul, 2);
        }
    };

    TEST_F(GrassRevetmentWaveImpactValidatorTest, TimeLineAgwi_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = TimeLineAgwi;

        constexpr auto errorMessage = "TimeLineAgwi must be larger than TimeLineCgwi.";

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 3.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 3.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 3.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, TimeLineB1gwi_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::TimeLineBgwi;

        constexpr auto errorMessage = "TimeLineBgwi must be smaller than 0";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, TimeLineCgwi_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::TimeLineCgwi;

        constexpr auto errorMessage = "TimeLineCgwi must be equal to 0 or larger.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, MinimumWaveHeightTemax_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::MinimumWaveHeightTemax;

        constexpr auto errorMessage = "MinimumWaveHeightTemax must be equal to 3600000 or smaller.";
        constexpr auto warningMessage = "MinimumWaveHeightTemax should be in range {1000000, 3600000].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Warning, warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1000000.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Warning,
                                                  warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1000000.0, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1000000.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3600000.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3600000.0);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3600000.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error,
                                                  errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, MaximumWaveHeightTemin_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::MaximumWaveHeightTemin;

        constexpr auto errorMessage = "MaximumWaveHeightTemin must be equal to 3.6 or larger.";
        constexpr auto warningMessage = "MaximumWaveHeightTemin should be in range [3.6, 10}.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3.6 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3.6);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 3.6 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 10.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 10.0, ValidationIssueType::Warning, warningMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 10.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Warning,
                                                  warningMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Warning, warningMessage);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, WaveAngleImpactNwa_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::WaveAngleImpactNwa;

        constexpr auto errorMessage = "WaveAngleImpactNwa must be equal to 1 or smaller.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, WaveAngleImpactQwa_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::WaveAngleImpactQwa;

        constexpr auto errorMessage = "WaveAngleImpactQwa must be in range [0, 1].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, WaveAngleImpactRwa_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = GrassRevetmentWaveImpactValidator::WaveAngleImpactRwa;

        constexpr auto errorMessage = "WaveAngleImpactRwa must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0.0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST_F(GrassRevetmentWaveImpactValidatorTest, UpperLimitLoadingAul_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = UpperLimitLoadingAul;

        constexpr auto errorMessage = "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.";

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, ValidatorAssertHelper::DOUBLE_MIN);

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 2.0 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 2.0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, 2.0 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound<double>(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }
}

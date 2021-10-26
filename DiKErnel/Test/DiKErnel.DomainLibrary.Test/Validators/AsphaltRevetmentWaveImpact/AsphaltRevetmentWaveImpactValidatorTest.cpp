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

#include "AsphaltRevetmentWaveImpactValidator.h"
#include "ValidatorAssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(AsphaltRevetmentWaveImpactValidatorTest, FatigueAlpha_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::FatigueAlpha;

        constexpr auto errorMessage = "FatigueAlpha must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, FatigueBeta_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::FatigueBeta;

        constexpr auto errorMessage = "FatigueBeta must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, FailureTension_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::FailureTension;

        constexpr auto errorMessage = "FailureTension must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, ImpactNumberC_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::ImpactNumberC;

        constexpr auto errorMessage = "ImpactNumberC must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, DensityOfWater_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::DensityOfWater;

        constexpr auto errorMessage = "DensityOfWater must be in range [950, 1050].";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 950 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 950);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 950 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1050 - ValidatorAssertHelper::EPSILON);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1050);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 1050 + ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX, ValidationIssueType::Error, errorMessage);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, SoilElasticity_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::SoilElasticity;

        constexpr auto errorMessage = "SoilElasticity must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, StiffnessRelationNu_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::StiffnessRelationNu;

        constexpr auto errorMessage = "StiffnessRelationNu must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, Thickness_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::Thickness;

        constexpr auto errorMessage = "Thickness must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }

    TEST(AsphaltRevetmentWaveImpactValidatorTest, ElasticModulus_VariousScenarios_ExpectedValues)
    {
        const auto validateAction = AsphaltRevetmentWaveImpactValidator::ElasticModulus;

        constexpr auto errorMessage = "ElasticModulus must be larger than 0.";

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MIN, ValidationIssueType::Error, errorMessage);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 - ValidatorAssertHelper::EPSILON, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0, ValidationIssueType::Error, errorMessage);
        ValidatorAssertHelper::AssertEqualToBound(validateAction, 0 + ValidatorAssertHelper::EPSILON);

        ValidatorAssertHelper::AssertEqualToBound(validateAction, ValidatorAssertHelper::DOUBLE_MAX);
    }
}

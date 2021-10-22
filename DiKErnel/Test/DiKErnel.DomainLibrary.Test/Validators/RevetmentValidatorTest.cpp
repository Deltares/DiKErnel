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

#include "RevetmentValidator.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST(RevetmentValidatorTest, InitialDamage_BelowZero_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = RevetmentValidator::InitialDamage(-0.0000000001);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("InitialDamage must be a positive number.", validationIssue->GetMessage());
    }

    TEST(RevetmentValidatorTest, InitialDamage_One_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = RevetmentValidator::InitialDamage(1);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("InitialDamage should be smaller than 1.", validationIssue->GetMessage());
    }

    TEST(RevetmentValidatorTest, InitialDamage_Zero_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = RevetmentValidator::InitialDamage(0);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(RevetmentValidatorTest, InitialDamage_SmallerThanOne_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = RevetmentValidator::InitialDamage(0.99999999999);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(RevetmentValidatorTest, FailureNumber_SmallerThanInitialDamage_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = RevetmentValidator::FailureNumber(0.199999999999, 0.2);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("FailureNumber must be larger than InitialDamage.", validationIssue->GetMessage());
    }

    TEST(RevetmentValidatorTest, FailureNumber_EqualToInitialDamage_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = RevetmentValidator::FailureNumber(0, 0);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(RevetmentValidatorTest, FailureNumber_LargerThanInitialDamage_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = RevetmentValidator::FailureNumber(0.0000000000001, 0);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }
}

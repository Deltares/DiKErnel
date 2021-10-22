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

#include "NaturalStoneRevetmentValidator.h"

namespace DiKErnel::DomainLibrary::Test
{
    #pragma region RelativeDensity

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_Zero_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(0);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity must be in range {0, 10}.", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_Ten_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(10);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity must be in range {0, 10}.", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_AboveZero_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(0.0000000001);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity should be in range [0.1, 5].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_BelowZeroPointOne_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(0.0000000009);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity should be in range [0.1, 5].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_AboveFive_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(5.0000000001);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity should be in range [0.1, 5].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_BelowTen_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(9.9999999999);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("RelativeDensity should be in range [0.1, 5].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_ZeroPointOne_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(0.1);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(NaturalStoneRevetmentValidatorTest, RelativeDensity_Five_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::RelativeDensity(5);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    #pragma endregion

    #pragma region ThicknessTopLayer

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_Zero_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer must be in range {0, 1}.", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_One_ReturnValidationIssueWithError)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(1);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer must be in range {0, 1}.", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_AboveZero_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.0000000001);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer should be in range [0.04, 0.6].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_BelowZeroPointZeroFour_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.0333333339);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer should be in range [0.04, 0.6].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_AboveZeroPointSix_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.6000000001);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer should be in range [0.04, 0.6].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_BelowOne_ReturnValidationIssueWithWarning)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.9999999999);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Warning, validationIssue->GetValidationIssueType());
        ASSERT_EQ("ThicknessTopLayer should be in range [0.04, 0.6].", validationIssue->GetMessage());
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_ZeroPointZeroFour_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.04);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(NaturalStoneRevetmentValidatorTest, ThicknessTopLayer_ZeroPointSix_ReturnNullPtr)
    {
        // Call
        const auto validationIssue = NaturalStoneRevetmentValidator::ThicknessTopLayer(0.6);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    #pragma endregion
}

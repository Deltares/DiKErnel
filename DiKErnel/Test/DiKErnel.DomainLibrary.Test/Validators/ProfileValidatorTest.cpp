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

#include "ProfileValidator.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace Util;

    TEST(ProfileValidatorTest, OuterToe_NoOuterToe_ReturnsExpectedValidationIssue)
    {
        // Call
        const auto validationIssue = ProfileValidator::OuterToe(nullptr);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("The OuterToe must be defined.", validationIssue->GetMessage());
    }

    TEST(ProfileValidatorTest, OuterToe_ValidOuterToe_ReturnsNullPtr)
    {
        // Setup
        constexpr auto outerToe = pair<double, double>(0, 0);

        // Call
        const auto validationIssue = ProfileValidator::OuterToe(&outerToe);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    TEST(ProfileValidatorTest, OuterCrest_NoOuterCrest_ReturnsExpectedValidationIssue)
    {
        // Call
        const auto validationIssue = ProfileValidator::OuterCrest(nullptr);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(ValidationIssueType::Error, validationIssue->GetValidationIssueType());
        ASSERT_EQ("The OuterCrest must be defined.", validationIssue->GetMessage());
    }

    TEST(ProfileValidatorTest, OuterCrest_ValidOuterCrest_ReturnsNullPtr)
    {
        // Setup
        constexpr auto outerCrest = pair<double, double>(0, 0);

        // Call
        const auto validationIssue = ProfileValidator::OuterCrest(&outerCrest);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }
}

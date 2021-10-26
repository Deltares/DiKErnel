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

#pragma once

#include <gtest/gtest.h>

#include <limits>

#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary::TestUtil
{
    class ValidatorAssertHelper
    {
        public:
            inline constexpr static double EPSILON = 1e-6;

            inline constexpr static double DOUBLE_MIN = std::numeric_limits<double>::min();

            inline constexpr static double DOUBLE_MAX = std::numeric_limits<double>::max();

            inline constexpr static int INTEGER_MIN = std::numeric_limits<int>::min();

            inline constexpr static int INTEGER_MAX = std::numeric_limits<int>::max();

            template <typename T>
            static void AssertEqualToBound(
                std::unique_ptr<ValidationIssue> (*const validateAction)(T),
                T bound)
            {
                // Call
                const auto validationIssue = validateAction(bound);

                // Assert
                ASSERT_EQ(nullptr, validationIssue);
            }

            template <typename T>
            static void AssertEqualToBound(
                std::unique_ptr<ValidationIssue> (*const validateAction)(T),
                T bound,
                ValidationIssueType validationIssueType,
                const std::string& message)
            {
                // Call
                const auto validationIssue = validateAction(bound);

                // Assert
                ASSERT_NE(nullptr, validationIssue);
                ASSERT_EQ(validationIssueType, validationIssue->GetValidationIssueType());
                ASSERT_EQ(message, validationIssue->GetMessage());
            }
    };
}

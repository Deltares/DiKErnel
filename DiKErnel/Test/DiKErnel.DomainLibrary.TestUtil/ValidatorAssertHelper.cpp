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

#include "ValidatorAssertHelper.h"

#include <gtest/gtest.h>

namespace DiKErnel::DomainLibrary::TestUtil
{
    void ValidatorAssertHelper::AssertBelowBound(
        const ActionWithDouble validateAction,
        const double bound)
    {
        AssertValidBound(validateAction, bound - _doubleEpsilon);
    }

    void ValidatorAssertHelper::AssertBelowBound(
        const ActionWithDouble validateAction,
        const double bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        AssertInvalidBound(validateAction, bound - _doubleEpsilon, validationIssueType, message);
    }

    void ValidatorAssertHelper::AssertEqualToBound(
        const ActionWithDouble validateAction,
        const double bound)
    {
        AssertValidBound(validateAction, bound);
    }

    void ValidatorAssertHelper::AssertEqualToBound(
        const ActionWithDouble validateAction,
        const double bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        AssertInvalidBound(validateAction, bound, validationIssueType, message);
    }

    void ValidatorAssertHelper::AssertAboveBound(
        const ActionWithDouble validateAction,
        const double bound)
    {
        AssertValidBound(validateAction, bound + _doubleEpsilon);
    }

    void ValidatorAssertHelper::AssertAboveBound(
        const ActionWithDouble validateAction,
        const double bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        AssertInvalidBound(validateAction, bound + _doubleEpsilon, validationIssueType, message);
    }

    void ValidatorAssertHelper::AssertEqualToBound(
        const ActionWithInt validateAction,
        const int bound)
    {
        AssertValidBound(validateAction, bound);
    }

    void ValidatorAssertHelper::AssertEqualToBound(
        const ActionWithInt validateAction,
        const int bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        AssertInvalidBound(validateAction, bound, validationIssueType, message);
    }

    void ValidatorAssertHelper::AssertAboveBound(
        const ActionWithInt validateAction,
        const int bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        AssertInvalidBound(validateAction, bound + 1, validationIssueType, message);
    }

    template <typename TAction, typename TBound>
    void ValidatorAssertHelper::AssertValidBound(
        const TAction validateAction,
        const TBound bound)
    {
        // Call
        const auto validationIssue = validateAction(bound);

        // Assert
        ASSERT_EQ(nullptr, validationIssue);
    }

    template <typename TAction, typename TBound>
    void ValidatorAssertHelper::AssertInvalidBound(
        const TAction validateAction,
        const TBound bound,
        const ValidationIssueType validationIssueType,
        const std::string& message)
    {
        // Call
        const auto validationIssue = validateAction(bound);

        // Assert
        ASSERT_NE(nullptr, validationIssue);
        ASSERT_EQ(validationIssueType, validationIssue->GetValidationIssueType());
        ASSERT_EQ(message, validationIssue->GetMessage());
    }
}

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

#include <memory>

#include "GrassRevetmentValidator.h"
#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;
    using namespace Util;

    unique_ptr<ValidationIssue> GrassRevetmentValidator::CriticalCumulativeOverload(
        const double criticalCumulativeOverload)
    {
        if (criticalCumulativeOverload <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "CriticalCumulativeOverload must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentValidator::CriticalFrontVelocity(
        const double criticalFrontVelocity)
    {
        return ValidateEqualToOrLargerThanZero(criticalFrontVelocity, "CriticalFrontVelocity");
    }

    unique_ptr<ValidationIssue> GrassRevetmentValidator::FixedNumberOfWaves(
        const int fixedNumberOfWaves)
    {
        if (fixedNumberOfWaves <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "FixedNumberOfWaves must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentValidator::IncreasedLoadTransitionAlphaM(
        const double increasedLoadTransitionAlphaM)
    {
        return ValidateEqualToOrLargerThanZero(increasedLoadTransitionAlphaM, "IncreasedLoadTransitionAlphaM");
    }

    unique_ptr<ValidationIssue> GrassRevetmentValidator::ReducedStrengthTransitionAlphaS(
        const double reducedStrengthTransitionAlphaS)
    {
        return ValidateEqualToOrLargerThanZero(reducedStrengthTransitionAlphaS, "ReducedStrengthTransitionAlphaS");
    }

    unique_ptr<ValidationIssue> GrassRevetmentValidator::ValidateEqualToOrLargerThanZero(
        const double propertyToValidate,
        const string& propertyName)
    {
        if (propertyToValidate < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, propertyName + " must be equal to 0 or larger.");
        }

        return nullptr;
    }
}

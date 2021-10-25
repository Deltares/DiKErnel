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

#include "GenericValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> GenericValidator::TimeSteps(
        const vector<pair<int, int>>& timeSteps)
    {
        if (timeSteps.empty())
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "At least 1 time step must be defined.");
        }

        auto previousEndTime = numeric_limits<int>::min();

        for (const auto& [beginTime, endTime] : timeSteps)
        {
            if (previousEndTime != numeric_limits<int>::min() && beginTime != previousEndTime)
            {
                return make_unique<ValidationIssue>(ValidationIssueType::Error,
                                                    "The begin time of a successive element must equal the end time of the previous element.");
            }

            previousEndTime = endTime;
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GenericValidator::NumberOfLocations(
        const int numberOfLocations)
    {
        if (numberOfLocations <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "At least 1 location must be defined.");
        }

        return nullptr;
    }
}

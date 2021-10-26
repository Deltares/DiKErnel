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

#include "ValidationHelper.h"

#include <stdexcept>

#include "EventRegistry.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    bool ValidationHelper::RegisterValidationIssues(
        const vector<unique_ptr<ValidationIssue>>& validationIssues)
    {
        auto validationSuccessful = true;

        for (auto& validationIssue : validationIssues)
        {
            validationSuccessful = RegisterValidationIssue(validationIssue) && validationSuccessful;
        }

        return validationSuccessful;
    }

    bool ValidationHelper::RegisterValidationIssue(
        const unique_ptr<ValidationIssue>& validationIssue)
    {
        if (validationIssue != nullptr)
        {
            const auto validationIssueType = validationIssue->GetValidationIssueType();

            EventRegistry::Register(make_unique<Event>(validationIssue->GetMessage(),
                                                       ConvertValidationIssueType(validationIssueType)));

            if (validationIssueType == ValidationIssueType::Error)
            {
                return false;
            }
        }

        return true;
    }

    EventType ValidationHelper::ConvertValidationIssueType(
        const ValidationIssueType validationIssueType)
    {
        switch (validationIssueType)
        {
            case ValidationIssueType::Warning:
                return EventType::Warning;
            case ValidationIssueType::Error:
                return EventType::Error;
            default:
                throw out_of_range("Invalid ValidationIssueType.");
        }
    }
}

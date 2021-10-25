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

#include "GrassRevetmentWaveImpactValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::TimeLineAgwi(
        const double timeLineAgwi,
        const double timeLineCgwi)
    {
        if (timeLineAgwi <= timeLineCgwi) 
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "TimeLineAgwi must be larger than TimeLineCgwi.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::TimeLineBgwi(
        const double timeLineBgwi)
    {
        if(timeLineBgwi >= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "TimeLineBgwi must be smaller than 0");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::TimeLineCgwi(
        const double timeLineCgwi)
    {
        if(timeLineCgwi < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "TimeLineCgwi must be equal to 0 or larger.");
        }

        return nullptr;
    }
}

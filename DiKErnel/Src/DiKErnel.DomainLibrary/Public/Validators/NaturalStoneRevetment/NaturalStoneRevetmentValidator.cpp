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

#include "NaturalStoneRevetmentValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> NaturalStoneRevetmentValidator::RelativeDensity(
        const double relativeDensity)
    {
        if(relativeDensity <= 0 || relativeDensity >= 10)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "RelativeDensity must be in range {0, 10}.");
        }

        if(relativeDensity < 0.1 || relativeDensity > 5)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "RelativeDensity should be in range [0.1, 5].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> NaturalStoneRevetmentValidator::ThicknessTopLayer(
        const double thicknessTopLayer)
    {
        if(thicknessTopLayer <= 0 || thicknessTopLayer >= 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "ThicknessTopLayer must be in range {0, 1}.");
        }

        if(thicknessTopLayer < 0.04 || thicknessTopLayer > 0.6)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "ThicknessTopLayer should be in range [0.04, 0.6].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> NaturalStoneRevetmentValidator::SlopeUpperLevelAus(
        const double slopeUpperLevelAus)
    {
        if(slopeUpperLevelAus <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "SlopeUpperLevelAus must be above 0.");
        }

        if(slopeUpperLevelAus < 0.01 || slopeUpperLevelAus > 0.2)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "SlopeUpperLevelAus should be in range [0.01, 0.2].");
        }

        return nullptr;
    }
}

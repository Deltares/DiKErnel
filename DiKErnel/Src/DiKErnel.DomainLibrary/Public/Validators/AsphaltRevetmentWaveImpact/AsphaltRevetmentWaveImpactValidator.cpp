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

#include "AsphaltRevetmentWaveImpactValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FatigueAlpha(
        const double fatigueAlpha)
    {
        if (fatigueAlpha <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "FatigueAlpha must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FatigueBeta(
        const double fatigueBeta)
    {
        if (fatigueBeta <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "FatigueBeta must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FailureTension(
        const double failureTension)
    {
        if (failureTension <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "FailureTension must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::ImpactNumberC(
        const double impactNumberC)
    {
        if (impactNumberC <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "ImpactNumberC must be larger than 0.");
        }

        return nullptr;
    }
}

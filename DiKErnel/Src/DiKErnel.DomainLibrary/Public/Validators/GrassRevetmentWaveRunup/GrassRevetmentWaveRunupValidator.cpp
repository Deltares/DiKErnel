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

#include "GrassRevetmentWaveRunupValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::CriticalCumulativeOverload(
        const double criticalCumulativeOverload)
    {
        if (criticalCumulativeOverload <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "CriticalCumulativeOverload must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammab(
        const double representativeWaveRunup2PGammab)
    {
        if (representativeWaveRunup2PGammab < 0.6 || representativeWaveRunup2PGammab > 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "RepresentativeWaveRunup2PGammab must be in range [0.6, 1].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammaf(
        const double representativeWaveRunup2PGammaf)
    {
        if (representativeWaveRunup2PGammaf < 0.5 || representativeWaveRunup2PGammaf > 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::OuterSlope(
        const double outerSlope)
    {
        if (outerSlope <= 0 || outerSlope >= 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "OuterSlope must be in range {0, 1}.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::CriticalFrontVelocity(
        const double criticalFrontVelocity)
    {
        if (criticalFrontVelocity < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "CriticalFrontVelocity must be equal to 0 or larger.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::IncreasedLoadTransitionAlphaM(
        const double increasedLoadTransitionAlphaM)
    {
        if (increasedLoadTransitionAlphaM < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveRunupValidator::ReducedStrengthTransitionAlphaS(
        const double reducedStrengthTransitionAlphaS)
    {
        if (reducedStrengthTransitionAlphaS < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.");
        }

        return nullptr;
    }
}

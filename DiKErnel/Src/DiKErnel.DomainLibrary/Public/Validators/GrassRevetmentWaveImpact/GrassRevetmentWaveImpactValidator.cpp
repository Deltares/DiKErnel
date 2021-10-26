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
        if (timeLineBgwi >= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "TimeLineBgwi must be smaller than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::TimeLineCgwi(
        const double timeLineCgwi)
    {
        if (timeLineCgwi < 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "TimeLineCgwi must be equal to 0 or larger.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::MinimumWaveHeightTemax(
        const double minimumWaveHeightTemax)
    {
        if (minimumWaveHeightTemax > 3600000)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "MinimumWaveHeightTemax must be equal to 3600000 or smaller.");
        }

        if (minimumWaveHeightTemax <= 1000000)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "MinimumWaveHeightTemax should be in range {1000000, 3600000].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::MaximumWaveHeightTemin(
        const double maximumWaveHeightTemin)
    {
        if (maximumWaveHeightTemin < 3.6)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "MaximumWaveHeightTemin must be equal to 3.6 or larger.");
        }

        if (maximumWaveHeightTemin >= 10)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "MaximumWaveHeightTemin should be in range [3.6, 10}.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::WaveAngleImpactNwa(
        const double waveAngleImpactNwa)
    {
        if (waveAngleImpactNwa > 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WaveAngleImpactNwa must be equal to 1 or smaller.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::WaveAngleImpactQwa(
        const double waveAngleImpactQwa)
    {
        if (waveAngleImpactQwa < 0 || waveAngleImpactQwa > 1)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WaveAngleImpactQwa must be in range [0, 1].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::WaveAngleImpactRwa(
        const double waveAngleImpactRwa)
    {
        if (waveAngleImpactRwa <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WaveAngleImpactRwa must be larger than 0.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> GrassRevetmentWaveImpactValidator::UpperLimitLoadingAul(
        const double upperLimitLoadingAul,
        const double lowerLimitLoadingAll)
    {
        if(upperLimitLoadingAul >= lowerLimitLoadingAll)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.");
        }

        return nullptr;
    }
}

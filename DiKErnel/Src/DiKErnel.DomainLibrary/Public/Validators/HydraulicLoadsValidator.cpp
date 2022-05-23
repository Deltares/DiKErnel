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

#include "HydraulicLoadsValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    unique_ptr<ValidationIssue> HydraulicLoadsValidator::WaveHeightHm0(
        const double waveHeightHm0)
    {
        if (waveHeightHm0 <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WaveHeightHm0 must be larger than 0.");
        }

        if (waveHeightHm0 <= 0.1 || waveHeightHm0 >= 10)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "WaveHeightHm0 should be in range {0.1, 10}.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> HydraulicLoadsValidator::WavePeriodTm10(
        const double wavePeriodTm10)
    {
        if (wavePeriodTm10 <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WavePeriodTm10 must be larger than 0.");
        }

        if (wavePeriodTm10 <= 0.5 || wavePeriodTm10 >= 25)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Warning, "WavePeriodTm10 should be in range {0.5, 25}.");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> HydraulicLoadsValidator::WaveAngle(
        const double waveAngle)
    {
        if (waveAngle <= -180 || waveAngle > 180)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "WaveAngle must be in range {-180, 180].");
        }

        return nullptr;
    }
}

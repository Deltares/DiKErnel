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

#include "TimeDependentInput.h"

#include "HydraulicLoadsValidator.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    TimeDependentInput::TimeDependentInput(
        const double beginTime,
        const double endTime,
        const double waterLevel,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle)
        : _beginTime(beginTime),
          _endTime(endTime),
          _waterLevel(waterLevel),
          _waveHeightHm0(waveHeightHm0),
          _wavePeriodTm10(wavePeriodTm10),
          _waveAngle(waveAngle) { }

    bool TimeDependentInput::Validate() const
    {
        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(HydraulicLoadsValidator::WaveHeightHm0(_waveHeightHm0));
        validationIssues.emplace_back(HydraulicLoadsValidator::WavePeriodTm10(_wavePeriodTm10));
        validationIssues.emplace_back(HydraulicLoadsValidator::WaveAngle(_waveAngle));

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    double TimeDependentInput::GetBeginTime() const
    {
        return _beginTime;
    }

    double TimeDependentInput::GetEndTime() const
    {
        return _endTime;
    }

    double TimeDependentInput::GetWaterLevel() const
    {
        return _waterLevel;
    }

    double TimeDependentInput::GetWaveHeightHm0() const
    {
        return _waveHeightHm0;
    }

    double TimeDependentInput::GetWavePeriodTm10() const
    {
        return _wavePeriodTm10;
    }

    double TimeDependentInput::GetWaveAngle() const
    {
        return _waveAngle;
    }
}

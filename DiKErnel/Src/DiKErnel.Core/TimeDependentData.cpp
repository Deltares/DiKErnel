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

#include "TimeDependentData.h"

#include "InvalidCalculationDataException.h"

namespace DiKErnel::Core
{
    TimeDependentData::TimeDependentData(
        const int beginTime,
        const int endTime,
        const double waterLevel,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle)
        : _beginTime(beginTime),
          _endTime(endTime),
          _waterLevel(waterLevel),
          _waveHeightHm0(waveHeightHm0),
          _wavePeriodTm10(wavePeriodTm10),
          _waveAngle(waveAngle)
    {
        if(this->_endTime <= this->_beginTime)
        {
            throw InvalidCalculationDataException("'beginTime' should be smaller than 'endTime'.");
        }
    }

    int TimeDependentData::GetBeginTime() const
    {
        return _beginTime;
    }

    int TimeDependentData::GetEndTime() const
    {
        return _endTime;
    }

    double TimeDependentData::GetWaterLevel() const
    {
        return _waterLevel;
    }

    double TimeDependentData::GetWaveHeightHm0() const
    {
        return _waveHeightHm0;
    }

    double TimeDependentData::GetWavePeriodTm10() const
    {
        return _wavePeriodTm10;
    }

    double TimeDependentData::GetWaveAngle() const
    {
        return _waveAngle;
    }
}

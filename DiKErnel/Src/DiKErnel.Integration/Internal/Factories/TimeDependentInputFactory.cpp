﻿// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "TimeDependentInputFactory.h"

#include "TimeDependentInput.h"
#include "TimeDependentInputFactoryData.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    vector<unique_ptr<ITimeDependentInput>> TimeDependentInputFactory::Create(
        const vector<reference_wrapper<TimeDependentInputFactoryData>>& timeStepDataItems)
    {
        auto timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();

        for (const auto& timeStepDataItemReference : timeStepDataItems)
        {
            const auto& timeStepDataItem = timeStepDataItemReference.get();

            timeDependentInputItems.push_back(make_unique<TimeDependentInput>(
                timeStepDataItem.GetBeginTime(), timeStepDataItem.GetEndTime(), timeStepDataItem.GetWaterLevel(),
                timeStepDataItem.GetWaveHeightHm0(), timeStepDataItem.GetWavePeriodTm10(), timeStepDataItem.GetWaveAngle()));
        }

        return timeDependentInputItems;
    }
}
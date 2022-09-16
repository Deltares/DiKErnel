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

#include "TimeDependentInputFactory.h"

#include <limits>

#include "InputFactoryException.h"
#include "TimeDependentInput.h"
#include "TimeDependentInputFactoryData.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    vector<unique_ptr<ITimeDependentInput>> TimeDependentInputFactory::Create(
        const vector<reference_wrapper<TimeDependentInputFactoryData>>& timeStepDataItems)
    {
        if (timeStepDataItems.empty())
        {
            throw InputFactoryException("At least 1 time step is required.");
        }

        auto timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();

        auto previousEndTime = numeric_limits<int>::min();

        for (const auto& timeStepDataItemReference : timeStepDataItems)
        {
            const auto& timeStepDataItem = timeStepDataItemReference.get();

            int beginTime = timeStepDataItem.GetBeginTime();
            int endTime = timeStepDataItem.GetEndTime();

            if (previousEndTime != numeric_limits<int>::min() && beginTime != previousEndTime)
            {
                throw InputFactoryException("The begin time of a successive element must equal the end time of the previous element.");
            }

            timeDependentInputItems.push_back(make_unique<TimeDependentInput>(
                beginTime, endTime, timeStepDataItem.GetWaterLevel(), timeStepDataItem.GetWaveHeightHm0(), timeStepDataItem.GetWavePeriodTm10(),
                timeStepDataItem.GetWaveAngle()));

            previousEndTime = endTime;
        }

        return timeDependentInputItems;
    }
}

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

#include "LocationDependentOutput.h"

#include <utility>

namespace DiKErnel::Core
{
    using namespace std;

    LocationDependentOutput::LocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
        : _timeDependentOutputItems(move(timeDependentOutputItems))
    {
        for (const auto& timeDependentOutput : _timeDependentOutputItems)
        {
            _timeDependentOutputItemReferences.emplace_back(*timeDependentOutput);
        }
    }

    vector<double> LocationDependentOutput::GetDamages(
        const double initialDamage) const
    {
        vector<double> cumulativeDamages;

        double cumulativeDamage = initialDamage;

        for (const auto& timeDependentOutput : _timeDependentOutputItems)
        {
            const double incrementDamage = timeDependentOutput->GetIncrementDamage();

            if (incrementDamage != numeric_limits<double>::infinity() && !isnan(incrementDamage))
            {
                cumulativeDamage += incrementDamage;
            }

            cumulativeDamages.push_back(cumulativeDamage);
        }

        return cumulativeDamages;
    }

    int LocationDependentOutput::GetTimeOfFailure(
        const double initialDamage,
        const double failureNumber,
        vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputItems) const
    {
        const auto cumulativeDamages = GetDamages(initialDamage);

        double damageAtStartOfCalculation = initialDamage;

        for (int i = 0; i < timeDependentInputItems.size(); i++)
        {
            const double damageAtEndOfCalculation = cumulativeDamages[i];

            if (damageAtStartOfCalculation < failureNumber && damageAtEndOfCalculation >= failureNumber)
            {
                return CalculateTimeOfFailure(failureNumber, timeDependentInputItems[i], _timeDependentOutputItemReferences[i],
                                              damageAtStartOfCalculation);
            }

            damageAtStartOfCalculation = damageAtEndOfCalculation;
        }

        return numeric_limits<int>::max();
    }

    const vector<reference_wrapper<TimeDependentOutput>>& LocationDependentOutput::GetTimeDependentOutputItems() const
    {
        return _timeDependentOutputItemReferences;
    }

    double LocationDependentOutput::CalculateTimeOfFailure(
        const double failureNumber,
        const std::reference_wrapper<ITimeDependentInput> timeDependentInput,
        const std::reference_wrapper<TimeDependentOutput> timeDependentOutput,
        const double damageAtStartOfCalculation)
    {
        const double incrementTime = timeDependentInput.get().GetEndTime() - timeDependentInput.get().GetBeginTime();
        const double incrementDamage = timeDependentOutput.get().GetIncrementDamage();
        const double durationInTimeStepFailure = (failureNumber - damageAtStartOfCalculation) / incrementDamage * incrementTime;

        return timeDependentInput.get().GetBeginTime() + durationInTimeStepFailure;
    }
}

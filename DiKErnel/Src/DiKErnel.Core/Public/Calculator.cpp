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

#include "Calculator.h"

#include "EventRegistry.h"

namespace DiKErnel::Core
{
    using namespace std;
    using namespace Util;

    Calculator::Calculator(
        const ICalculationInput& calculationInput)
    {
        PerformCalculation(calculationInput);
    }

    shared_ptr<DataResult<CalculationOutput>> Calculator::GetResult() const
    {
        return _result;
    }

    void Calculator::PerformCalculation(
        const ICalculationInput& calculationInput)
    {
        try
        {
            const auto& profileData = calculationInput.GetProfileData();
            const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
            const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();

            auto timeDependentOutputItems = vector<vector<unique_ptr<TimeDependentOutput>>>(locationDependentInputItems.size());

            for (auto i = 0; i < static_cast<int>(timeDependentInputItems.size()); ++i)
            {
                const auto& timeDependentInput = timeDependentInputItems.at(i).get();

                for (auto j = 0; j < static_cast<int>(locationDependentInputItems.size()); ++j)
                {
                    auto& locationDependentInput = locationDependentInputItems.at(j).get();

                    const auto initialDamage = i == 0
                                                   ? locationDependentInput.GetInitialDamage()
                                                   : timeDependentOutputItems.at(j).back()->GetDamage();

                    auto timeDependentOutput = locationDependentInput.Calculate(initialDamage, timeDependentInput, profileData);

                    timeDependentOutputItems.at(j).push_back(move(timeDependentOutput));
                }
            }

            CreateResultWithCalculationOutput(locationDependentInputItems, timeDependentOutputItems);
        }
        catch (const exception& e)
        {
            EventRegistry::Register(make_unique<Event>("An unhandled error occurred while performing the calculation. See stack trace for more "
                                                       "information:\n" + static_cast<string>(e.what()), EventType::Error));

            CreateResultWithoutCalculationOutput();
        }
    }

    void Calculator::CreateResultWithCalculationOutput(
        const vector<reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
        vector<vector<unique_ptr<TimeDependentOutput>>>& timeDependentOutputItems)
    {
        auto locationDependentOutputItems = vector<unique_ptr<LocationDependentOutput>>();

        for (auto i = 0; i < static_cast<int>(locationDependentInputItems.size()); ++i)
        {
            locationDependentOutputItems.push_back(
                locationDependentInputItems.at(i).get().GetLocationDependentOutput(move(timeDependentOutputItems.at(i))));
        }

        _result = make_shared<DataResult<CalculationOutput>>(make_unique<CalculationOutput>(move(locationDependentOutputItems)),
                                                             EventRegistry::Flush());
    }

    void Calculator::CreateResultWithoutCalculationOutput()
    {
        _result = make_shared<DataResult<CalculationOutput>>(EventRegistry::Flush());
    }
}

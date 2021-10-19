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

#include "Calculator.h"

#include <cmath>

#include "EventRegistry.h"

namespace DiKErnel::Core
{
    using namespace std;
    using namespace Util;

    Calculator::Calculator(
        ICalculationInput& calculationInput)
    {
        _calculationThread = thread(
            &Calculator::PerformCalculation,
            this,
            ref(calculationInput),
            ref(_progress),
            ref(_isFinished),
            ref(_isCancelled),
            ref(_fatalErrorOccurred));
    }

    void Calculator::WaitForCompletion()
    {
        if (_calculationThread.joinable())
        {
            _calculationThread.join();
        }
    }

    int Calculator::GetProgress() const
    {
        return static_cast<int>(round(_progress * 100));
    }

    bool Calculator::IsFinished() const
    {
        return _isFinished;
    }

    void Calculator::Cancel()
    {
        if (!_isFinished)
        {
            _isCancelled = true;
        }
    }

    bool Calculator::IsCancelled() const
    {
        return _isCancelled;
    }

    shared_ptr<Result<CalculationOutput>> Calculator::GetCalculationOutput()
    {
        unique_ptr<CalculationOutput> output = nullptr;

        if (_isFinished && !_fatalErrorOccurred)
        {
            output = move(_calculationOutput);
        }

        return make_shared<Result<CalculationOutput>>(move(output), move(_events));
    }

    void Calculator::PerformCalculation(
        const ICalculationInput& calculationInput,
        atomic<double>& progress,
        atomic<bool>& isFinished,
        const atomic<bool>& isCancelled,
        atomic<bool>& fatalErrorOccurred)
    {
        try
        {
            const auto& profileData = calculationInput.GetProfileData();
            const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
            const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();

            auto timeDependentOutputItems = vector<vector<unique_ptr<TimeDependentOutput>>>(locationDependentInputItems.size());

            const auto progressPerCalculationStep = 1.0
                    / static_cast<double>(timeDependentInputItems.size())
                    / static_cast<double>(locationDependentInputItems.size());

            for (auto i = 0; i < static_cast<int>(timeDependentInputItems.size()); ++i)
            {
                if (isCancelled)
                {
                    break;
                }

                const auto& timeDependentInput = timeDependentInputItems[i].get();

                for (auto j = 0; j < static_cast<int>(locationDependentInputItems.size()); ++j)
                {
                    if (isCancelled)
                    {
                        break;
                    }

                    auto& locationDependentInput = locationDependentInputItems[j].get();

                    const auto initialDamage = i == 0
                                                   ? locationDependentInput.GetInitialDamage()
                                                   : timeDependentOutputItems[j].back()->GetDamage();

                    auto timeDependentOutput = locationDependentInput.Calculate(initialDamage, timeDependentInput, profileData);

                    timeDependentOutputItems[j].push_back(move(timeDependentOutput));

                    progress = progress + progressPerCalculationStep;
                }
            }

            if (!isCancelled)
            {
                CreateOutput(timeDependentOutputItems);
                isFinished = true;
            }
        }
        catch (const exception& e)
        {
            EventRegistry::Register(make_unique<Event>(e.what(), EventType::Error));
            fatalErrorOccurred = true;
        }

        _events = EventRegistry::Flush();
    }

    void Calculator::CreateOutput(
        vector<vector<unique_ptr<TimeDependentOutput>>>& timeDependentOutputItems)
    {
        auto locationDependentOutputItems = vector<unique_ptr<LocationDependentOutput>>();

        for (auto& timeDependentOutputItemsPerLocation : timeDependentOutputItems)
        {
            locationDependentOutputItems.push_back(make_unique<LocationDependentOutput>(move(timeDependentOutputItemsPerLocation)));
        }

        _calculationOutput = make_unique<CalculationOutput>(move(locationDependentOutputItems));
    }
}

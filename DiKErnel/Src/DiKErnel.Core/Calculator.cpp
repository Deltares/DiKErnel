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

namespace DiKErnel::Core
{
    using namespace std;

    Calculator::Calculator(
        ICalculationInput& calculationInput)
    {
        _calculationThread = thread(
            &Calculator::PerformCalculation,
            this,
            ref(calculationInput),
            ref(_progress),
            ref(_isFinished),
            ref(_isCancelled));
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

    shared_ptr<CalculationOutput> Calculator::GetCalculationOutput() const
    {
        if (!_isFinished)
        {
            return nullptr;
        }

        return _calculationOutput;
    }

    void Calculator::PerformCalculation(
        const ICalculationInput& calculationInput,
        atomic<double>& progress,
        atomic<bool>& isFinished,
        const atomic<bool>& isCancelled)
    {
        const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
        const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();

        auto damages = vector<vector<double>>(locationDependentInputItems.size(), vector<double>());

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

                const auto startDamage = i == 0
                                             ? locationDependentInput.GetInitialDamage()
                                             : damages[j].back();

                const auto damage = locationDependentInput.Calculate(startDamage, timeDependentInput, calculationInput.GetMaximumWaveAngle());

                damages[j].push_back(damage);

                progress = progress + progressPerCalculationStep;
            }
        }

        if (!isCancelled)
        {
            CreateOutput(damages);
            isFinished = true;
        }
    }

    void Calculator::CreateOutput(
        const vector<vector<double>>& damages)
    {
        auto locationDependentOutputItems = vector<unique_ptr<LocationDependentOutput>>();

        for (const auto& locationDamages : damages)
        {
            locationDependentOutputItems.push_back(make_unique<LocationDependentOutput>(locationDamages, nullptr));
        }

        _calculationOutput = make_shared<CalculationOutput>(move(locationDependentOutputItems));
    }
}

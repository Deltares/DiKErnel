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
        CalculationInput& calculationInput)
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
        const CalculationInput& calculationInput,
        std::atomic<double>& progress,
        std::atomic<bool>& isFinished,
        const std::atomic<bool>& isCancelled)
    {
        const auto& timeDependentDataItems = calculationInput.GetTimeDependentDataItems();
        const auto& locationDependentDataItems = calculationInput.GetLocationDependentDataItems();

        _calculationOutput = InitializeOutput(locationDependentDataItems);

        const auto percentagePerCalculation = 1.0
                / static_cast<double>(timeDependentDataItems.size())
                / static_cast<double>(locationDependentDataItems.size());

        for (const auto& timeDependentData : timeDependentDataItems)
        {
            if (isCancelled)
            {
                break;
            }

            for (auto i = 0; i < static_cast<int>(locationDependentDataItems.size()); ++i)
            {
                if (isCancelled)
                {
                    break;
                }

                auto& location = locationDependentDataItems[i].get();
                auto& locationOutput = _calculationOutput->GetLocationOutputs()[i].get();
                const auto& calculatedLocationDamages = locationOutput.GetDamages();

                const auto startDamage = calculatedLocationDamages.empty()
                                             ? location.GetInitialDamage()
                                             : calculatedLocationDamages.back();

                const auto damage = location.Calculate(startDamage, timeDependentData.get(), calculationInput.GetMaximumWaveAngle());

                locationOutput.AddDamage(damage);

                progress = progress + percentagePerCalculation;
            }
        }

        if (!isCancelled)
        {
            isFinished = true;
        }
    }

    shared_ptr<CalculationOutput> Calculator::InitializeOutput(
        const vector<reference_wrapper<LocationDependentData>>& locationDependentDataItems) const
    {
        auto locationOutputs = vector<unique_ptr<LocationOutput>>();

        for (const auto& _ : locationDependentDataItems)
        {
            locationOutputs.push_back(make_unique<LocationOutput>());
        }

        return make_shared<CalculationOutput>(move(locationOutputs));
    }
}

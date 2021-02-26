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

#include "cmath"

#include "Calculator.h"

namespace DiKErnel::Core
{
    using namespace std;

    Calculator::Calculator(
        CalculationInput& calculationInput)
    {
        calculationThread = thread(
            &Calculator::PerformCalculation,
            this,
            ref(calculationInput),
            ref(progress),
            ref(isFinished),
            ref(isCancelled));
    }

    void Calculator::WaitForCompletion()
    {
        if (calculationThread.joinable())
        {
            calculationThread.join();
        }
    }

    int Calculator::GetProgress() const
    {
        return static_cast<int>(round(progress * 100));
    }

    bool Calculator::IsFinished() const
    {
        return isFinished;
    }

    void Calculator::Cancel()
    {
        if (!isFinished)
        {
            isCancelled = true;
        }
    }

    bool Calculator::IsCancelled() const
    {
        return isCancelled;
    }

    shared_ptr<CalculationOutput> Calculator::GetCalculationOutput() const
    {
        return calculationOutput;
    }

    void Calculator::PerformCalculation(
        const CalculationInput& calculationInput,
        std::atomic<double>& progress,
        std::atomic<bool>& isFinished,
        const std::atomic<bool>& isCancelled)
    {
        const auto& timeDependentDataItems = calculationInput.GetTimeDependentDataItems();
        const auto& locationDependentDataItems = calculationInput.GetLocationDependentDataItems();

        calculationOutput = InitializeOutput(locationDependentDataItems);

        const auto percentagePerCalculation = 1.0
                / static_cast<double>(timeDependentDataItems.size())
                / static_cast<double>(locationDependentDataItems.size());

        for (const auto& timeDependentData : timeDependentDataItems)
        {
            if (isCancelled)
            {
                break;
            }

            for (const auto& location : locationDependentDataItems)
            {
                if (isCancelled)
                {
                    break;
                }

                location.get().Calculate(timeDependentData.get(), calculationInput.GetMaximumWaveAngle());

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

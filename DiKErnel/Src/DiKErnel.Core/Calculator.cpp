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

namespace DiKErnel::Core
{
    using namespace std;

    Calculator::Calculator(
        CalculationInput& calculationInput)
    {
        calculationThread = thread(
            PerformCalculation,
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

    reference_wrapper<CalculationOutput> Calculator::GetCalculationOutput() const
    {
        return *calculationOutput;
    }

    void Calculator::PerformCalculation(
        CalculationInput& calculationInput,
        std::atomic<double>& progress,
        std::atomic<bool>& isFinished,
        const std::atomic<bool>& isCancelled)
    {
        auto timeDependentDataItems = calculationInput.GetTimeDependentDataItems();
        auto locationDependentDataItems = calculationInput.GetLocationDependentDataItems();

        const auto percentagePerCalculation = 1.0
                / static_cast<double>(timeDependentDataItems.size())
                / static_cast<double>(locationDependentDataItems.size());

        for (const auto& timeDependentData : timeDependentDataItems)
        {
            if (isCancelled)
            {
                break;
            }

            for (auto& location : locationDependentDataItems)
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
}

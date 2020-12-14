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
#include <atomic>
#include <thread>

namespace DiKErnel::Core
{
    Calculator::Calculator(
        std::vector<CalculationLocation*> locations,
        std::vector<int> times,
        double (*subCalculation)(double initialDamage,
            double slopeAngle,
            double relativeDensity,
            double thicknessTopLayer,
            double spectralWaveHeight,
            double spectralWavePeriod,
            double waveAngle,
            double startTime,
            double endTime))
    {
        thread = std::thread(
            PerformCalculation,
            locations,
            times,
            subCalculation,
            std::ref(progress),
            std::ref(finished),
            std::ref(cancelled));
    }

    void Calculator::WaitForCompletion()
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    int Calculator::GetProgress() const
    {
        return progress;
    }

    bool Calculator::IsFinished() const
    {
        return finished;
    }

    void Calculator::Cancel()
    {
        cancelled = true;
    }

    bool Calculator::IsCancelled() const
    {
        return cancelled;
    }

    void Calculator::PerformCalculation(
        std::vector<CalculationLocation*> locations,
        const std::vector<int> times,
        double (*subCalculation)(
            double initialDamage,
            double slopeAngle,
            double relativeDensity,
            double thicknessTopLayer,
            double spectralWaveHeight,
            double spectralWavePeriod,
            double waveAngle,
            double startTime,
            double endTime),
        std::atomic<int>& progress,
        std::atomic<bool>& finished,
        std::atomic<bool>& cancelled)
    {
        const auto numberOfLocations = locations.size();
        const auto numberOfTimeSteps = times.size();

        const auto totalSteps = numberOfLocations * numberOfTimeSteps;

        // Perform sub-calculation for all time steps
        for (auto i = 0; i < numberOfLocations; i++)
        {
            // Perform sub-calculation for all locations
            for (auto j = 0; j < numberOfTimeSteps; j++)
            {
                // Break from loop when cancelled
                if (cancelled)
                {
                    break;
                }

                // Perform the actual sub-calculation
                auto result = subCalculation(0, 0, 0, 0, 0, 0, 0, 0 ,0);

                // Update progress indicator
                progress = ceil((i * numberOfTimeSteps + j + 1.0) / totalSteps * 100);
            }
        }

        // Mark calculation as finished
        finished = true;
    }
}

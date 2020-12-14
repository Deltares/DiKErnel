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
        std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>> timeSteps,
        double (*subCalculation)(
            double initialDamage,
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
            timeSteps,
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
        std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>> timeSteps,
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
        const auto totalSteps = locations.size() * timeSteps.size();

        // Perform sub-calculation for all time steps
        for (auto i = 0; i < timeSteps.size(); i++)
        {
            // Perform sub-calculation for all locations
            for (auto j = 0; j < locations.size(); j++)
            {
                // Break from loop when cancelled
                if (cancelled)
                {
                    break;
                }

                auto* revetment = locations[j]->GetRevetment();
                auto* profileSchematization = locations[j]->GetProfileSchematization();

                auto* boundaryCondition = std::get<2>(timeSteps[i]);

                auto result = subCalculation(
                    revetment->GetInitialDamage(),
                    profileSchematization->GetTanA(),
                    revetment->GetRelativeDensity(),
                    revetment->GetThicknessTopLayer(),
                    boundaryCondition->GetWaveHeightHm0(),
                    boundaryCondition->GetWavePeriodTm10(),
                    boundaryCondition->GetWaveAngle(),
                    std::get<0>(timeSteps[i]),
                    std::get<1>(timeSteps[i]));

                // Update progress indicator
                progress = ceil((i * timeSteps.size() + j + 1.0) / totalSteps * 100);
            }
        }

        // Mark calculation as finished
        finished = true;
    }
}

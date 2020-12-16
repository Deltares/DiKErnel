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
#include <cmath>
#include <functional>
#include <map>
#include <thread>

namespace DiKErnel::Core
{
    Calculator::Calculator(
        const InputData* inputData,
        const std::function<double(
            double initialDamage,
            double slopeAngle,
            double relativeDensity,
            double thicknessTopLayer,
            double spectralWaveHeight,
            double spectralWavePeriod,
            double waveAngle,
            double startTime,
            double endTime,
            double ap,
            double bp,
            double cp,
            double np,
            double as,
            double bs,
            double cs,
            double ns,
            double waveAngleMaximum,
            double similarityParameterThreshold)>& subCalculation)
    {
        const auto locations = inputData->GetLocations();
        const auto times = inputData->GetCalculationData()->GetTimes();
        const auto* hydraulicLoads = inputData->GetHydraulicLoads();
        const auto boundariesPerTimeStep = hydraulicLoads->GetBoundaryConditionsPerTimeStep();

        auto timeSteps = std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>>();

        for (auto i = 0; i < times.size() - 1; i++)
        {
            timeSteps.emplace_back(times[i], times[i + 1], boundariesPerTimeStep[i]);
        }

        thread = std::thread(
            PerformCalculation,
            locations,
            timeSteps,
            hydraulicLoads,
            subCalculation,
            std::ref(progress),
            std::ref(finished),
            std::ref(cancelled),
            std::ref(results));
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

    std::map<CalculationLocation*, std::vector<std::tuple<double, double>>> Calculator::GetResults() const
    {
        return results;
    }

    void Calculator::PerformCalculation(
        const std::vector<CalculationLocation*>& locations,
        const std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>>& timeSteps,
        const HydraulicLoads* hydraulicLoads,
        const std::function<double(
            double initialDamage,
            double slopeAngle,
            double relativeDensity,
            double thicknessTopLayer,
            double spectralWaveHeight,
            double spectralWavePeriod,
            double waveAngle,
            double startTime,
            double endTime,
            double ap,
            double bp,
            double cp,
            double np,
            double as,
            double bs,
            double cs,
            double ns,
            double waveAngleMaximum,
            double similarityParameterThreshold)>& subCalculation,
        std::atomic<int>& progress,
        std::atomic<bool>& finished,
        const std::atomic<bool>& cancelled,
        std::map<CalculationLocation*, std::vector<std::tuple<double, double>>>& results)
    {
        const auto totalSteps = locations.size() * timeSteps.size();

        for (auto* location : locations)
        {
            results[location] = std::vector<std::tuple<double, double>>();
            results[location].emplace_back(std::get<0>(timeSteps[0]), location->GetRevetment()->GetInitialDamage());
        }

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

                const auto* revetment = locations[j]->GetRevetment();
                const auto* profileSchematization = locations[j]->GetProfileSchematization();
                const auto* boundaryCondition = std::get<2>(timeSteps[i]);

                const auto result = subCalculation(
                    std::get<1>(results[locations[j]].back()),
                    profileSchematization->GetTanA(),
                    revetment->GetRelativeDensity(),
                    revetment->GetThicknessTopLayer(),
                    boundaryCondition->GetWaveHeightHm0(),
                    boundaryCondition->GetWavePeriodTm10(),
                    boundaryCondition->GetWaveAngle(),
                    std::get<0>(timeSteps[i]),
                    std::get<1>(timeSteps[i]),
                    revetment->GetCoefficientPlungingAp(),
                    revetment->GetCoefficientPlungingBp(),
                    revetment->GetCoefficientPlungingCp(),
                    revetment->GetCoefficientPlungingNp(),
                    revetment->GetCoefficientSurgingAs(),
                    revetment->GetCoefficientSurgingBs(),
                    revetment->GetCoefficientSurgingCs(),
                    revetment->GetCoefficientSurgingNs(),
                    hydraulicLoads->GetWaveAngleMaximum(),
                    revetment->GetSimilarityParameterThreshold());

                results[locations[j]].emplace_back(std::get<1>(timeSteps[i]), result);

                // Update progress indicator
                progress = std::ceil((i * timeSteps.size() + j + 1.0) / totalSteps * 100);
            }
        }

        // Mark calculation as finished
        finished = true;
    }
}

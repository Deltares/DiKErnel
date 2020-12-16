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
#include <iostream>
#include <map>
#include <thread>

namespace DiKErnel::Core
{
    Calculator::Calculator(
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
            double np,
            double bp,
            double cp,
            double as,
            double ns,
            double bs,
            double cs,
            double waveAngleMaximum,
            double xiFactor)>& subCalculation)
    {
        thread = std::thread(
            PerformCalculation,
            locations,
            timeSteps,
            hydraulicLoads,
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
            double np,
            double bp,
            double cp,
            double as,
            double ns,
            double bs,
            double cs,
            double waveAngleMaximum,
            double xiFactor)>& subCalculation,
        std::atomic<int>& progress,
        std::atomic<bool>& finished,
        const std::atomic<bool>& cancelled)
    {
        const auto totalSteps = locations.size() * timeSteps.size();

        std::map<CalculationLocation*, std::vector<std::tuple<double, double>>> damageLookup;

        for (auto* location : locations)
        {
            damageLookup[location] = std::vector<std::tuple<double, double>>();
            damageLookup[location].emplace_back(std::get<0>(timeSteps[0]), location->GetRevetment()->GetInitialDamage());
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
                    std::get<1>(damageLookup[locations[j]].back()),
                    profileSchematization->GetTanA(),
                    revetment->GetRelativeDensity(),
                    revetment->GetThicknessTopLayer(),
                    boundaryCondition->GetWaveHeightHm0(),
                    boundaryCondition->GetWavePeriodTm10(),
                    boundaryCondition->GetWaveAngle(),
                    std::get<0>(timeSteps[i]),
                    std::get<1>(timeSteps[i]),
                    revetment->GetCoefficientPlungingAp(),
                    revetment->GetCoefficientPlungingNp(),
                    revetment->GetCoefficientPlungingBp(),
                    revetment->GetCoefficientPlungingCp(),
                    revetment->GetCoefficientSurgingAs(),
                    revetment->GetCoefficientSurgingNs(),
                    revetment->GetCoefficientSurgingBs(),
                    revetment->GetCoefficientSurgingCs(),
                    hydraulicLoads->GetWaveAngleMaximum(),
                    revetment->GetSimilarityParameterThreshold());

                damageLookup[locations[j]].emplace_back(std::get<1>(timeSteps[i]), result);

                // Update progress indicator
                progress = std::ceil((i * timeSteps.size() + j + 1.0) / totalSteps * 100);
            }
        }

        for (const auto& [location, damageLookup] : damageLookup)
        {
            std::cout << std::endl;
            std::cout << "-> Location: " << location->GetName() << std::endl;
            std::cout << "-> Damages: " << std::endl;

            for (auto lookup : damageLookup)
            {
                std::cout << "\t -> Time: " << std::get<0>(lookup) << ", Damage: " << std::get<1>(lookup) << "." << std::endl;
            }
        }

        // Mark calculation as finished
        finished = true;
    }
}

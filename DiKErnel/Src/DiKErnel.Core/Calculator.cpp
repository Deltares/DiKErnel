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
    using namespace KernelWrapper::Json;

    Calculator::Calculator(
        const InputData& inputData,
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
        const auto locations = inputData.GetLocations();
        const auto& times = inputData.GetCalculationData().GetTimes();
        const auto* hydraulicLoads = inputData.GetHydraulicLoads();
        const auto boundariesPerTimeStep = hydraulicLoads->GetBoundaryConditionsPerTimeStep();

        auto timeSteps = std::vector<std::tuple<int, int, std::reference_wrapper<BoundaryConditionsPerTimeStep>>>();

        for (auto i = 0; i < times.size() - 1; i++)
        {
            timeSteps.emplace_back(times[i], times[i + 1], boundariesPerTimeStep[i]);
        }

        calculationThread = std::thread(
            PerformCalculation,
            locations,
            timeSteps,
            hydraulicLoads,
            subCalculation,
            std::ref(progress),
            std::ref(isFinished),
            std::ref(isCancelled),
            std::ref(outputData));
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
        return static_cast<int>(std::ceil(progress * 100));
    }

    bool Calculator::IsFinished() const
    {
        return isFinished;
    }

    void Calculator::Cancel()
    {
        isCancelled = true;
    }

    bool Calculator::IsCancelled() const
    {
        return isCancelled;
    }

    std::unique_ptr<OutputData> Calculator::GetOutputData() const
    {
        std::vector<std::unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        if (isFinished)
        {
            for (const auto& [location, damageAtTimeSteps] : outputData)
            {
                calculationLocationsOutput.push_back(
                    std::make_unique<CalculationLocationOutput>(
                        location->GetName(),
                        std::make_unique<RevetmentOutput>(std::get<1>(damageAtTimeSteps.back()))));
            }
        }

        return std::make_unique<OutputData>(std::move(calculationLocationsOutput));
    }

    void Calculator::PerformCalculation(
        const std::vector<CalculationLocation*>& locations,
        const std::vector<std::tuple<int, int, std::reference_wrapper<BoundaryConditionsPerTimeStep>>>& timeSteps,
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
        std::atomic<double>& progress,
        std::atomic<bool>& finished,
        const std::atomic<bool>& cancelled,
        std::map<CalculationLocation*, std::vector<std::tuple<double, double>>>& results)
    {
        const auto percentagePerCalculation = 1.0 / static_cast<double>(timeSteps.size()) / static_cast<double>(locations.size());

        for (auto* location : locations)
        {
            results[location] = std::vector<std::tuple<double, double>>();
            results[location].emplace_back(std::get<0>(timeSteps[0]), location->GetRevetment().GetInitialDamage());
        }

        for (const auto& timeStep : timeSteps)
        {
            if (cancelled)
            {
                break;
            }

            for (auto* location : locations)
            {
                if (cancelled)
                {
                    break;
                }

                PerformCalculationForTimeStepAndLocation(timeStep, location, hydraulicLoads, subCalculation, results);

                progress = progress + percentagePerCalculation;
            }
        }

        finished = true;
    }

    void Calculator::PerformCalculationForTimeStepAndLocation(
        std::tuple<int, int, std::reference_wrapper<BoundaryConditionsPerTimeStep>> currentTimeStep,
        CalculationLocation* currentLocation,
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
        std::map<CalculationLocation*, std::vector<std::tuple<double, double>>>& results)
    {
        const auto& revetment = currentLocation->GetRevetment();
        const auto& profileSchematization = currentLocation->GetProfileSchematization();
        const auto& boundaryCondition = std::get<2>(currentTimeStep).get();

        const auto result = subCalculation(
            std::get<1>(results[currentLocation].back()),
            profileSchematization.GetTanA(),
            revetment.GetRelativeDensity(),
            revetment.GetThicknessTopLayer(),
            boundaryCondition.GetWaveHeightHm0(),
            boundaryCondition.GetWavePeriodTm10(),
            boundaryCondition.GetWaveAngle(),
            std::get<0>(currentTimeStep),
            std::get<1>(currentTimeStep),
            revetment.GetCoefficientPlungingAp(),
            revetment.GetCoefficientPlungingBp(),
            revetment.GetCoefficientPlungingCp(),
            revetment.GetCoefficientPlungingNp(),
            revetment.GetCoefficientSurgingAs(),
            revetment.GetCoefficientSurgingBs(),
            revetment.GetCoefficientSurgingCs(),
            revetment.GetCoefficientSurgingNs(),
            hydraulicLoads->GetWaveAngleMaximum(),
            revetment.GetSimilarityParameterThreshold());

        results[currentLocation].emplace_back(std::get<1>(currentTimeStep), result);
    }
}

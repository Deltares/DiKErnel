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
    using namespace KernelWrapper::Json;

    Calculator::Calculator(
        const InputData& inputData,
        const function<double(
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
        : locations(inputData.GetLocations())
    {
        const auto& times = inputData.GetCalculationData().GetTimes();
        const auto& hydraulicLoads = inputData.GetHydraulicLoads();
        const auto& boundariesPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

        auto timeSteps = vector<tuple<int, int, reference_wrapper<BoundaryConditionsPerTimeStep>>>();

        for (auto i = 0; i < static_cast<int>(times.size()) - 1; i++)
        {
            timeSteps.emplace_back(times[i], times[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) + 1], boundariesPerTimeStep[i]);
        }

        calculationThread = thread(
            PerformCalculation,
            ref(locations),
            ref(timeSteps),
            ref(hydraulicLoads),
            ref(subCalculation),
            ref(progress),
            ref(isFinished),
            ref(isCancelled),
            ref(outputData));
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
        return static_cast<int>(ceil(progress * 100));
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

    unique_ptr<OutputData> Calculator::GetOutputData() const
    {
        vector<unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        if (isFinished)
        {
            for (auto i = 0; i < static_cast<int>(locations.size()); i++)
            {
                calculationLocationsOutput.push_back(
                    make_unique<CalculationLocationOutput>(
                        locations[i].get().GetName(),
                        make_unique<RevetmentOutput>(
                            get<1>(outputData[i].back()))));
            }
        }

        return make_unique<OutputData>(move(calculationLocationsOutput));
    }

    void Calculator::PerformCalculation(
        const vector<reference_wrapper<CalculationLocation>>& locations,
        const vector<tuple<int, int, reference_wrapper<BoundaryConditionsPerTimeStep>>>& timeSteps,
        const HydraulicLoads& hydraulicLoads,
        const function<double(
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
        atomic<double>& progress,
        atomic<bool>& finished,
        const atomic<bool>& cancelled,
        vector<vector<tuple<double, double>>>& outputData)
    {
        const auto percentagePerCalculation = 1.0 / static_cast<double>(timeSteps.size()) / static_cast<double>(locations.size());

        for (const auto& location : locations)
        {
            vector<tuple<double, double>> damage;

            damage.emplace_back(get<0>(timeSteps[0]), location.get().GetRevetment().GetInitialDamage());

            outputData.emplace_back(damage);
        }

        for (const auto& timeStep : timeSteps)
        {
            if (cancelled)
            {
                break;
            }

            for (auto i = 0; i < locations.size(); i++)
            {
                if (cancelled)
                {
                    break;
                }

                PerformCalculationForTimeStepAndLocation(timeStep, locations[i].get(), hydraulicLoads, subCalculation, outputData[i]);

                progress = progress + percentagePerCalculation;
            }
        }

        finished = true;
    }

    void Calculator::PerformCalculationForTimeStepAndLocation(
        const tuple<int, int, reference_wrapper<BoundaryConditionsPerTimeStep>>& currentTimeStep,
        const CalculationLocation& currentLocation,
        const HydraulicLoads& hydraulicLoads,
        const function<double(
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
        vector<tuple<double, double>>& outputData)
    {
        const auto& revetment = currentLocation.GetRevetment();
        const auto& profileSchematization = currentLocation.GetProfileSchematization();
        const auto& boundaryCondition = get<2>(currentTimeStep).get();

        const auto result = subCalculation(
            get<1>(outputData.back()),
            profileSchematization.GetTanA(),
            revetment.GetRelativeDensity(),
            revetment.GetThicknessTopLayer(),
            boundaryCondition.GetWaveHeightHm0(),
            boundaryCondition.GetWavePeriodTm10(),
            boundaryCondition.GetWaveAngle(),
            get<0>(currentTimeStep),
            get<1>(currentTimeStep),
            revetment.GetCoefficientPlungingAp(),
            revetment.GetCoefficientPlungingBp(),
            revetment.GetCoefficientPlungingCp(),
            revetment.GetCoefficientPlungingNp(),
            revetment.GetCoefficientSurgingAs(),
            revetment.GetCoefficientSurgingBs(),
            revetment.GetCoefficientSurgingCs(),
            revetment.GetCoefficientSurgingNs(),
            hydraulicLoads.GetWaveAngleMaximum(),
            revetment.GetSimilarityParameterThreshold());

        outputData.emplace_back(get<1>(currentTimeStep), result);
    }
}

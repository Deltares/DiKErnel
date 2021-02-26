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

#include "DeprecatedCalculator.h"

#include <cmath>

namespace DiKErnel::Core
{
    using namespace KernelWrapper::Json;
    using namespace std;

    DeprecatedCalculator::DeprecatedCalculator(
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
        : _locations(inputData.GetLocations())
    {
        const auto& times = inputData.GetCalculationData().GetTimes();
        const auto& hydraulicLoads = inputData.GetHydraulicLoads();
        const auto& boundariesPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

        auto timeSteps = vector<tuple<int, int, reference_wrapper<BoundaryConditionsPerTimeStep>>>();

        for (auto i = 0; i < static_cast<int>(times.size()) - 1; i++)
        {
            timeSteps.emplace_back(times[i], times[static_cast<vector<int, allocator<int>>::size_type>(i) + 1], boundariesPerTimeStep[i]);
        }

        _calculationThread = thread(
            PerformCalculation,
            ref(_locations),
            timeSteps,
            ref(hydraulicLoads),
            subCalculation,
            ref(_progress),
            ref(_isFinished),
            ref(_isCancelled),
            ref(_outputData));
    }

    void DeprecatedCalculator::WaitForCompletion()
    {
        if (_calculationThread.joinable())
        {
            _calculationThread.join();
        }
    }

    int DeprecatedCalculator::GetProgress() const
    {
        return static_cast<int>(round(_progress * 100));
    }

    bool DeprecatedCalculator::IsFinished() const
    {
        return _isFinished;
    }

    void DeprecatedCalculator::Cancel()
    {
        if (!_isFinished)
        {
            _isCancelled = true;
        }
    }

    bool DeprecatedCalculator::IsCancelled() const
    {
        return _isCancelled;
    }

    unique_ptr<OutputData> DeprecatedCalculator::GetOutputData() const
    {
        vector<unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        if (_isFinished)
        {
            for (auto i = 0; i < static_cast<int>(_locations.size()); i++)
            {
                const auto& outputDataForLocation = _outputData[i];

                vector<double> damagesForLocation;
                for (const auto& [time, damage] : outputDataForLocation)
                {
                    damagesForLocation.push_back(damage);
                }

                calculationLocationsOutput.push_back(
                    make_unique<CalculationLocationOutput>(
                        _locations[i].get().GetName(),
                        make_unique<RevetmentOutput>(
                            damagesForLocation)));
            }
        }

        return make_unique<OutputData>(move(calculationLocationsOutput));
    }

    void DeprecatedCalculator::PerformCalculation(
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
        atomic<bool>& isFinished,
        const atomic<bool>& isCancelled,
        vector<vector<tuple<double, double>>>& outputData)
    {
        const auto percentagePerCalculation = 1.0 / static_cast<double>(timeSteps.size()) / static_cast<double>(locations.size());

        for (const auto& location : locations)
        {
            vector<tuple<double, double>> damage;

            damage.emplace_back(get<0>(timeSteps[0]), location.get().GetDamageVariables().GetInitialDamage());

            outputData.emplace_back(damage);
        }

        for (const auto& timeStep : timeSteps)
        {
            if (isCancelled)
            {
                break;
            }

            for (auto i = 0; i < static_cast<int>(locations.size()); i++)
            {
                if (isCancelled)
                {
                    break;
                }

                PerformCalculationForTimeStepAndLocation(timeStep, locations[i].get(), hydraulicLoads, subCalculation, outputData[i]);

                progress = progress + percentagePerCalculation;
            }
        }

        if (!isCancelled)
        {
            isFinished = true;
        }
    }

    void DeprecatedCalculator::PerformCalculationForTimeStepAndLocation(
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

        const auto damage = subCalculation(
            get<1>(outputData.back()),
            profileSchematization.GetTanA(),
            revetment.GetRelativeDensity(),
            revetment.GetThicknessTopLayer(),
            boundaryCondition.GetWaveHeightHm0(),
            boundaryCondition.GetWavePeriodTm10(),
            boundaryCondition.GetWaveAngle(),
            get<0>(currentTimeStep),
            get<1>(currentTimeStep),
            revetment.GetPlungingCoefficientA(),
            revetment.GetPlungingCoefficientB(),
            revetment.GetPlungingCoefficientC(),
            revetment.GetPlungingCoefficientN(),
            revetment.GetSurgingCoefficientA(),
            revetment.GetSurgingCoefficientB(),
            revetment.GetSurgingCoefficientC(),
            revetment.GetSurgingCoefficientN(),
            hydraulicLoads.GetWaveAngleMaximum(),
            revetment.GetSimilarityParameterThreshold());

        outputData.emplace_back(get<1>(currentTimeStep), damage);
    }
}

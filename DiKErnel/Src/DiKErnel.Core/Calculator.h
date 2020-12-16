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

#pragma once
#include <atomic>
#include <functional>
#include <map>
#include <thread>
#include <vector>

#include "CalculationLocation.h"
#include "HydraulicLoads.h"
#include "InputData.h"
#include "OutputData.h"

namespace DiKErnel::Core
{
    using namespace KernelWrapper::Json;

    extern int waitTime;

    /*!
     * \brief Class responsible for performing calculations.
     */
    class Calculator
    {
        public:
            explicit Calculator(
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
                    double similarityParameterThreshold)>& subCalculation);

            void WaitForCompletion();

            int GetProgress() const;

            bool IsFinished() const;

            void Cancel();

            bool IsCancelled() const;

            std::unique_ptr<OutputData> GetOutputData() const;

        private:
            std::thread thread;
            std::atomic<double> progress = 0;
            std::atomic<bool> cancelled = false;
            std::atomic<bool> finished = false;
            std::map<CalculationLocation*, std::vector<std::tuple<double, double>>> results;

            static void PerformCalculation(
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
                std::atomic<double>& progress,
                std::atomic<bool>& finished,
                const std::atomic<bool>& cancelled,
                std::map<CalculationLocation*, std::vector<std::tuple<double, double>>>& results);

            static void PerformCalculationForLocationAndTimeStep(
                std::tuple<int, int, BoundaryConditionsPerTimeStep*> currentTimeStep,
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
                std::map<CalculationLocation*, std::vector<std::tuple<double, double>>>& results);
    };
}

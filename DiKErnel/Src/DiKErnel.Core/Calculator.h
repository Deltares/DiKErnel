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
#include <thread>
#include <vector>

#include "CalculationLocation.h"
#include "HydraulicLoads.h"

using namespace DiKErnel::KernelWrapper::Json;

namespace DiKErnel::Core
{
    /*!
     * \brief Class responsible for performing calculations.
     */
    class Calculator
    {
        public:
            explicit Calculator(
                const std::vector<CalculationLocation*>& locations,
                const std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>>& timeSteps,
                double (*subCalculation)(
                    double initialDamage,
                    double slopeAngle,
                    double relativeDensity,
                    double thicknessTopLayer,
                    double spectralWaveHeight,
                    double spectralWavePeriod,
                    double waveAngle,
                    double startTime,
                    double endTime));

            void WaitForCompletion();

            int GetProgress() const;

            bool IsFinished() const;

            void Cancel();

            bool IsCancelled() const;

        private:
            std::thread thread;
            std::atomic<int> progress = 0;
            std::atomic<bool> cancelled = false;
            std::atomic<bool> finished = false;

            static void PerformCalculation(
                const std::vector<CalculationLocation*>& locations,
                const std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>>& timeSteps,
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
                std::atomic<bool>& cancelled);
    };
}

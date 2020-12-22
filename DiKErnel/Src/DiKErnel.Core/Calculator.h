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
    /*!
     * \brief Class responsible for performing calculations on a separate thread.
     */
    class Calculator
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param inputData
             *        The input data of the calculation.
             * \param subCalculation
             *        The sub-calculation to perform.
             */
            explicit Calculator(
                const KernelWrapper::Json::InputData& inputData,
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

            /*!
             * \brief Handle that enables a calling instance to wait for the calculation to
             *        complete.
             */
            void WaitForCompletion();

            /*!
             * \brief Gets the current progress of the calculation.
             * \return The current progress of the calculation.
             *         Unit = [%]
             */
            int GetProgress() const;

            /*!
             * \brief Gets whether or not the calculation is finished.
             * \return Whether or not the calculation is finished.
             */
            bool IsFinished() const;

            /*!
             * \brief Cancels the current calculation when it is not finished yet.
             */
            void Cancel();

            /*!
             * \brief Gets whether or not the calculation is cancelled.
             * \return Whether or not the calculation is cancelled.
             */
            bool IsCancelled() const;

            /*!
             * \brief Gets the output data of the calculation.
             * \return The output data of the calculation when the calculation is finished, null
             *         otherwise.
             */
            std::unique_ptr<KernelWrapper::Json::OutputData> GetOutputData() const;

        private:
            std::thread calculationThread;
            std::atomic<double> progress = 0;
            std::atomic<bool> isCancelled = false;
            std::atomic<bool> isFinished = false;
            std::map<std::reference_wrapper<KernelWrapper::Json::CalculationLocation>, std::vector<std::tuple<double, double>>> outputData;

            static void PerformCalculation(
                const std::vector<std::reference_wrapper<KernelWrapper::Json::CalculationLocation>>&,
                const std::vector<std::tuple<int, int, std::reference_wrapper<KernelWrapper::Json::BoundaryConditionsPerTimeStep>>>&,
                const KernelWrapper::Json::HydraulicLoads&,
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
                    double similarityParameterThreshold)>&,
                std::atomic<double>&,
                std::atomic<bool>&,
                const std::atomic<bool>&,
                std::map<KernelWrapper::Json::CalculationLocation*, std::vector<std::tuple<double, double>>>&);

            static void PerformCalculationForTimeStepAndLocation(
                std::tuple<int, int, std::reference_wrapper<KernelWrapper::Json::BoundaryConditionsPerTimeStep>>,
                KernelWrapper::Json::CalculationLocation&,
                const KernelWrapper::Json::HydraulicLoads&,
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
                    double similarityParameterThreshold)>&,
                std::map<KernelWrapper::Json::CalculationLocation*, std::vector<std::tuple<double, double>>>&);
    };
}

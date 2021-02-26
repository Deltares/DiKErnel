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

#include "CalculationInput.h"
#include "CalculationOutput.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class responsible for performing calculations on a separate thread.
     */
    class Calculator
    {
        public:
            /*!
             * \brief Create a new instance.
             * \param calculationInput
             *        The data used in the calculation.
             */
            explicit Calculator(
                CalculationInput& calculationInput);

            /*!
             * \brief Handle that enables a calling instance to wait for the calculation to
             *        complete.
             */
            void WaitForCompletion();

            /*!
             * \brief Gets the current progress of the calculation.
             * \return The current progress of the calculation.
             *         Unit = [%]
             * \remarks Also returns the current progress when the calculation is cancelled.
             */
            int GetProgress() const;

            /*!
             * \brief Gets whether or not the calculation is finished.
             * \return Whether or not the calculation is finished.
             */
            bool IsFinished() const;

            /*!
             * \brief Cancels the calculation.
             * \remarks A calculation can only be cancelled when it is not finished yet.
             */
            void Cancel();

            /*!
             * \brief Gets whether or not the calculation is cancelled.
             * \return Whether or not the calculation is cancelled.
             */
            bool IsCancelled() const;

            /*!
             * \brief Gets the output of the calculation.
             * \return The output of the calculation.
             */
            std::shared_ptr<CalculationOutput> GetCalculationOutput() const;

        private:
            std::thread _calculationThread;
            std::atomic<double> _progress = 0;
            std::atomic<bool> _isCancelled = false;
            std::atomic<bool> _isFinished = false;
            std::shared_ptr<CalculationOutput> _calculationOutput;

            void PerformCalculation(
                const CalculationInput& calculationInput,
                std::atomic<double>& progress,
                std::atomic<bool>& isFinished,
                const std::atomic<bool>& isCancelled);

            std::shared_ptr<CalculationOutput> InitializeOutput(
                const std::vector<std::reference_wrapper<LocationDependentData>>& locationDependentDataItems) const;
    };
}

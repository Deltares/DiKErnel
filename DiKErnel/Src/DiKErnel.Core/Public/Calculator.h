// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include <thread>

#include "CalculationOutput.h"
#include "DataResult.h"
#include "ICalculationInput.h"

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
             * \param calculationInput
             *        The input used in the calculation.
             */
            explicit Calculator(
                const ICalculationInput& calculationInput);

            /*!
             * \brief Handle that enables a calling instance to wait for the calculation to
             *        complete.
             */
            void WaitForCompletion();

            /*!
             * \brief Gets the result of the calculator.
             * \return The result of the operation after being finished successfully, cancelled or
             *         finished in error. When the calculation is still running, a nullptr is
             *         returned.
             */
            [[nodiscard]]
            std::shared_ptr<Util::DataResult<CalculationOutput>> GetResult() const;

        private:
            std::jthread _calculationThread;
            std::shared_ptr<Util::DataResult<CalculationOutput>> _result = nullptr;

            void PerformCalculation(
                const ICalculationInput& calculationInput);

            void CreateResultWithCalculationOutput(
                const std::vector<std::reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
                std::vector<std::vector<std::unique_ptr<TimeDependentOutput>>>& timeDependentOutputItems);

            void CreateResultWithoutCalculationOutput();
    };
}

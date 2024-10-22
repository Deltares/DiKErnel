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

#include "CalculationMode.h"
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
             * \brief Creates a new instance and directly starts the calculation.
             * \param calculationInput
             *        The input used in the calculation.
             */
            explicit Calculator(
                const ICalculationInput& calculationInput,
                CalculationMode locationCalculationMode = CalculationMode::Sequential,
                CalculationMode timeStepCalculationMode = CalculationMode::Sequential);

            /*!
             * \brief Gets the result of the calculator.
             * \return The result of the operation after being finished successfully, cancelled or
             *         finished in error. When the calculation is still running, a nullptr is
             *         returned.
             */
            [[nodiscard]]
            std::shared_ptr<Util::DataResult<CalculationOutput>> GetResult() const;

        private:
            std::shared_ptr<Util::DataResult<CalculationOutput>> _result = nullptr;

            void PerformCalculation(
                const ICalculationInput& calculationInput,
                CalculationMode locationCalculationMode,
                CalculationMode timeStepCalculationMode);

            static void CalculateTimeStepsForLocations(
                const IProfileData& profileData,
                const std::vector<std::reference_wrapper<ITimeDependentInput>>& timeDependentInputItems,
                const std::vector<std::reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
                std::vector<std::vector<std::unique_ptr<TimeDependentOutput>>>& timeDependentOutputItems,
                CalculationMode locationCalculationMode,
                CalculationMode timeStepCalculationMode);

            static void CalculateTimeStepsForLocation(
                const IProfileData& profileData,
                const std::vector<std::reference_wrapper<ITimeDependentInput>>& timeDependentInputItems,
                ILocationDependentInput& locationDependentInput,
                std::vector<std::unique_ptr<TimeDependentOutput>>& timeDependentOutputItemsForLocation,
                CalculationMode timeStepCalculationMode);

            void CreateResultWithCalculationOutput(
                const std::vector<std::reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
                std::vector<std::vector<std::unique_ptr<TimeDependentOutput>>>& timeDependentOutputItems);

            void CreateResultWithoutCalculationOutput();
    };
}

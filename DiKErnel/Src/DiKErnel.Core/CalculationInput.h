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

#include <memory>
#include <vector>

#include "ILocationCalculationInput.h"
#include "TimeStep.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing all data that is needed to perform a calculation.
     */
    class CalculationInput
    {
        public:
            /*!
             * \brief Create a new instance.
             * \param locations
             *        The locations to perform the calculations for.
             * \param timeSteps
             *        The time steps to perform the calculations for.
             */
            explicit CalculationInput(
                std::vector<std::unique_ptr<ILocationCalculationInput>> locations,
                std::vector<std::unique_ptr<TimeStep>> timeSteps
            );

            /*!
             * \brief Gets the locations to perform the calculations for.
             * \return The locations to perform the calculations for.
             */
            const std::vector<std::reference_wrapper<ILocationCalculationInput>>& GetLocations() const;

            /*!
             * \brief Gets the time steps to perform the calculations for.
             * \return The time steps to perform the calculations for.
             */
            const std::vector<std::reference_wrapper<TimeStep>>& GetTimeSteps() const;

        private:
            std::vector<std::unique_ptr<ILocationCalculationInput>> locations;
            std::vector<std::unique_ptr<TimeStep>> timeSteps;

            std::vector<std::reference_wrapper<ILocationCalculationInput>> locationsReferences;
            std::vector<std::reference_wrapper<TimeStep>> timeStepsReferences;
    };
}

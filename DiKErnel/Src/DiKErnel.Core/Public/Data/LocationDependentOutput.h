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

#include <memory>
#include <vector>

#include "ITimeDependentInput.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing all location dependent output of a location.
     */
    class LocationDependentOutput
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~LocationDependentOutput() = default;

            /*!
             * \brief Gets the calculated damages.
             * \return The calculated damages.
             */
            [[nodiscard]]
            std::vector<double> GetDamages(
                double initialDamage) const;

            /*!
             * \brief Gets the calculated time of failure.
             * \return The calculated time of failure.
             */
            [[nodiscard]]
            double GetTimeOfFailure(
                double initialDamage,
                double failureNumber,
                const std::vector<std::reference_wrapper<ITimeDependentInput>>& timeDependentInputItems) const;

            /*!
             * \brief Gets the time dependent output items.
             * \return The time dependent output items.
             */
            [[nodiscard]]
            const std::vector<std::reference_wrapper<TimeDependentOutput>>& GetTimeDependentOutputItems() const;

        protected:
            /*!
             * \brief Creates a new instance.
             * \param timeDependentOutputItems
             *        The time dependent output items of the location.
             */
            explicit LocationDependentOutput(
                std::vector<std::unique_ptr<TimeDependentOutput>> timeDependentOutputItems);

            virtual double CalculateTimeOfFailure(
                double failureNumber,
                std::reference_wrapper<ITimeDependentInput> timeDependentInput,
                std::reference_wrapper<TimeDependentOutput> timeDependentOutput,
                double damageAtStartOfCalculation) const;

        private:
            std::vector<std::unique_ptr<TimeDependentOutput>> _timeDependentOutputItems;
            std::vector<std::reference_wrapper<TimeDependentOutput>> _timeDependentOutputItemReferences;
    };
}

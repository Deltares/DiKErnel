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
             * \brief Creates a new instance.
             * \param timeDependentOutputItems
             *        The time dependent output items of the location.
             */
            explicit LocationDependentOutput(
                std::vector<std::unique_ptr<TimeDependentOutput>> timeDependentOutputItems);

            /*!
             * \brief Gets the damages.
             * \return The damages.
             */
            const std::vector<double>& GetDamages() const;

            /*!
             * \brief Gets the time of failure.
             * \return The time of failure.
             */
            const int* GetTimeOfFailure() const;

            /*!
             * \brief Gets the time dependent output items.
             * \return The time dependent output items.
             */
            const std::vector<std::reference_wrapper<TimeDependentOutput>>& GetTimeDependentOutputItems() const;

        private:
            std::vector<double> _damages = std::vector<double>();
            std::unique_ptr<int> _timeOfFailure;
            std::vector<std::unique_ptr<TimeDependentOutput>> _timeDependentOutputItems;
            std::vector<std::reference_wrapper<TimeDependentOutput>> _timeDependentOutputItemReferences;
    };
}

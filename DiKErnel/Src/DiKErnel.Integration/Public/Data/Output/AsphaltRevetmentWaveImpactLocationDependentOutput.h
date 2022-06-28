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

#include "LocationDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Location dependent output of an asphalt revetment wave impact location.
     */
    class AsphaltRevetmentWaveImpactLocationDependentOutput : public Core::LocationDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param z
             *        The calculated z.
             * \param timeDependentOutputItems
             *        The time dependent output items of the location.
             * \param outerSlope
             *        The calculated outer slope.
             */
            explicit AsphaltRevetmentWaveImpactLocationDependentOutput(
                double z,
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems,
                double outerSlope);

            /*!
             * \brief Gets the calculated outer slope.
             * \return The calculated outer slope.
             */
            [[nodiscard]]
            double GetOuterSlope() const;

        private:
            const double _outerSlope;
    };
}

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

#include <vector>

#include "CalculationData.h"
#include "CalculationLocation.h"
#include "HydraulicLoads.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for all calculation input data.
     */
    class InputData
    {
        std::unique_ptr<CalculationData> calculationData;
        std::unique_ptr<HydraulicLoads> hydraulicLoads;
        std::vector<std::unique_ptr<CalculationLocation>> locations;

        public:
            /*!
             * \brief Creates a new instance.
             * \param calculationData
             *        The calculation data.
             * \param hydraulicLoads
             *        The hydraulic loads data.
             * \param locations
             *        The calculation locations.
             */
            explicit InputData(
                std::unique_ptr<CalculationData> calculationData,
                std::unique_ptr<HydraulicLoads> hydraulicLoads,
                std::vector<std::unique_ptr<CalculationLocation>> locations
            );

            /*!
             * \brief Gets the calculation data.
             * \return The calculation data.
             */
            const CalculationData& GetCalculationData() const;

            /*!
             * \brief Gets the hydraulic loads data.
             * \return The hydraulic loads data.
             */
            HydraulicLoads* GetHydraulicLoads() const;

            /*!
             * \brief Gets the calculation locations.
             * \return The calculation locations.
             */
            std::vector<CalculationLocation*> GetLocations() const;
    };
}

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

#include "CalculationLocationOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for all calculation related output data.
     */
    class OutputData
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param calculationLocationsOutput
             *        The output on a per calculation location basis.
             */
            explicit OutputData(
                std::vector<std::unique_ptr<CalculationLocationOutput>> calculationLocationsOutput
            );

            /*!
             * \brief Gets the output on a per calculation location basis.
             * \return The output on a per calculation location basis.
             */
            const std::vector<std::reference_wrapper<CalculationLocationOutput>>& GetCalculationLocationsOutput() const;

        private:
            std::vector<std::unique_ptr<CalculationLocationOutput>> _calculationLocationsOutput;
            std::vector<std::reference_wrapper<CalculationLocationOutput>> _calculationLocationOutputReferences;
    };
}

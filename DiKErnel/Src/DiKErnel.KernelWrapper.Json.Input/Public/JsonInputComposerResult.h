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

#include "ICalculationInput.h"
#include "JsonInputProcessType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    /*!
     * \brief Class that holds results as produced by JsonInputComposer.
     */
    class JsonInputComposerResult
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param calculationInput
             *        The composed calculation input.
             * \param processType
             *        The read process type.
             */
            explicit JsonInputComposerResult(
                std::unique_ptr<Core::ICalculationInput> calculationInput,
                JsonInputProcessType processType);

            /*!
             * \brief Gets the composed calculation input.
             * \return The composed calculation input.
             */
            const Core::ICalculationInput& GetCalculationInput() const;

            /*!
             * \brief Gets the read process type.
             * \return The read process type.
             */
            const JsonInputProcessType& GetProcessType() const;

        private:
            std::unique_ptr<Core::ICalculationInput> _calculationInput;
            JsonInputProcessType _processType;
    };
}

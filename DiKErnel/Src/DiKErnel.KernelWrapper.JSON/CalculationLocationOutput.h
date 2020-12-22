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
#include <string>

#include "RevetmentOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for location output data.
     */
    class CalculationLocationOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param name
             *        The name of the location.
             * \param revetmentOutput
             *        The revetment output.
             */
            explicit CalculationLocationOutput(
                std::string name,
                std::unique_ptr<RevetmentOutput> revetmentOutput);

            /*!
             * \brief Gets the name of the location.
             * \return The name of the location.
             */
            const std::string& GetName() const;

            /*!
             * \brief Gets the revetment output.
             * \return The revetment output.
             */
            const RevetmentOutput& GetRevetmentOutput() const;

        private:
            std::string name;
            std::unique_ptr<RevetmentOutput> revetmentOutput;
    };
}

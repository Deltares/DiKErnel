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
#include <string>

namespace DiKErnel::External::Overtopping
{
    struct Geometry;
    struct Load;
    struct ModelFactors;
    struct Result;

    /*!
     * \brief Adapter for the overtopping validation and calculation.
     */
    class OvertoppingAdapter
    {
        public:
            /*!
             * \brief Validates the input arguments for an overtopping calculation.
             * \param geometry
             *        The geometry.
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             * \param messageBuffer
             *        The message buffer to write validation messages to.
             * \param success
             *        Indicator whether the input arguments are valid or not.
             */
            static void Validate(
                Geometry& geometry,
                double dikeHeight,
                const std::string* messageBuffer,
                bool* success);

            /*!
             * \brief Calculates the overtopping based on its input arguments.
             * \param load
             *        The load.
             * \param geometry
             *        The geometry.
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             * \return The representative wave run-up (2 percent).
             *         Unit = [m]
             */
            static double CalculateQo(
                Load& load,
                Geometry& geometry,
                double dikeHeight);

        private:
            inline static std::string _languageCode = "UK";
            inline static int _bufferSize = 256;
            inline static int _verbosity = -1;

            static ModelFactors _modelFactors;
    };
}

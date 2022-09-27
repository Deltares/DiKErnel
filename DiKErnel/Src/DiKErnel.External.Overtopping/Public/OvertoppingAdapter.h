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
             * \param modelFactors
             *        The input.
             * \param messageBuffer
             *        The message buffer to write validation messages to.
             * \param success
             *        Indicator whether the input arguments are valid or not.
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             */
            static void Validate(
                Geometry& geometry,
                double dikeHeight,
                ModelFactors& modelFactors,
                const std::string* messageBuffer,
                bool* success);

            /*!
             * \brief Calculates the overtopping based on its input arguments.
             * \param load
             *        The load.
             * \param geometry
             *        The geometry.
             * \param modelFactors
             *        The input.
             * \param result
             *        The results of the calculation.
             * \param messageBuffer
             *        The message buffer to write error message to.
             * \param success
             *        Indicator whether the calculation was successful or not.
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             */
            static void CalculateQo(
                Load& load,
                Geometry& geometry,
                double dikeHeight,
                ModelFactors& modelFactors,
                Result* result,
                const std::string* messageBuffer,
                bool* success);

        private:
            inline static std::string _languageCode = "UK";
            inline static int _logFileNameSize = 256;
            inline static int _verbosity = -1;
    };
}

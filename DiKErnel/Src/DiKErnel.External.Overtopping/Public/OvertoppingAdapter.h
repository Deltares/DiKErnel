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
#include <vector>

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
             * \param xValues
             *        The x values of the profile points.
             *        Unit = [m]
             * \param zValues
             *        The z values of the profile points.
             *        Unit = [m]
             * \param roughnessCoefficients
             *        The roughness coefficients of the profile segments.
             *        Unit = [-]
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             * \return A vector of validation messages.
             */
            static std::vector<std::unique_ptr<std::string>> Validate(
                const std::vector<double>& xValues,
                const std::vector<double>& zValues,
                const std::vector<double>& roughnessCoefficients,
                double dikeHeight);

            /*!
             * \brief Calculates the representative wave run-up (2 percent).
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param wavePeriodTm10
             *        The wave period Tm10.
             *        Unit = [s]
             * \param waveDirection
             *        The wave direction with respect to the North.
             *        Unit = [degrees]
             * \param xValues
             *        The x values of the profile points.
             *        Unit = [m]
             * \param zValues
             *        The z values of the profile points.
             *        Unit = [m]
             * \param roughnessCoefficients
             *        The roughness coefficients of the profile segments.
             *        Unit = [-]
             * \param dikeHeight
             *        The dike height.
             *        Unit = [m]
             * \return The representative wave run-up (2 percent).
             *         Unit = [m]
             */
            static double CalculateZ2(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection,
                const std::vector<double>& xValues,
                const std::vector<double>& zValues,
                const std::vector<double>& roughnessCoefficients,
                double dikeHeight);

        private:
            inline static std::string _languageCode = "UK";
            inline static int _bufferSize = 256;
            inline static int _verbosity = -1;

            static ModelFactors _modelFactors;
    };
}

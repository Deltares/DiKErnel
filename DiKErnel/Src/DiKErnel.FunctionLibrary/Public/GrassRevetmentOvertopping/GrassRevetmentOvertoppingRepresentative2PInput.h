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

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Input for a grass revetment overtopping representative 2P calculation.
     */
    struct GrassRevetmentOvertoppingRepresentative2PInput
    {
        /*!
         * \brief The water level.
         *        Unit = [m]
         */
        double _waterLevel{};

        /*!
         * \brief The wave height.
         *        Unit = [m]
         */
        double _waveHeightHm0{};

        /*!
         * \brief The wave period Tm10.
         *        Unit = [s]
         */
        double _wavePeriodTm10{};

        /*!
         * \brief The wave direction with respect to the North.
         *        Unit = [degrees]
         */
        double _waveDirection{};

        /*!
         * \brief The x values of the profile points.
         *        Unit = [m]
         */
        std::vector<double> _xValuesProfile;

        /*!
         * \brief The z values of the profile points.
         *        Unit = [m]
         */
        std::vector<double> _zValuesProfile;

        /*!
         * \brief The roughness coefficients of the profile segments.
         *        Unit = [-]
         */
        std::vector<double> _roughnessCoefficients;

        /*!
         * \brief The dike height.
         *        Unit = [m]
         */
        double _dikeHeight{};
    };
}

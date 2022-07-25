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
     * \brief Input for the asphalt revetment wave impact functions.
     */
    struct AsphaltRevetmentWaveImpactFunctionsInput
    {
        /*!
         * \brief The logarithm of the failure tension.
         *        Unit = [MPa]
         */
        double _logFailureTension{};

        /*!
         * \brief The average number of waves.
         *        Unit = [-]
         */
        double _averageNumberOfWaves{};

        /*!
         * \brief The maximum peak stress.
         *        Unit = [MPa]
         */
        double _maximumPeakStress{};

        /*!
         * \brief The stiffness relation.
         *        Unit = [m^-1]
         */
        double _stiffnessRelation{};

        /*!
         * \brief The computational thickness.
         *        Unit = [m]
         */
        double _computationalThickness{};

        /*!
         * \brief The outer slope.
         *        Unit = [-]
         */
        double _outerSlope{};

        /*!
         * \brief The width factors.
         *        Unit = [-]
         */
        std::vector<std::pair<double, double>> _widthFactors{};

        /*!
         * \brief The depth factors.
         *        Unit = [-]
         */
        std::vector<std::pair<double, double>> _depthFactors{};

        /*!
         * \brief The impact factors.
         *        Unit = [-]
         */
        std::vector<std::pair<double, double>> _impactFactors{};

        /*!
         * \brief The z coordinate.
         *        Unit = [m]
         */
        double _z{};

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
         * \brief The fatigue alpha coefficient.
         *        Unit = [-]
         */
        double _fatigueAlpha{};

        /*!
         * \brief The fatigue beta coefficient.
         *        Unit = [-]
         */
        double _fatigueBeta{};

        /*!
         * \brief The impact number c coefficient.
         *        Unit = [-]
         */
        double _impactNumberC{};
    };
}

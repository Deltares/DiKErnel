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

namespace DiKErnel::Overtopping::KernelWrapper
{
    /*!
     * \brief The geometry for the overtopping kernel.
     */
    struct Geometry
    {
        /*!
         * \brief The normal of the dike.
         *        Unit = [deg]
         */
        double _normal{};

        /*!
         * \brief The number of coordinates.
         */
        int _nPoints{};

        /*!
         * \brief The x coordinates of the dike.
         *        Unit = [m]
         */
        double* _xCoords{};

        /*!
         * \brief The y coordinates of the dike.
         *        Unit = [m]
         */
        double* _yCoords{};

        /*!
         * \brief The roughness of the dike.
         *        Unit = [-]
         */
        double* _roughness{};
    };
}

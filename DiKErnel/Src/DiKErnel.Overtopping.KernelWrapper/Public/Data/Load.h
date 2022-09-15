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

namespace DiKErnel::External::Overtopping
{
    /*!
     * \brief The load for the overtopping kernel.
     */
    struct Load
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
        double _height{};

        /*!
         * \brief The wave period.
         *        Unit = [s]
         */
        double _period{};

        /*!
         * \brief The wave direction.
         *        Unit = [deg]
         */
        double _direction{};
    };
}

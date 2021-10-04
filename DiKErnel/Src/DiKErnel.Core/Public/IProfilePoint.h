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

namespace DiKErnel::Core
{
    /*!
     * \brief Interface defining a profile point that is needed to perform a calculation.
     */
    class IProfilePoint
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~IProfilePoint() = default;

            /*!
             * \brief Gets the x coordinate of the point.
             * \return The x coordinate of the point.
             */
            virtual double GetX() const = 0;

            /*!
             * \brief Gets the z coordinate of the point.
             * \return The z coordinate of the point.
             */
            virtual double GetZ() const = 0;
    };
}

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

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing a profile point that is needed to perform a calculation.
     */
    class ProfilePoint
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param x
             *        The x coordinate.
             * \param z
             *        The z coordinate.
             */
            explicit ProfilePoint(
                double x,
                double z);

            /*!
             * \brief Gets the x coordinate of the point.
             * \return The x coordinate of the point.
             */
            [[nodiscard]]
            double GetX() const;

            /*!
             * \brief Gets the z coordinate of the point.
             * \return The z coordinate of the point.
             */
            [[nodiscard]]
            double GetZ() const;

        private:
            double _x;
            double _z;
    };
}

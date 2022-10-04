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

namespace DiKErnel::Util
{
    /*!
     * \brief Helper class to help with numerics.
     */
    class NumericsHelper
    {
        public:
            /*!
             * \brief Asserts whether first and second are equal.
             * \param first
             *        The first argument.
             * \param second
             *        The second argument.
             * \return true when equal; false otherwise.
             */
            static bool AreEqual(
                double first,
                double second);

            /*!
             * \brief Converts the given value to a string.
             * \param value
             *        The value to convert.
             * \return The converted string.
             */
            static std::string ToString(
                double value);
    };
}

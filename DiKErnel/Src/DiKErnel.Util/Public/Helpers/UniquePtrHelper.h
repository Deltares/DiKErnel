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

namespace DiKErnel::Util
{
    /*!
     * \brief Helper class to help with unique pointers.
     */
    class UniquePtrHelper
    {
        public:
            /*!
             * \brief Tries to cast a unique pointer of Base to a unique pointer of Derived.
             * \tparam Derived
             *         The type to cast to.
             * \tparam Base
             *         The type to cast from.
             * \param basePointer
             *        The unique pointer to cast.
             * \return A unique pointer with Derived; or nullptr when the cast failed.
             */
            template <typename Derived, typename Base>
            static std::unique_ptr<Derived> DynamicCast(
                std::unique_ptr<Base>& basePointer)
            {
                auto baseObject = basePointer.release();
                if (auto* derivedObject = dynamic_cast<Derived*>(baseObject))
                {
                    return std::unique_ptr<Derived>(derivedObject);
                }

                basePointer.reset(baseObject);
                return std::unique_ptr<Derived>(nullptr);
            }
    };
}

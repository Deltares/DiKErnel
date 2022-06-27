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

#include <map>

namespace DiKErnel::Util
{
    /*!
     * \brief Class containing helper methods for a map.
     */
    class MapHelper
    {
        public:
            /**
             * \brief Checks whether the given map contains an element with the given key.
             * \tparam TKey The type of the key.
             * \tparam TValue The type of the value.
             * \param map The map to check
             * \param key The key to check.
             * \return Whether the map contains the key.
             */
            template <typename TKey, typename TValue>
            static bool ContainsKey(
                std::map<TKey, TValue> map,
                TKey key)
            {
                return map.find(key) != map.end();
            }
    };
}

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

#include <memory>
#include <vector>

#include "Event.h"

namespace DiKErnel::Util
{
    /*!
     * \brief Class that holds all information about a result and the events that occurred.
     * \tparam T The type of result.
     */
    template <typename T>
    class Result
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param result
             *        The result.
             * \param events
             *        The events that occurred.
             */
            Result(
                std::unique_ptr<T> result,
                std::vector<std::unique_ptr<Event>> events)
                : _result(std::move(result)),
                  _events(std::move(events))
            {
                for (const auto& event : _events)
                {
                    _eventReferences.emplace_back(*event);
                }
            }

            /*!
             * \brief Gets the result.
             * \return The result.
             */
            T* GetResult() const
            {
                return _result.get();
            }

            /*!
             * \brief Gets the events.
             * \return The events.
             */
            const std::vector<std::reference_wrapper<Event>>& GetEvents() const
            {
                return _eventReferences;
            }

        private:
            std::unique_ptr<T> _result;
            std::vector<std::unique_ptr<Event>> _events;
            std::vector<std::reference_wrapper<Event>> _eventReferences;
    };
}

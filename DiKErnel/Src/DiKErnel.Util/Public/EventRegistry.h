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
#include <vector>

#include "Event.h"

namespace DiKErnel::Util
{
    /*!
     * \brief Class where events can be registered and tracked on a per thread basis.
     */
    class EventRegistry
    {
        public:
            #pragma region Disable copy and assignment API

            EventRegistry(
                EventRegistry& eventRegistry) = delete;

            EventRegistry(
                EventRegistry&& eventRegistry) = delete;

            void operator=(
                EventRegistry& eventRegistry) = delete;

            void operator=(
                EventRegistry&& eventRegistry) = delete;

            #pragma endregion

            /*!
             * \brief Registers an event.
             * \param event
             *        The event to register.
             */
            static void Register(
                std::unique_ptr<Event> event);

            /*!
             * \brief Flushes all registered events.
             * \return The registered events.
             */
            static std::vector<std::unique_ptr<Event>> Flush();

        private:
            EventRegistry() = default;

            ~EventRegistry() = default;

            thread_local static EventRegistry _instance;

            std::vector<std::unique_ptr<Event>> _events = std::vector<std::unique_ptr<Event>>();
    };
}

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
     * \brief Class where events can be registered and tracked.
     */
    class EventRegistry
    {
        public:
            #pragma region Disable copy and assignment constructor and operator API

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
             * \brief Gets all the registered events.
             * \return The registered events.
             */
            static const std::vector<std::reference_wrapper<Event>>& GetEvents();

            /*!
             * \brief Flushes all registered events.
             */
            static void Flush();

        private:
            EventRegistry() = default;

            ~EventRegistry() = default;

            static EventRegistry& GetInstance();

            static thread_local EventRegistry* _eventRegistry;

            std::vector<std::unique_ptr<Event>> _events = std::vector<std::unique_ptr<Event>>();
            std::vector<std::reference_wrapper<Event>> _eventReferences = std::vector<std::reference_wrapper<Event>>();
    };
}

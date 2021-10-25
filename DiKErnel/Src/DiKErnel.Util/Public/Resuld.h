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
     * \brief Class that holds all information about the result of an operation and the events that
     *        occurred.
     */
    class Resuld
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param successful
             *        Whether the operation was successful.
             * \param events
             *        The events that occurred.
             */
            Resuld(
                bool successful,
                std::vector<std::unique_ptr<Event>> events);

            /*!
             * \brief Gets whether the operation was successful.
             * \return Whether the operation was successful.
             */
            bool GetSuccessful() const;

            /*!
             * \brief Gets the events.
             * \return The events.
             */
            const std::vector<std::reference_wrapper<Event>>& GetEvents() const;

        private:
            bool _successful;
            std::vector<std::unique_ptr<Event>> _events;
            std::vector<std::reference_wrapper<Event>> _eventReferences;
    };
}

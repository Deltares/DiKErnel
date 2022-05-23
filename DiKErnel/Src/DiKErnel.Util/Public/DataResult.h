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

#include "SimpleResult.h"

namespace DiKErnel::Util
{
    /*!
     * \brief Class that holds information about the result of an operation, the events that
     *        occurred and the data that was produced.
     * \tparam T The type of the data that was produced.
     */
    template <typename T>
    class DataResult : public SimpleResult
    {
        public:
            /*!
             * \brief Creates a new instance in case the operation was not successful.
             * \param events
             *        The events that occurred.
             */
            explicit DataResult(
                std::vector<std::unique_ptr<Event>> events)
                : SimpleResult(false, std::move(events)),
                  _data(nullptr) { }

            /*!
             * \brief Creates a new instance in case the operation was successful.
             * \param data
             *        The data that was produced.
             * \param events
             *        The events that occurred.
             */
            explicit DataResult(
                std::unique_ptr<T> data,
                std::vector<std::unique_ptr<Event>> events)
                : SimpleResult(true, std::move(events)),
                  _data(std::move(data)) { }

            /*!
             * \brief Gets the data that was produced.
             * \return The data that was produced.
             */
            const T* GetData() const
            {
                return _data.get();
            }

        private:
            std::unique_ptr<T> _data;
    };
}

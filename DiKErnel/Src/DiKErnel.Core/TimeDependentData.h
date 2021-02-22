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
     * \brief Class containing all time step that is needed to perform a calculation.
     */
    class TimeDependentData
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param beginTime
             *        The begin time.
             * \param endTime
             *        The end time.
             */
            explicit TimeDependentData(
                int beginTime,
                int endTime);

            /*!
             * \brief Gets the begin time.
             * \return The begin time.
            */
            int GetBeginTime() const;

            /*!
             * \brief Gets the end time.
             * \return The end time.
             */
            int GetEndTime() const;

        private:
            int beginTime;
            int endTime;
    };
}

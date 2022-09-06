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

#include "ProfilePoint.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing a profile segment that is needed to perform a calculation.
     */
    class ProfileSegment
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param lowerPoint
             *        The lower profile point.
             * \param upperPoint
             *        The upper profile point.
             */
            explicit ProfileSegment(
                const ProfilePoint& lowerPoint,
                const ProfilePoint& upperPoint);

            /*!
             * \brief Creates a new instance.
             * \param lowerPoint
             *        The lower profile point.
             * \param upperPoint
             *        The upper profile point.
             * \param roughness
             *        The roughness.
             */
            explicit ProfileSegment(
                const ProfilePoint& lowerPoint,
                const ProfilePoint& upperPoint,
                double roughness);

            /*!
             * \brief Gets the lower point of the segment.
             * \return The lower point of the segment.
             */
            [[nodiscard]]
            const ProfilePoint& GetLowerPoint() const;

            /*!
             * \brief Gets the upper point of the segment.
             * \return The upper point of the segment.
             */
            [[nodiscard]]
            const ProfilePoint& GetUpperPoint() const;

            /*!
             * \brief Gets roughness of the segment.
             * \return The roughness of the segment.
             */
            [[nodiscard]]
            double GetRoughness() const;

        private:
            const ProfilePoint& _lowerPoint;
            const ProfilePoint& _upperPoint;
            double _roughness;
    };
}

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
             * \param startPoint
             *        The start point.
             * \param endPoint
             *        The end point.
             * \param roughnessCoefficient
             *        The roughness coefficient.
             */
            explicit ProfileSegment(
                std::shared_ptr<ProfilePoint> startPoint,
                std::shared_ptr<ProfilePoint> endPoint,
                double roughnessCoefficient);

            /*!
             * \brief Gets the start point of the segment.
             * \return The start point of the segment.
             */
            [[nodiscard]]
            ProfilePoint& GetStartPoint() const;

            /*!
             * \brief Gets the end point of the segment.
             * \return The end point of the segment.
             */
            [[nodiscard]]
            ProfilePoint& GetEndPoint() const;

            /*!
             * \brief Gets the roughness coefficient of the segment.
             * \return The roughness coefficient of the segment.
             */
            [[nodiscard]]
            double GetRoughnessCoefficient() const;

        private:
            std::shared_ptr<ProfilePoint> _startPoint;
            std::shared_ptr<ProfilePoint> _endPoint;
            double _roughnessCoefficient;
    };
}

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
             * \param lowerPoint
             *        The lower profile point.
             * \param upperPoint
             *        The upper profile point.
             * \param roughnessCoefficient
             *        The roughness coefficient.
             *        Unit = [-]
             */
            explicit ProfileSegment(
                std::shared_ptr<ProfilePoint> lowerPoint,
                std::shared_ptr<ProfilePoint> upperPoint,
                double roughnessCoefficient);

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
             * \brief Gets the roughness coefficient of the segment.
             * \return The roughness coefficient of the segment.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetRoughnessCoefficient() const;

        private:
            std::shared_ptr<ProfilePoint> _lowerPointReference;
            std::shared_ptr<ProfilePoint> _upperPointReference;
            double _roughnessCoefficient;
    };
}

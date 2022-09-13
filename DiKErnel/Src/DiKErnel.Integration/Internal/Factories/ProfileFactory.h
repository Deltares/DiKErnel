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

#include "CharacteristicPoint.h"
#include "ProfileFactoryPointData.h"
#include "ProfileFactorySegmentData.h"
#include "ProfileSegment.h"

namespace DiKErnel::Integration
{
    class ProfileFactory
    {
        public:
            static std::vector<std::unique_ptr<Core::ProfileSegment>> CreateProfileSegments(
                const std::vector<std::unique_ptr<ProfileFactorySegmentData>>& profileSegments);

            static std::vector<std::unique_ptr<Core::CharacteristicPoint>> CreateCharacteristicPoints(
                const std::vector<std::unique_ptr<ProfileFactoryPointData>>& profilePoints,
                const std::vector<std::unique_ptr<Core::ProfileSegment>>& profileSegments);

        private:
            static double GetRoughnessCoefficient(
                const double* roughnessCoefficient);

            static bool DoesSegmentStartAtPoint(
                const Core::ProfilePoint& profilePoint,
                const ProfileFactorySegmentData& segmentData);

            static const Core::ProfilePoint* FindMatchingPoint(
                const ProfileFactoryPointData& profilePointData,
                const std::vector<std::unique_ptr<Core::ProfileSegment>>& segments);
    };
}

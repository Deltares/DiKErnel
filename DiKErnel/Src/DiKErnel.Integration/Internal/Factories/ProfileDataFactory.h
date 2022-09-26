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
#include "ProfileData.h"
#include "ProfileDataFactoryPoint.h"
#include "ProfileDataFactorySegment.h"
#include "ProfileSegment.h"

namespace DiKErnel::Integration
{
    class ProfileDataFactory
    {
        public:
            static std::unique_ptr<ProfileData> Create(
                const std::vector<std::reference_wrapper<ProfileDataFactorySegment>>& profileSegments,
                const std::vector<std::reference_wrapper<ProfileDataFactoryPoint>>& profilePoints);

        private:
            static std::vector<std::unique_ptr<Core::ProfileSegment>> CreateProfileSegments(
                const std::vector<std::reference_wrapper<ProfileDataFactorySegment>>& profileSegments);

            static std::vector<std::unique_ptr<Core::CharacteristicPoint>> CreateCharacteristicPoints(
                const std::vector<std::reference_wrapper<ProfileDataFactoryPoint>>& profilePoints,
                const std::vector<std::unique_ptr<Core::ProfileSegment>>& profileSegments);

            static const Core::ProfilePoint* FindMatchingPointOnSegment(
                const ProfileDataFactoryPoint& profilePointData,
                const std::vector<std::unique_ptr<Core::ProfileSegment>>& segments);

            static bool IsMatchingPoint(
                const ProfileDataFactoryPoint& profilePointData,
                const Core::ProfilePoint& profilePoint);
    };
}

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

#include "ProfileDataFactory.h"

#include "InputHelper.h"
#include "NumericsHelper.h"
#include "ProfileSegmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    vector<unique_ptr<CharacteristicPoint>> ProfileDataFactory::CreateCharacteristicPoints(
        const vector<reference_wrapper<ProfileDataFactoryPoint>>& profilePoints,
        const vector<unique_ptr<ProfileSegment>>& profileSegments)
    {
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints;
        for (const auto& profilePointDataReference : profilePoints)
        {
            const auto& profilePointData = profilePointDataReference.get();

            characteristicPoints.push_back(
                make_unique<CharacteristicPoint>(GetMatchingPointOnSegment(profilePointDataReference, profileSegments),
                                                 profilePointData.GetCharacteristicPoint()));
        }

        return characteristicPoints;
    }

    const ProfilePoint& ProfileDataFactory::GetMatchingPointOnSegment(
        const ProfileDataFactoryPoint& profilePointData,
        const vector<unique_ptr<ProfileSegment>>& segments)
    {
        for (const auto& segment : segments)
        {
            if (const auto& segmentStartPoint = segment->GetStartPoint();
                NumericsHelper::AreEqual(profilePointData.GetX(), segmentStartPoint.GetX()))
            {
                return segmentStartPoint;
            }
        }

        return segments.back()->GetEndPoint();
    }
}

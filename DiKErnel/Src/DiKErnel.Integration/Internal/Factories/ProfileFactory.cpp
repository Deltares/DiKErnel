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

#include "ProfileFactory.h"

#include <cmath>

#include "InputFactoryException.h"
#include "InputFactoryHelper.h"
#include "ProfileSegmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<ProfileData> ProfileFactory::Create(
        const std::vector<std::reference_wrapper<ProfileFactorySegmentData>>& profileSegments,
        const std::vector<std::reference_wrapper<ProfileFactoryPointData>>& profilePoints)
    {
        if (profileSegments.empty())
        {
            throw InputFactoryException("At least 1 segment is required.");
        }

        auto segments = CreateProfileSegments(profileSegments);
        auto characteristicPoints = CreateCharacteristicPoints(profilePoints, segments);

        return make_unique<ProfileData>(move(segments), move(characteristicPoints));
    }

    vector<unique_ptr<ProfileSegment>> ProfileFactory::CreateProfileSegments(
        const vector<reference_wrapper<ProfileFactorySegmentData>>& profileSegments)
    {
        vector<unique_ptr<ProfileSegment>> segments;

        shared_ptr<ProfilePoint> segmentStartPoint = nullptr;
        for (const auto& currentSegment : profileSegments)
        {
            const auto& currentSegmentReference = currentSegment.get();
            if (segmentStartPoint == nullptr)
            {
                segmentStartPoint = make_shared<ProfilePoint>(currentSegmentReference.GetStartPointX(), currentSegmentReference.GetStartPointZ());
            }

            if (!DoesSegmentStartAtPoint(*segmentStartPoint, currentSegmentReference))
            {
                throw InputFactoryException("The start point of a successive segment must be equal to the end point of the previous segment.");
            }

            auto segmentEndPoint = make_shared<ProfilePoint>(currentSegmentReference.GetEndPointX(), currentSegmentReference.GetEndPointZ());
            segments.emplace_back(make_unique<ProfileSegment>(
                segmentStartPoint, segmentEndPoint,
                InputFactoryHelper::GetValue(currentSegmentReference.GetRoughnessCoefficient(),ProfileSegmentDefaults::GetRoughnessCoefficient())));
            segmentStartPoint = segmentEndPoint;
        }

        return segments;
    }

    vector<unique_ptr<CharacteristicPoint>> ProfileFactory::CreateCharacteristicPoints(
        const vector<reference_wrapper<ProfileFactoryPointData>>& profilePoints,
        const vector<unique_ptr<ProfileSegment>>& profileSegments)
    {
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints;
        for (const auto& profilePointData : profilePoints)
        {
            const auto& profilePointDataReference = profilePointData.get();
            const auto matchingPointReference = FindMatchingPointOnSegment(profilePointDataReference, profileSegments);

            if (matchingPointReference == nullptr)
            {
                throw InputFactoryException("Characteristic point must be on a start or end point of a segment.");
            }

            characteristicPoints.emplace_back(
                make_unique<CharacteristicPoint>(*matchingPointReference, profilePointDataReference.GetCharacteristicPoint()));
        }

        return characteristicPoints;
    }

    bool ProfileFactory::DoesSegmentStartAtPoint(
        const ProfilePoint& profilePoint,
        const ProfileFactorySegmentData& segmentData)
    {
        return abs(profilePoint.GetX() - segmentData.GetStartPointX()) < numeric_limits<double>::epsilon()
                && abs(profilePoint.GetZ() - segmentData.GetStartPointZ()) < numeric_limits<double>::epsilon();
    }

    const ProfilePoint* ProfileFactory::FindMatchingPointOnSegment(
        const ProfileFactoryPointData& profilePointData,
        const vector<unique_ptr<ProfileSegment>>& segments)
    {
        for (const auto& segment : segments)
        {
            const auto& segmentStartPoint = segment->GetStartPoint();
            const auto& segmentEndPoint = segment->GetEndPoint();

            if (FindMatchingPoint(profilePointData, segmentStartPoint) != nullptr)
            {
                return &segmentStartPoint;
            }

            if (FindMatchingPoint(profilePointData, segmentEndPoint) != nullptr)
            {
                return &segmentEndPoint;
            }
        }

        return nullptr;
    }

    const ProfilePoint* ProfileFactory::FindMatchingPoint(
        const ProfileFactoryPointData& profilePointData,
        const ProfilePoint& profilePoint)
    {
        return abs(profilePointData.GetX() - profilePoint.GetX()) <= numeric_limits<double>::epsilon()
                   ? &profilePoint
                   : nullptr;
    }
}

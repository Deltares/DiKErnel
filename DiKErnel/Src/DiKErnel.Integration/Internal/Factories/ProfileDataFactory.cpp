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

#include <cmath>

#include "InputFactoryException.h"
#include "InputFactoryHelper.h"
#include "ProfileSegmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<ProfileData> ProfileDataFactory::Create(
        const vector<reference_wrapper<ProfileDataFactorySegment>>& profileSegments,
        const vector<reference_wrapper<ProfileDataFactoryPoint>>& profilePoints)
    {
        if (profileSegments.empty())
        {
            throw InputFactoryException("At least 1 segment is required.");
        }

        auto segments = CreateProfileSegments(profileSegments);
        return make_unique<ProfileData>(move(segments), CreateCharacteristicPoints(profilePoints, segments));
    }

    vector<unique_ptr<ProfileSegment>> ProfileDataFactory::CreateProfileSegments(
        const vector<reference_wrapper<ProfileDataFactorySegment>>& profileSegments)
    {
        vector<unique_ptr<ProfileSegment>> segments;

        shared_ptr<ProfilePoint> segmentStartPoint = nullptr;
        for (const auto& currentSegmentReference : profileSegments)
        {
            const auto& currentSegment = currentSegmentReference.get();
            if (segmentStartPoint == nullptr)
            {
                segmentStartPoint = make_shared<ProfilePoint>(currentSegment.GetStartPointX(), currentSegment.GetStartPointZ());
            }

            if (!DoesSegmentStartAtPoint(*segmentStartPoint, currentSegmentReference))
            {
                throw InputFactoryException("The start point of a successive segment must be equal to the end point of the previous segment.");
            }

            auto segmentEndPoint = make_shared<ProfilePoint>(currentSegment.GetEndPointX(), currentSegment.GetEndPointZ());
            segments.emplace_back(make_unique<ProfileSegment>(
                segmentStartPoint, segmentEndPoint,
                InputFactoryHelper::GetValue(currentSegment.GetRoughnessCoefficient(), ProfileSegmentDefaults::GetRoughnessCoefficient())));
            segmentStartPoint = segmentEndPoint;
        }

        return segments;
    }

    vector<unique_ptr<CharacteristicPoint>> ProfileDataFactory::CreateCharacteristicPoints(
        const vector<reference_wrapper<ProfileDataFactoryPoint>>& profilePoints,
        const vector<unique_ptr<ProfileSegment>>& profileSegments)
    {
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints;
        for (const auto& profilePointDataReference : profilePoints)
        {
            const auto& profilePointData = profilePointDataReference.get();
            const auto* matchingPoint = FindMatchingPointOnSegment(profilePointDataReference, profileSegments);

            if (matchingPoint == nullptr)
            {
                throw InputFactoryException("Characteristic point must be on a start or end point of a segment.");
            }

            characteristicPoints.emplace_back(
                make_unique<CharacteristicPoint>(*matchingPoint, profilePointData.GetCharacteristicPoint()));
        }

        return characteristicPoints;
    }

    bool ProfileDataFactory::DoesSegmentStartAtPoint(
        const ProfilePoint& profilePoint,
        const ProfileDataFactorySegment& segmentData)
    {
        return abs(profilePoint.GetX() - segmentData.GetStartPointX()) < numeric_limits<double>::epsilon()
                && abs(profilePoint.GetZ() - segmentData.GetStartPointZ()) < numeric_limits<double>::epsilon();
    }

    const ProfilePoint* ProfileDataFactory::FindMatchingPointOnSegment(
        const ProfileDataFactoryPoint& profilePointData,
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

    const ProfilePoint* ProfileDataFactory::FindMatchingPoint(
        const ProfileDataFactoryPoint& profilePointData,
        const ProfilePoint& profilePoint)
    {
        return abs(profilePointData.GetX() - profilePoint.GetX()) <= numeric_limits<double>::epsilon()
                   ? &profilePoint
                   : nullptr;
    }
}

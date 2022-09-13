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

#include "ProfileFactoryException.h"
#include "ProfileSegmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    vector<unique_ptr<ProfileSegment>> ProfileFactory::CreateProfileSegments(
        const vector<unique_ptr<ProfileFactorySegmentData>>& profileSegments)
    {
        vector<unique_ptr<ProfileSegment>> segments;

        if (!profileSegments.empty())
        {
            auto& initialSegmentData = profileSegments.at(0);
            auto startPoint = make_shared<ProfilePoint>(initialSegmentData->GetStartPointX(), initialSegmentData->GetStartPointZ());

            for (int i = 0; i < static_cast<int>(profileSegments.size()); ++i)
            {
                auto& currentSegmentData = profileSegments.at(i);

                if (i > 0 && !DoesSegmentStartAtPoint(*startPoint, *currentSegmentData))
                {
                    throw ProfileFactoryException("Segments must be chained.");
                }

                auto endPoint = make_shared<ProfilePoint>(currentSegmentData->GetEndPointX(), currentSegmentData->GetEndPointZ());
                segments.emplace_back(make_unique<ProfileSegment>(startPoint, endPoint,
                                                                  GetRoughnessCoefficient(currentSegmentData->GetRoughnessCoefficient())));
                startPoint = endPoint;
            }
        }

        return segments;
    }

    vector<unique_ptr<CharacteristicPoint>> ProfileFactory::CreateCharacteristicPoints(
        const vector<unique_ptr<ProfileFactoryPointData>>& profilePoints,
        const vector<unique_ptr<ProfileSegment>>& profileSegments)
    {
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints;
        for (const auto& profilePointData : profilePoints)
        {
            const auto matchingPointReference = FindMatchingPoint(*profilePointData, profileSegments);
            if (matchingPointReference == nullptr)
            {
                throw ProfileFactoryException("Characteristic point must be on a start or end point of a segment.");
            }

            characteristicPoints.emplace_back(make_unique<CharacteristicPoint>(*matchingPointReference, profilePointData->GetCharacteristicPoint()));
        }

        return characteristicPoints;
    }

    double ProfileFactory::GetRoughnessCoefficient(
        const double* roughnessCoefficient)
    {
        if (roughnessCoefficient == nullptr)
        {
            return ProfileSegmentDefaults::GetRoughnessCoefficient();
        }

        return *roughnessCoefficient;
    }

    bool ProfileFactory::DoesSegmentStartAtPoint(
        const ProfilePoint& profilePoint,
        const ProfileFactorySegmentData& segmentData)
    {
        return abs(profilePoint.GetX() - segmentData.GetStartPointX()) < numeric_limits<double>::epsilon()
                && abs(profilePoint.GetZ() - segmentData.GetStartPointZ()) < numeric_limits<double>::epsilon();
    }

    const ProfilePoint* ProfileFactory::FindMatchingPoint(
        const ProfileFactoryPointData& profilePointData,
        const vector<unique_ptr<ProfileSegment>>& segments)
    {
        const ProfilePoint* matchingPointReference = nullptr;
        for (const auto& segment : segments)
        {
            const double profilePointX = profilePointData.GetX();
            if (const auto& segmentStartPoint = segment->GetStartPoint();
                abs(profilePointX - segmentStartPoint.GetX()) <= numeric_limits<double>::epsilon())
            {
                matchingPointReference = &segmentStartPoint;
            }

            if (const auto& segmentEndPoint = segment->GetEndPoint();
                abs(profilePointX - segmentEndPoint.GetX()) <= numeric_limits<double>::epsilon())
            {
                matchingPointReference = &segmentEndPoint;
            }
        }

        return matchingPointReference;
    }
}

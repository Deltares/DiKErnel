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
            for (const auto& segmentData : profileSegments)
            {
                auto startPoint = make_shared<ProfilePoint>(segmentData->GetStartPointX(), segmentData->GetStartPointZ());
                auto endPoint = make_shared<ProfilePoint>(segmentData->GetEndPointX(), segmentData->GetStartPointZ());

                segments.emplace_back(make_unique<ProfileSegment>(startPoint, endPoint,
                                                                  GetRoughnessCoefficient(segmentData->GetRoughnessCoefficient())));
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
        for (const auto& characteristicPoint : profilePoints)
        {
            for (const auto& segment : profileSegments)
            {
                const double characteristicPointX = characteristicPoint->GetX();
                if (const auto& segmentStartPoint = segment->GetStartPoint();
                    abs(characteristicPointX - segmentStartPoint.GetX()) <= numeric_limits<double>::epsilon())
                {
                    characteristicPoints.emplace_back(make_unique<CharacteristicPoint>(segmentStartPoint,
                                                                                       characteristicPoint->GetCharacteristicPoint()));
                    break;
                }

                if (const auto& segmentEndPoint = segment->GetEndPoint();
                    abs(characteristicPointX - segmentEndPoint.GetX()) <= numeric_limits<double>::epsilon())
                {
                    characteristicPoints.emplace_back(make_unique<CharacteristicPoint>(segmentEndPoint,
                                                                                       characteristicPoint->GetCharacteristicPoint()));
                    break;
                }
            }
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
}

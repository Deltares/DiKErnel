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

#include <gtest/gtest.h>

#include "ProfileData.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace testing;

    struct ProfileDataTest : Test
    {
        static unique_ptr<ProfileData> CreateDefaultProfileData()
        {
            auto pointOne = make_shared<ProfilePoint>(1.0, 1.1);
            auto pointTwo = make_shared<ProfilePoint>(2.0, 2.2);
            auto pointThree = make_shared<ProfilePoint>(3.0, 3.3);

            vector<unique_ptr<ProfileSegment>> testDikeProfileSegments;
            testDikeProfileSegments.push_back(make_unique<ProfileSegment>(pointOne, pointTwo, 1.0));
            testDikeProfileSegments.push_back(make_unique<ProfileSegment>(pointTwo, pointThree, 1.0));

            return make_unique<ProfileData>(move(testDikeProfileSegments), vector<unique_ptr<CharacteristicPoint>>());
        }
    };

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionLeftOfDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(0.0);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(1.0);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(2.0);

        // Assert
        ASSERT_DOUBLE_EQ(2.2, verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(3.0);

        // Assert
        ASSERT_DOUBLE_EQ(3.3, verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionBetweenAscendingDikeProfilePoints_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(1.5);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionBetweenDescendingDikeProfilePoints_ExpectedValue)
    {
        // Setup
        auto pointOne = make_shared<ProfilePoint>(1.0, 3.3);
        auto pointTwo = make_shared<ProfilePoint>(2.0, 2.2);
        auto pointThree = make_shared<ProfilePoint>(3.0, 1.1);

        vector<unique_ptr<ProfileSegment>> testDikeProfileSegmentsWithDescendingHeight;
        testDikeProfileSegmentsWithDescendingHeight.push_back(make_unique<ProfileSegment>(pointOne, pointTwo, 1.0));
        testDikeProfileSegmentsWithDescendingHeight.push_back(make_unique<ProfileSegment>(pointTwo, pointThree, 1.0));

        const ProfileData profileData(move(testDikeProfileSegmentsWithDescendingHeight), vector<unique_ptr<CharacteristicPoint>>());

        // Call
        const auto verticalHeight = profileData.InterpolationVerticalHeight(2.5);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationVerticalHeight_HorizontalPositionRightOfDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto verticalHeight = profileData->InterpolationVerticalHeight(4.0);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightBelowDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(0.0);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(1.1);

        // Assert
        ASSERT_DOUBLE_EQ(1.0, horizontalPosition);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(2.2);

        // Assert
        ASSERT_DOUBLE_EQ(2.0, horizontalPosition);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightOnLastDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(3.3);

        // Assert
        ASSERT_DOUBLE_EQ(3.0, horizontalPosition);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightBetweenProfilePoints_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(1.65);

        // Assert
        ASSERT_DOUBLE_EQ(1.5, horizontalPosition);
    }

    TEST_F(ProfileDataTest, InterpolationHorizontalPosition_VerticalHeightAboveDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto horizontalPosition = profileData->InterpolationHorizontalPosition(4.0);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionLeftOfDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(0.0);

        // Assert
        ASSERT_EQ(nullptr, profileSegment);
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(1.0);

        // Assert
        ASSERT_EQ(nullptr, profileSegment);
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(2.0);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        ASSERT_DOUBLE_EQ(1.0, startPoint.GetX());
        ASSERT_DOUBLE_EQ(1.1, startPoint.GetZ());
        ASSERT_DOUBLE_EQ(2.0, endPoint.GetX());
        ASSERT_DOUBLE_EQ(2.2, endPoint.GetZ());
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionBetweenDikeProfilePoints_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(1.5);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        ASSERT_DOUBLE_EQ(1.0, startPoint.GetX());
        ASSERT_DOUBLE_EQ(1.1, startPoint.GetZ());
        ASSERT_DOUBLE_EQ(2.0, endPoint.GetX());
        ASSERT_DOUBLE_EQ(2.2, endPoint.GetZ());
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(3.0);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        ASSERT_DOUBLE_EQ(2.0, startPoint.GetX());
        ASSERT_DOUBLE_EQ(2.2, startPoint.GetZ());
        ASSERT_DOUBLE_EQ(3.0, endPoint.GetX());
        ASSERT_DOUBLE_EQ(3.3, endPoint.GetZ());
    }

    TEST_F(ProfileDataTest, GetProfileSegment_HorizontalPositionRightOfDikeProfile_ExpectedValue)
    {
        // Setup
        const auto profileData = CreateDefaultProfileData();

        // Call
        const auto profileSegment = profileData->GetProfileSegment(4.0);

        // Assert
        ASSERT_EQ(nullptr, profileSegment);
    }
}

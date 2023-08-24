// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class ProfileDataTest
    {

    struct ProfileDataTest : Test
    {
        static unique_ptr<ProfileData> CreateDefaultProfileData()
        {
            var pointOne = make_shared<ProfilePoint>(1.0, 1.1);
            var pointTwo = make_shared<ProfilePoint>(2.0, 2.2);
            var pointThree = make_shared<ProfilePoint>(3.0, 3.3);

            vector<unique_ptr<ProfileSegment>> testDikeProfileSegments;
            testDikeProfileSegments.push_back(make_unique<ProfileSegment>(pointOne, pointTwo, 1.0));
            testDikeProfileSegments.push_back(make_unique<ProfileSegment>(pointTwo, pointThree, 1.0));

            return make_unique<ProfileData>(move(testDikeProfileSegments), vector<unique_ptr<CharacteristicPoint>>());
        }
    };

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionLeftOfDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(0.0);

        // Assert
        Assert.AreEqual(numeric_limits<double>::infinity(), verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(1.0);

        // Assert
        Assert.AreEqual(1.1, verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(2.0);

        // Assert
        Assert.AreEqual(2.2, verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(3.0);

        // Assert
        Assert.AreEqual(3.3, verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionBetweenAscendingDikeProfilePoints_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(1.5);

        // Assert
        Assert.AreEqual(1.65, verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionBetweenDescendingDikeProfilePoints_ExpectedValue()
    {
        // Setup
        var pointOne = make_shared<ProfilePoint>(1.0, 3.3);
        var pointTwo = make_shared<ProfilePoint>(2.0, 2.2);
        var pointThree = make_shared<ProfilePoint>(3.0, 1.1);

        vector<unique_ptr<ProfileSegment>> testDikeProfileSegmentsWithDescendingHeight;
        testDikeProfileSegmentsWithDescendingHeight.push_back(make_unique<ProfileSegment>(pointOne, pointTwo, 1.0));
        testDikeProfileSegmentsWithDescendingHeight.push_back(make_unique<ProfileSegment>(pointTwo, pointThree, 1.0));

        const ProfileData profileData(move(testDikeProfileSegmentsWithDescendingHeight), vector<unique_ptr<CharacteristicPoint>>());

        // Call
        const var verticalHeight = profileData.InterpolationVerticalHeight(2.5);

        // Assert
        Assert.AreEqual(1.65, verticalHeight);
    }

        [Test]
    public void InterpolationVerticalHeight_HorizontalPositionRightOfDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var verticalHeight = profileData->InterpolationVerticalHeight(4.0);

        // Assert
        Assert.AreEqual(numeric_limits<double>::infinity(), verticalHeight);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightBelowDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(0.0);

        // Assert
        Assert.AreEqual(numeric_limits<double>::infinity(), horizontalPosition);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightOnFirstDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(1.1);

        // Assert
        Assert.AreEqual(1.0, horizontalPosition);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightOnRandomDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(2.2);

        // Assert
        Assert.AreEqual(2.0, horizontalPosition);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightOnLastDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(3.3);

        // Assert
        Assert.AreEqual(3.0, horizontalPosition);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightBetweenProfilePoints_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(1.65);

        // Assert
        Assert.AreEqual(1.5, horizontalPosition);
    }

        [Test]
    public void InterpolationHorizontalPosition_VerticalHeightAboveDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var horizontalPosition = profileData->InterpolationHorizontalPosition(4.0);

        // Assert
        Assert.AreEqual(numeric_limits<double>::infinity(), horizontalPosition);
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionLeftOfDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(0.0);

        // Assert
        Assert.IsNull(profileSegment);
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(1.0);

        // Assert
        Assert.IsNull(profileSegment);
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(2.0);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        Assert.AreEqual(1.0, startPoint.GetX());
        Assert.AreEqual(1.1, startPoint.GetZ());
        Assert.AreEqual(2.0, endPoint.GetX());
        Assert.AreEqual(2.2, endPoint.GetZ());
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionBetweenDikeProfilePoints_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(1.5);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        Assert.AreEqual(1.0, startPoint.GetX());
        Assert.AreEqual(1.1, startPoint.GetZ());
        Assert.AreEqual(2.0, endPoint.GetX());
        Assert.AreEqual(2.2, endPoint.GetZ());
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(3.0);

        // Assert
        const auto& startPoint = profileSegment->GetStartPoint();
        const auto& endPoint = profileSegment->GetEndPoint();
        Assert.AreEqual(2.0, startPoint.GetX());
        Assert.AreEqual(2.2, startPoint.GetZ());
        Assert.AreEqual(3.0, endPoint.GetX());
        Assert.AreEqual(3.3, endPoint.GetZ());
    }

        [Test]
    public void GetProfileSegment_HorizontalPositionRightOfDikeProfile_ExpectedValue()
    {
        // Setup
        const var profileData = CreateDefaultProfileData();

        // Call
        const var profileSegment = profileData->GetProfileSegment(4.0);

        // Assert
        Assert.IsNull(profileSegment);
    }
}

}

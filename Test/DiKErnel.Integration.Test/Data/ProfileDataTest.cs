// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    internal sealed class ProfileDataTest
    {
        private const double tolerance = 1e-15;

        [Test]
        public void GetVerticalHeight_HorizontalPositionLeftOfDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(0);

            // Assert
            Assert.That(verticalHeight, Is.NaN);
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(1);

            // Assert
            Assert.That(verticalHeight, Is.EqualTo(1.1));
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(2);

            // Assert
            Assert.That(verticalHeight, Is.EqualTo(2.2));
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(3);

            // Assert
            Assert.That(verticalHeight, Is.EqualTo(3.3));
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionBetweenAscendingDikeProfilePoints_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(1.5);

            // Assert
            Assert.That(verticalHeight, Is.EqualTo(1.65).Within(tolerance));
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionBetweenDescendingDikeProfilePoints_ExpectedValue()
        {
            // Setup
            var profilePoint1 = new ProfilePoint(1, 3.3);
            var profilePoint2 = new ProfilePoint(2, 2.2);
            var profilePoint3 = new ProfilePoint(3, 1.1);

            var profileSegmentsWithDescendingHeight = new List<ProfileSegment>
            {
                new ProfileSegment(profilePoint1, profilePoint2, Random.NextDouble()),
                new ProfileSegment(profilePoint2, profilePoint3, Random.NextDouble())
            };

            var profileData = new ProfileData(Random.NextDouble(), profileSegmentsWithDescendingHeight,
                                              new List<CharacteristicPoint>(), CreateDefaultForeshore());

            // Call
            double verticalHeight = profileData.GetVerticalHeight(2.5);

            // Assert
            Assert.That(verticalHeight, Is.EqualTo(1.65).Within(tolerance));
        }

        [Test]
        public void GetVerticalHeight_HorizontalPositionRightOfDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double verticalHeight = profileData.GetVerticalHeight(4);

            // Assert
            Assert.That(verticalHeight, Is.NaN);
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightBelowDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(0);

            // Assert
            Assert.That(horizontalPosition, Is.NaN);
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightOnFirstDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(1.1);

            // Assert
            Assert.That(horizontalPosition, Is.EqualTo(1));
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightOnRandomDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(2.2);

            // Assert
            Assert.That(horizontalPosition, Is.EqualTo(2));
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightOnLastDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(3.3);

            // Assert
            Assert.That(horizontalPosition, Is.EqualTo(3));
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightBetweenProfilePoints_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(1.65);

            // Assert
            Assert.That(horizontalPosition, Is.EqualTo(1.5).Within(tolerance));
        }

        [Test]
        public void GetHorizontalPosition_VerticalHeightAboveDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            double horizontalPosition = profileData.GetHorizontalPosition(4);

            // Assert
            Assert.That(horizontalPosition, Is.NaN);
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionLeftOfDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(0);

            // Assert
            Assert.That(profileSegment, Is.Null);
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(1);

            // Assert
            Assert.That(profileSegment, Is.Null);
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(2);

            // Assert
            Assert.That(profileSegment.StartPoint.X, Is.EqualTo(1));
            Assert.That(profileSegment.StartPoint.Z, Is.EqualTo(1.1));
            Assert.That(profileSegment.EndPoint.X, Is.EqualTo(2));
            Assert.That(profileSegment.EndPoint.Z, Is.EqualTo(2.2));
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionBetweenDikeProfilePoints_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(1.5);

            // Assert
            Assert.That(profileSegment.StartPoint.X, Is.EqualTo(1));
            Assert.That(profileSegment.StartPoint.Z, Is.EqualTo(1.1));
            Assert.That(profileSegment.EndPoint.X, Is.EqualTo(2));
            Assert.That(profileSegment.EndPoint.Z, Is.EqualTo(2.2));
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(3);

            // Assert
            Assert.That(profileSegment.StartPoint.X, Is.EqualTo(2));
            Assert.That(profileSegment.StartPoint.Z, Is.EqualTo(2.2));
            Assert.That(profileSegment.EndPoint.X, Is.EqualTo(3));
            Assert.That(profileSegment.EndPoint.Z, Is.EqualTo(3.3));
        }

        [Test]
        public void GetProfileSegment_HorizontalPositionRightOfDikeProfile_ExpectedValue()
        {
            // Setup
            ProfileData profileData = CreateDefaultProfileData();

            // Call
            ProfileSegment profileSegment = profileData.GetProfileSegment(4);

            // Assert
            Assert.That(profileSegment, Is.Null);
        }

        private static ProfileData CreateDefaultProfileData()
        {
            var profilePoint1 = new ProfilePoint(1, 1.1);
            var profilePoint2 = new ProfilePoint(2, 2.2);
            var profilePoint3 = new ProfilePoint(3, 3.3);

            var profileSegments = new List<ProfileSegment>
            {
                new ProfileSegment(profilePoint1, profilePoint2, Random.NextDouble()),
                new ProfileSegment(profilePoint2, profilePoint3, Random.NextDouble())
            };

            return new ProfileData(Random.NextDouble(), profileSegments, new List<CharacteristicPoint>(), CreateDefaultForeshore());
        }

        private static Foreshore CreateDefaultForeshore()
        {
            return new Foreshore(0.004, -4);
        }
    }
}
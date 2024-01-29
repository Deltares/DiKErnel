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

using DiKErnel.Core.Data;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class ProfileDataAssertHelper
    {
        public static void AssertProfileSegment(double expectedStartPointX, double expectedStartPointZ,
                                                double expectedEndPointX, double expectedEndPointZ,
                                                double expectedRoughnessCoefficient,
                                                ProfileSegment actualProfileSegment)
        {
            AssertProfilePoint(expectedStartPointX, expectedStartPointZ, actualProfileSegment.StartPoint);
            AssertProfilePoint(expectedEndPointX, expectedEndPointZ, actualProfileSegment.EndPoint);
            Assert.That(actualProfileSegment.RoughnessCoefficient, Is.EqualTo(expectedRoughnessCoefficient));
        }

        public static void AssertCharacteristicPoint(ProfilePoint expectedProfilePoint,
                                                     CharacteristicPointType expectedCharacteristicPointType,
                                                     CharacteristicPoint actualCharacteristicPoint)
        {
            Assert.That(actualCharacteristicPoint.ProfilePoint, Is.SameAs(expectedProfilePoint));
            Assert.That(actualCharacteristicPoint.CharacteristicPointType, Is.EqualTo(expectedCharacteristicPointType));
        }

        public static void AssertForeshore(double expectedSlope, double expectedBottomZ, Foreshore actualForeshore)
        {
            Assert.That(actualForeshore.Slope, Is.EqualTo(expectedSlope));
            Assert.That(actualForeshore.BottomZ, Is.EqualTo(expectedBottomZ));
        }

        private static void AssertProfilePoint(double expectedX, double expectedZ, ProfilePoint actualProfilePoint)
        {
            Assert.That(actualProfilePoint.X, Is.EqualTo(expectedX));
            Assert.That(actualProfilePoint.Z, Is.EqualTo(expectedZ));
        }
    }
}
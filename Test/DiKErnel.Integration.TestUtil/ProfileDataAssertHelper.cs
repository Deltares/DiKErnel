// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
        public static void AssertProfileSegment(double startPointX, double startPointZ, double endPointX,
                                                double endPointZ, double roughnessCoefficient,
                                                ProfileSegment profileSegment)
        {
            AssertProfilePoint(startPointX, startPointZ, profileSegment.StartPoint);
            AssertProfilePoint(endPointX, endPointZ, profileSegment.EndPoint);
            Assert.That(profileSegment.RoughnessCoefficient, Is.EqualTo(roughnessCoefficient));
        }

        public static void AssertCharacteristicPoint(ProfilePoint profilePoint,
                                                     CharacteristicPointType characteristicPointType,
                                                     CharacteristicPoint characteristicPoint)
        {
            Assert.That(characteristicPoint.ProfilePoint, Is.SameAs(profilePoint));
            Assert.That(characteristicPoint.CharacteristicPointType, Is.EqualTo(characteristicPointType));
        }

        public static void AssertForeshore(double slope, double bottomZ, Foreshore foreshore)
        {
            Assert.That(foreshore.Slope, Is.EqualTo(slope));
            Assert.That(foreshore.BottomZ, Is.EqualTo(bottomZ));
        }

        private static void AssertProfilePoint(double x, double z, ProfilePoint profilePoint)
        {
            Assert.That(profilePoint.X, Is.EqualTo(x));
            Assert.That(profilePoint.Z, Is.EqualTo(z));
        }
    }
}
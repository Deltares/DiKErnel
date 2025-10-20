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

using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Defaults;
using DiKErnel.Integration.Data;
using DiKErnel.Util.Helpers;

namespace DiKErnel.Integration.Factories
{
    internal static class ProfileDataFactory
    {
        public static ProfileData Create(double dikeOrientation, IReadOnlyList<ProfileDataFactorySegment> profileSegments,
                                         IReadOnlyList<ProfileDataFactoryPoint> profilePoints, Foreshore foreshore)
        {
            IReadOnlyList<ProfileSegment> segments = CreateProfileSegments(profileSegments);

            return new ProfileData(dikeOrientation, segments, CreateCharacteristicPoints(profilePoints, segments), foreshore);
        }

        private static List<ProfileSegment> CreateProfileSegments(
            IReadOnlyList<ProfileDataFactorySegment> profileSegments)
        {
            var segments = new List<ProfileSegment>();

            ProfilePoint segmentStartPoint = null;

            foreach (ProfileDataFactorySegment profileSegment in profileSegments)
            {
                segmentStartPoint ??= new ProfilePoint(profileSegment.StartPointX, profileSegment.StartPointZ);

                var segmentEndPoint = new ProfilePoint(profileSegment.EndPointX, profileSegment.EndPointZ);

                double roughnessCoefficient = profileSegment.RoughnessCoefficient
                                              ?? ProfileSegmentDefaults.RoughnessCoefficient;

                segments.Add(new ProfileSegment(segmentStartPoint, segmentEndPoint, roughnessCoefficient));

                segmentStartPoint = segmentEndPoint;
            }

            return segments;
        }

        private static List<CharacteristicPoint> CreateCharacteristicPoints(
            IReadOnlyList<ProfileDataFactoryPoint> profilePoints, IReadOnlyList<ProfileSegment> profileSegments)
        {
            return profilePoints.Select(profilePoint => new CharacteristicPoint(
                                            GetMatchingPointOnSegment(profilePoint, profileSegments),
                                            profilePoint.CharacteristicPointType))
                                .ToList();
        }

        private static ProfilePoint GetMatchingPointOnSegment(ProfileDataFactoryPoint profilePoint,
                                                              IReadOnlyList<ProfileSegment> segments)
        {
            ProfilePoint matchingStartPoint = segments.Select(s => s.StartPoint)
                                                      .FirstOrDefault(sp => NumericsHelper.AreEqual(profilePoint.X, sp.X));

            return matchingStartPoint ?? segments[segments.Count - 1].EndPoint;
        }
    }
}
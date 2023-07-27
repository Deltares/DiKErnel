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
        public static ProfileData Create(IReadOnlyList<ProfileDataFactorySegment> profileSegments,
                                         IReadOnlyList<ProfileDataFactoryPoint> profilePoints)
        {
            IReadOnlyList<ProfileSegment> segments = CreateProfileSegments(profileSegments);

            return new ProfileData(segments, CreateCharacteristicPoints(profilePoints, segments));
        }

        private static IReadOnlyList<ProfileSegment> CreateProfileSegments(
            IReadOnlyList<ProfileDataFactorySegment> profileSegments)
        {
            var segments = new List<ProfileSegment>();

            ProfilePoint segmentStartPoint = null;

            foreach (ProfileDataFactorySegment profileSegment in profileSegments)
            {
                segmentStartPoint ??= new ProfilePoint(profileSegment.StartPointX, profileSegment.StartPointZ);

                var segmentEndPoint = new ProfilePoint(profileSegment.EndPointX, profileSegment.EndPointZ);

                double roughnessCoefficient = profileSegment.RoughnessCoefficient ?? ProfileSegmentDefaults.RoughnessCoefficient;

                segments.Add(new ProfileSegment(segmentStartPoint, segmentEndPoint, roughnessCoefficient));

                segmentStartPoint = segmentEndPoint;
            }

            return segments;
        }

        private static IReadOnlyList<CharacteristicPoint> CreateCharacteristicPoints(
            IReadOnlyList<ProfileDataFactoryPoint> profilePoints,
            IReadOnlyList<ProfileSegment> profileSegments)
        {
            return profilePoints.Select(profilePoint => new CharacteristicPoint(
                                            GetMatchingPointOnSegment(profilePoint, profileSegments),
                                            profilePoint.CharacteristicPointType))
                                .ToList();
        }

        private static ProfilePoint GetMatchingPointOnSegment(ProfileDataFactoryPoint profilePoint,
                                                              IReadOnlyList<ProfileSegment> segments)
        {
            foreach (ProfileSegment segment in segments)
            {
                ProfilePoint segmentStartPoint = segment.StartPoint;

                if (NumericsHelper.AreEqual(profilePoint.X, segmentStartPoint.X))
                {
                    return segmentStartPoint;
                }
            }

            return segments[segments.Count - 1].EndPoint;
        }
    }
}
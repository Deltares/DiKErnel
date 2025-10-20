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
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data
{
    internal class ProfileData : IProfileData
    {
        private readonly List<ProfilePoint> profilePoints = new List<ProfilePoint>();

        public ProfileData(double dikeOrientation, IReadOnlyList<ProfileSegment> profileSegments,
                           IReadOnlyList<CharacteristicPoint> characteristicPoints, Foreshore foreshore)
        {
            DikeOrientation = dikeOrientation;
            ProfileSegments = profileSegments;
            CharacteristicPoints = characteristicPoints;
            Foreshore = foreshore;

            profilePoints.Add(ProfileSegments[0].StartPoint);
            profilePoints.AddRange(ProfileSegments.Select(profileSegment => profileSegment.EndPoint));
        }

        public double DikeOrientation { get; }

        public IReadOnlyList<ProfileSegment> ProfileSegments { get; }

        public IReadOnlyList<CharacteristicPoint> CharacteristicPoints { get; }

        public Foreshore Foreshore { get; }

        public bool Validate()
        {
            var validationIssues = new List<ValidationIssue>
            {
                ProfileValidator.DikeOrientation(DikeOrientation)
            };

            validationIssues.AddRange(ProfileSegments.Select(profileSegment => ProfileValidator.RoughnessCoefficient(
                                                                 profileSegment.RoughnessCoefficient))
                                                     .ToList());

            return ValidationHelper.RegisterValidationIssues(validationIssues);
        }

        public double GetVerticalHeight(double horizontalPosition)
        {
            for (var i = 0; i < profilePoints.Count; i++)
            {
                ProfilePoint profilePoint = profilePoints[i];
                double xCurrentDikeProfilePoint = profilePoint.X;
                double zCurrentDikeProfilePoint = profilePoint.Z;

                if (NumericsHelper.AreEqual(xCurrentDikeProfilePoint, horizontalPosition))
                {
                    return zCurrentDikeProfilePoint;
                }

                if (xCurrentDikeProfilePoint > horizontalPosition)
                {
                    if (i == 0)
                    {
                        return double.NaN;
                    }

                    ProfilePoint previousProfilePoint = profilePoints[i - 1];
                    double xPreviousDikeProfilePoint = previousProfilePoint.X;
                    double zPreviousDikeProfilePoint = previousProfilePoint.Z;

                    return zPreviousDikeProfilePoint + (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                           / (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                           * (horizontalPosition - xPreviousDikeProfilePoint);
                }
            }

            return double.NaN;
        }

        public double GetHorizontalPosition(double verticalHeight)
        {
            for (var i = 0; i < profilePoints.Count; i++)
            {
                ProfilePoint profilePoint = profilePoints[i];
                double xCurrentDikeProfilePoint = profilePoint.X;
                double zCurrentDikeProfilePoint = profilePoint.Z;

                if (NumericsHelper.AreEqual(zCurrentDikeProfilePoint, verticalHeight))
                {
                    return xCurrentDikeProfilePoint;
                }

                if (zCurrentDikeProfilePoint > verticalHeight)
                {
                    if (i == 0)
                    {
                        return double.NaN;
                    }

                    ProfilePoint previousProfilePoint = profilePoints[i - 1];
                    double xPreviousDikeProfilePoint = previousProfilePoint.X;
                    double zPreviousDikeProfilePoint = previousProfilePoint.Z;

                    return xPreviousDikeProfilePoint + (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                           / (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                           * (verticalHeight - zPreviousDikeProfilePoint);
                }
            }

            return double.NaN;
        }

        public ProfileSegment GetProfileSegment(double horizontalPosition)
        {
            for (var i = 0; i < ProfileSegments.Count; i++)
            {
                ProfileSegment profileSegment = ProfileSegments[i];

                if (i == 0 && NumericsHelper.AreEqual(profileSegment.StartPoint.X, horizontalPosition))
                {
                    return null;
                }

                if (profileSegment.StartPoint.X <= horizontalPosition
                    && profileSegment.EndPoint.X >= horizontalPosition)
                {
                    return profileSegment;
                }
            }

            return null;
        }
    }
}
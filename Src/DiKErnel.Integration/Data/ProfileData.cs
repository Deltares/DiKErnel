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

using System;
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

        public ProfileData(IReadOnlyList<ProfileSegment> profileSegments,
                           IReadOnlyList<CharacteristicPoint> characteristicPoints)
        {
            ProfileSegments = profileSegments;
            CharacteristicPoints = characteristicPoints;

            profilePoints.Add(ProfileSegments[0].StartPoint);
            profilePoints.AddRange(ProfileSegments.Select(profileSegment => profileSegment.EndPoint));
        }

        public IReadOnlyList<ProfileSegment> ProfileSegments { get; }

        public IReadOnlyList<CharacteristicPoint> CharacteristicPoints { get; }

        public bool Validate()
        {
            List<ValidationIssue> validationIssues =
                ProfileSegments.Select(profileSegment => ProfileValidator.RoughnessCoefficient(
                                           profileSegment.RoughnessCoefficient))
                               .ToList();

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
                        return double.PositiveInfinity;
                    }

                    ProfilePoint previousProfilePoint = profilePoints[i - 1];
                    double xPreviousDikeProfilePoint = previousProfilePoint.X;
                    double zPreviousDikeProfilePoint = previousProfilePoint.Z;

                    return zPreviousDikeProfilePoint + (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                           / (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                           * (horizontalPosition - xPreviousDikeProfilePoint);
                }
            }

            return double.PositiveInfinity;
        }

        public double GetHorizontalPosition(double verticalHeight)
        {
            throw new NotImplementedException();
        }

        public ProfileSegment GetProfileSegment(double horizontalPosition)
        {
            throw new NotImplementedException();
        }
    }
}
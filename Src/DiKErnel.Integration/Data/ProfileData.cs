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

namespace DiKErnel.Integration.Data
{
    internal class ProfileData : IProfileData
    {
        public void ProfileData(
                IReadOnlyList<ProfileSegment> profileSegments,
                IReadOnlyList<CharacteristicPoint> characteristicPoints);

    public bool Validate() override;

    public double InterpolationVerticalHeight(
                double horizontalPosition) override;

    public double InterpolationHorizontalPosition(
                double verticalHeight) override;

    public ProfileSegment* GetProfileSegment(
                double horizontalPosition) override;

    public IReadOnlyList<ProfileSegment> GetProfileSegments() override;

    public IReadOnlyList<CharacteristicPoint> GetCharacteristicPoints() override;

            private IReadOnlyList<ProfilePoint> _profilePointReferences;
            private IReadOnlyList<ProfileSegment> _profileSegments;
            private IReadOnlyList<ProfileSegment> _profileSegmentReferences;
            private IReadOnlyList<CharacteristicPoint> _characteristicPoints;
            private IReadOnlyList<CharacteristicPoint> _characteristicPointReferences;
    }
}

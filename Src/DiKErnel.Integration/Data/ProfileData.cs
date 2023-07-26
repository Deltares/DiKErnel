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
    internal class ProfileData : Core::IProfileData
    {
        public void ProfileData(
                vector<unique_ptr<Core::ProfileSegment>> profileSegments,
                vector<unique_ptr<Core::CharacteristicPoint>> characteristicPoints);

    public bool Validate() override;

    public double InterpolationVerticalHeight(
                double horizontalPosition) override;

    public double InterpolationHorizontalPosition(
                double verticalHeight) override;

    public Core::ProfileSegment* GetProfileSegment(
                double horizontalPosition) override;

    public vector<reference_wrapper<Core::ProfileSegment>>& GetProfileSegments() override;

    public vector<reference_wrapper<Core::CharacteristicPoint>>& GetCharacteristicPoints() override;

            private vector<reference_wrapper<Core::ProfilePoint>> _profilePointReferences;
            private vector<unique_ptr<Core::ProfileSegment>> _profileSegments;
            private vector<reference_wrapper<Core::ProfileSegment>> _profileSegmentReferences;
            private vector<unique_ptr<Core::CharacteristicPoint>> _characteristicPoints;
            private vector<reference_wrapper<Core::CharacteristicPoint>> _characteristicPointReferences;
    }
}

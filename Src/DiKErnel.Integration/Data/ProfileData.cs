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
    class ProfileData : public Core::IProfileData
    {
        public:
            explicit ProfileData(
                std::vector<std::unique_ptr<Core::ProfileSegment>> profileSegments,
                std::vector<std::unique_ptr<Core::CharacteristicPoint>> characteristicPoints);

            bool Validate() const override;

            double InterpolationVerticalHeight(
                double horizontalPosition) const override;

            double InterpolationHorizontalPosition(
                double verticalHeight) const override;

            const Core::ProfileSegment* GetProfileSegment(
                double horizontalPosition) const override;

            const std::vector<std::reference_wrapper<Core::ProfileSegment>>& GetProfileSegments() const override;

            const std::vector<std::reference_wrapper<Core::CharacteristicPoint>>& GetCharacteristicPoints() const override;

        private:
            std::vector<std::reference_wrapper<Core::ProfilePoint>> _profilePointReferences;
            std::vector<std::unique_ptr<Core::ProfileSegment>> _profileSegments;
            std::vector<std::reference_wrapper<Core::ProfileSegment>> _profileSegmentReferences;
            std::vector<std::unique_ptr<Core::CharacteristicPoint>> _characteristicPoints;
            std::vector<std::reference_wrapper<Core::CharacteristicPoint>> _characteristicPointReferences;
    };
}

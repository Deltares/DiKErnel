// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

#include <memory>

#include "IProfileData.h"

namespace DiKErnel::Integration
{
    class ProfileData : public Core::IProfileData
    {
        public:
            explicit ProfileData(
                std::vector<std::unique_ptr<Core::ProfilePoint>> profilePoints,
                std::vector<std::unique_ptr<Core::CharacteristicPoint>> characteristicPoints);

            const std::vector<std::reference_wrapper<Core::ProfilePoint>>& GetProfilePoints() const override;

            const std::vector<std::reference_wrapper<Core::CharacteristicPoint>>& GetCharacteristicPoints() const override;

            bool HasBerm() const override;

        private:
            std::vector<std::unique_ptr<Core::ProfilePoint>> _profilePoints;
            std::vector<std::reference_wrapper<Core::ProfilePoint>> _profilePointReferences;
            std::vector<std::unique_ptr<Core::CharacteristicPoint>> _characteristicPoints;
            std::vector<std::reference_wrapper<Core::CharacteristicPoint>> _characteristicPointReferences;
    };
}

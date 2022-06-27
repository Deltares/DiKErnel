// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "ProfileData.h"

#include "CharacteristicPointsHelper.h"
#include "ProfileValidator.h"
#include "ValidationHelper.h"
#include "ValidationIssue.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    ProfileData::ProfileData(
        vector<unique_ptr<ProfilePoint>> profilePoints,
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints)
        : _profilePoints(move(profilePoints)),
          _characteristicPoints(move(characteristicPoints))
    {
        for (const auto& profilePoint : _profilePoints)
        {
            _profilePointReferences.emplace_back(*profilePoint);
        }

        for (const auto& characteristicPoint : _characteristicPoints)
        {
            _characteristicPointReferences.emplace_back(*characteristicPoint);
        }
    }

    bool ProfileData::Validate() const
    {
        const auto& outerToe = CharacteristicPointsHelper::GetCoordinatesForType(_characteristicPointReferences, CharacteristicPointType::OuterToe);
        const auto& outerCrest = CharacteristicPointsHelper::GetCoordinatesForType(_characteristicPointReferences, CharacteristicPointType::OuterCrest);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(ProfileValidator::OuterToe(outerToe.get()));
        validationIssues.emplace_back(ProfileValidator::OuterCrest(outerCrest.get()));

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    const vector<reference_wrapper<ProfilePoint>>& ProfileData::GetProfilePoints() const
    {
        return _profilePointReferences;
    }

    const vector<reference_wrapper<CharacteristicPoint>>& ProfileData::GetCharacteristicPoints() const
    {
        return _characteristicPointReferences;
    }
}

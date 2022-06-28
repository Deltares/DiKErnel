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

#include <cmath>

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
        const auto outerToe = CharacteristicPointsHelper::GetCoordinatesForType(_characteristicPointReferences, CharacteristicPointType::OuterToe);
        const auto outerCrest = CharacteristicPointsHelper::GetCoordinatesForType(_characteristicPointReferences,
                                                                                   CharacteristicPointType::OuterCrest);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(ProfileValidator::OuterToe(outerToe.get()));
        validationIssues.emplace_back(ProfileValidator::OuterCrest(outerCrest.get()));

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    double ProfileData::InterpolationVerticalHeight(
        const double horizontalPosition) const
    {
        for (auto i = 0; i < static_cast<int>(_profilePoints.size()); ++i)
        {
            const auto& profilePoint = _profilePoints.at(i);
            const auto xCurrentDikeProfilePoint = profilePoint->GetX();
            const auto zCurrentDikeProfilePoint = profilePoint->GetZ();

            if (abs(xCurrentDikeProfilePoint - horizontalPosition) <= numeric_limits<double>::epsilon())
            {
                return zCurrentDikeProfilePoint;
            }

            if (xCurrentDikeProfilePoint > horizontalPosition)
            {
                if (i == 0)
                {
                    return numeric_limits<double>::infinity();
                }

                const auto& previousProfilePoint = _profilePoints.at(i - 1);
                const auto xPreviousDikeProfilePoint = previousProfilePoint->GetX();
                const auto zPreviousDikeProfilePoint = previousProfilePoint->GetZ();

                return zPreviousDikeProfilePoint + (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                        / (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                        * (horizontalPosition - xPreviousDikeProfilePoint);
            }
        }

        return numeric_limits<double>::infinity();
    }

    double ProfileData::InterpolationHorizontalPosition(
        const double verticalHeight) const
    {
        for (auto i = 0; i < static_cast<int>(_profilePoints.size()); ++i)
        {
            const auto& profilePoint = _profilePoints.at(i);
            const auto xCurrentDikeProfilePoint = profilePoint->GetX();
            const auto zCurrentDikeProfilePoint = profilePoint->GetZ();

            if (abs(zCurrentDikeProfilePoint - verticalHeight) <= numeric_limits<double>::epsilon())
            {
                return xCurrentDikeProfilePoint;
            }

            if (zCurrentDikeProfilePoint > verticalHeight)
            {
                if (i == 0)
                {
                    return numeric_limits<double>::infinity();
                }

                const auto& previousProfilePoint = _profilePoints.at(i - 1);
                const auto xPreviousDikeProfilePoint = previousProfilePoint->GetX();
                const auto zPreviousDikeProfilePoint = previousProfilePoint->GetZ();

                return xPreviousDikeProfilePoint + (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                        / (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                        * (verticalHeight - zPreviousDikeProfilePoint);
            }
        }

        return numeric_limits<double>::infinity();
    }

    unique_ptr<ProfileSegment> ProfileData::GetProfileSegment(
        const double horizontalPosition) const
    {
        for (auto i = 0; i < static_cast<int>(_profilePoints.size()); ++i)
        {
            if(const auto& profilePoint = _profilePoints.at(i); profilePoint->GetX() >= horizontalPosition)
            {
                if(i == 0)
                {
                    return nullptr;
                }

                return make_unique<ProfileSegment>(*profilePoint, *_profilePoints.at(i - 1));
            }
        }

        return nullptr;
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

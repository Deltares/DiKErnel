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
#include "ProfileDataValidator.h"
#include "ValidationHelper.h"
#include "ValidationIssue.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    ProfileData::ProfileData(
        vector<unique_ptr<ProfileSegment>> profileSegments,
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints)
        : _profileSegments(move(profileSegments)),
          _characteristicPoints(move(characteristicPoints))
    {
        _profilePointReferences.emplace_back(_profileSegments.front()->GetStartPoint());

        for (const auto& profileSegment : _profileSegments)
        {
            _profileSegmentReferences.emplace_back(*profileSegment);
            _profilePointReferences.emplace_back(profileSegment->GetEndPoint());
        }

        for (const auto& characteristicPoint : _characteristicPoints)
        {
            _characteristicPointReferences.emplace_back(*characteristicPoint);
        }
    }

    bool ProfileData::Validate() const
    {
        vector<unique_ptr<ValidationIssue>> validationIssues;
        for (const auto& profileSegment : _profileSegments)
        {
            validationIssues.emplace_back(ProfileDataValidator::RoughnessCoefficient(profileSegment->GetRoughnessCoefficient()));
        }

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    double ProfileData::InterpolationVerticalHeight(
        const double horizontalPosition) const
    {
        for (auto i = 0; i < static_cast<int>(_profilePointReferences.size()); ++i)
        {
            const auto& profilePoint = _profilePointReferences.at(i).get();
            const auto xCurrentDikeProfilePoint = profilePoint.GetX();
            const auto zCurrentDikeProfilePoint = profilePoint.GetZ();

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

                const auto& previousProfilePoint = _profilePointReferences.at(i - 1).get();
                const auto xPreviousDikeProfilePoint = previousProfilePoint.GetX();
                const auto zPreviousDikeProfilePoint = previousProfilePoint.GetZ();

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
        for (auto i = 0; i < static_cast<int>(_profilePointReferences.size()); ++i)
        {
            const auto& profilePoint = _profilePointReferences.at(i).get();
            const auto xCurrentDikeProfilePoint = profilePoint.GetX();
            const auto zCurrentDikeProfilePoint = profilePoint.GetZ();

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

                const auto& previousProfilePoint = _profilePointReferences.at(i - 1).get();
                const auto xPreviousDikeProfilePoint = previousProfilePoint.GetX();
                const auto zPreviousDikeProfilePoint = previousProfilePoint.GetZ();

                return xPreviousDikeProfilePoint + (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                        / (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                        * (verticalHeight - zPreviousDikeProfilePoint);
            }
        }

        return numeric_limits<double>::infinity();
    }

    const ProfileSegment* ProfileData::GetProfileSegment(
        const double horizontalPosition) const
    {
        for (auto i = 0; i < static_cast<int>(_profileSegments.size()); ++i)
        {
            auto& profileSegment = _profileSegments.at(i);
            if (i == 0 && abs(profileSegment->GetStartPoint().GetX() - horizontalPosition) <= numeric_limits<double>::epsilon())
            {
                return nullptr;
            }

            if (profileSegment->GetStartPoint().GetX() <= horizontalPosition && profileSegment->GetEndPoint().GetX() >= horizontalPosition)
            {
                return profileSegment.get();
            }
        }

        return nullptr;
    }

    const vector<reference_wrapper<ProfileSegment>>& ProfileData::GetProfileSegments() const
    {
        return _profileSegmentReferences;
    }

    const vector<reference_wrapper<CharacteristicPoint>>& ProfileData::GetCharacteristicPoints() const
    {
        return _characteristicPointReferences;
    }
}

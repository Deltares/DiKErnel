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

#include "LocationDependentInput.h"

#include <utility>

#include "CharacteristicPointsHelper.h"
#include "RevetmentFunctions.h"
#include "RevetmentValidator.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;
    using namespace Util;

    LocationDependentInput::LocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber)
        : _x(x),
          _initialDamage(initialDamage),
          _failureNumber(failureNumber) { }

    bool LocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto& characteristicPoints = profileData.GetCharacteristicPoints();

        const auto outerToe = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::OuterToe);
        const auto outerCrest = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::OuterCrest);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        if (outerToe != nullptr && outerCrest != nullptr)
        {
            validationIssues.emplace_back(RevetmentValidator::X(_x, outerToe->first, outerCrest->first));
        }
        validationIssues.emplace_back(RevetmentValidator::InitialDamage(_initialDamage));
        validationIssues.emplace_back(RevetmentValidator::FailureNumber(_failureNumber, _initialDamage));

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    unique_ptr<TimeDependentOutput> LocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        if (!_derivedLocationDependentInputInitialized)
        {
            _derivedLocationDependentInputInitialized = true;

            InitializeDerivedLocationDependentInput(profileData);
        }

        return CalculateTimeDependentOutput(initialDamage, timeDependentInput, profileData);
    }

    double LocationDependentInput::GetX() const
    {
        return _x;
    }

    double LocationDependentInput::GetInitialDamage() const
    {
        return _initialDamage;
    }

    double LocationDependentInput::GetFailureNumber() const
    {
        return _failureNumber;
    }

    double LocationDependentInput::GetZ() const
    {
        return _z;
    }

    void LocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        _z = profileData.InterpolationVerticalHeight(_x);
    }
}

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
        const double failureNumber,
        const bool requiresDamageAtStartOfCalculation)
        : _x(x),
          _initialDamage(initialDamage),
          _failureNumber(failureNumber),
          _requiresDamageAtStartOfCalculation(requiresDamageAtStartOfCalculation) {}

    bool LocationDependentInput::Validate(
        const vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputs,
        const IProfileData& profileData) const
    {
        vector<unique_ptr<ValidationIssue>> validationIssues;

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

    bool LocationDependentInput::GetRequiresDamageAtStartOfCalculation() const
    {
        return _requiresDamageAtStartOfCalculation;
    }

    void LocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        _z = profileData.InterpolationVerticalHeight(_x);
    }
}

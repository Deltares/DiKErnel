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

#include "LocationDependentInput.h"

#include <utility>

#include "RevetmentFunctions.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace FunctionLibrary;
    using namespace std;

    LocationDependentInput::LocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber)
        : _x(x),
          _initialDamage(initialDamage),
          _failureNumber(failureNumber) { }

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
        for (const auto& profilePointReference : profileData.GetProfilePoints())
        {
            const auto& profilePoint = profilePointReference.get();

            _dikeProfilePoints.emplace_back(profilePoint.GetX(), profilePoint.GetZ());
        }

        _z = RevetmentFunctions::InterpolationVerticalHeight(_x, _dikeProfilePoints);
    }

    vector<pair<double, double>>& LocationDependentInput::GetDikeProfilePoints()
    {
        return _dikeProfilePoints;
    }
}

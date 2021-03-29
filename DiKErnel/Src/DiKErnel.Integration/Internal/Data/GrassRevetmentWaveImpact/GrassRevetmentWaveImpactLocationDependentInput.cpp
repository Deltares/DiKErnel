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

#include "GrassRevetmentWaveImpactLocationDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    GrassRevetmentWaveImpactLocationDependentInput::GrassRevetmentWaveImpactLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
        unique_ptr<GrassRevetmentWaveImpactFailureTime> failureTime)
        : LocationDependentInput(move(name), initialDamage, failureNumber, tanA, positionZ),
          _waveAngleImpact(move(waveAngleImpact)),
          _failureTime(move(failureTime)) {}

    double GrassRevetmentWaveImpactLocationDependentInput::Calculate(
        double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        return 0;
    }

    GrassRevetmentWaveImpactWaveAngleImpact& GrassRevetmentWaveImpactLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }

    GrassRevetmentWaveImpactFailureTime& GrassRevetmentWaveImpactLocationDependentInput::GetFailureTime() const
    {
        return *_failureTime;
    }
}

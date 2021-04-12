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

#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    GrassRevetmentWaveRunupRayleighLocationDependentInput::GrassRevetmentWaveRunupRayleighLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        const double representativeWaveRunup2PGammab,
        const double representativeWaveRunup2PGammaf,
        const double criticalCumulativeOverload,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double averageNumberOfWavesCtm,
        unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
        unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact,
        const double cumulativeOverloadNFixed,
        const double frontVelocityCu)
        : GrassRevetmentWaveRunupLocationDependentInput(move(name), initialDamage, failureNumber, positionZ, tanA, representativeWaveRunup2PGammab,
                                                        representativeWaveRunup2PGammaf, criticalCumulativeOverload, criticalFrontVelocity,
                                                        increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                                                        move(representative2P), move(waveAngleImpact)),
          _cumulativeOverloadNFixed(cumulativeOverloadNFixed),
          _frontVelocityCu(frontVelocityCu) {}

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveRunupRayleighLocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        return nullptr;
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::GetCumulativeOverloadNFixed() const
    {
        return _cumulativeOverloadNFixed;
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::GetFrontVelocityCu() const
    {
        return _frontVelocityCu;
    }
}

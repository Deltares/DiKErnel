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

#include "GrassRevetmentWaveRunupLocationDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    GrassRevetmentWaveRunupLocationDependentInput::GrassRevetmentWaveRunupLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        const double representativeWaveRunup2PGammab,
        const double representativeWaveRunup2PGammaf)
        : LocationDependentInput(move(name), initialDamage, failureNumber, positionZ),
          _tanA(tanA),
          _representativeWaveRunup2PGammab(representativeWaveRunup2PGammab),
          _representativeWaveRunup2PGammaf(representativeWaveRunup2PGammaf) {}

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveRunupLocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        return nullptr;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetTanA() const
    {
        return _tanA;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetRepresentativeWaveRunup2PGammab() const
    {
        return _representativeWaveRunup2PGammab;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetRepresentativeWaveRunup2PGammaf() const
    {
        return _representativeWaveRunup2PGammaf;
    }
}

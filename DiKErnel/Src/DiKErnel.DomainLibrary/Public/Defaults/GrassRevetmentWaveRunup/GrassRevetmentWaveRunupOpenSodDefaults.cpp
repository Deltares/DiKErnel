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

#include "GrassRevetmentWaveRunupOpenSodDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveRunupOpenSodDefaults::GetCriticalCumulativeOverload() const
    {
        return 7000;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetCriticalFrontVelocity() const
    {
        return 4.3;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetIncreasedLoadTransitionAlphaM() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetReducedStrengthTransitionAlphaS() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 0.92;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetRepresentativeWaveRunup2PAru() const
    {
        return 1.65;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetRepresentativeWaveRunup2PBru() const
    {
        return 4;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetRepresentativeWaveRunup2PCru() const
    {
        return 1.5;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetRepresentativeWaveRunup2PGammab() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetRepresentativeWaveRunup2PGammaf() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetWaveAngleImpactAbeta() const
    {
        return 0.0022;
    }

    double GrassRevetmentWaveRunupOpenSodDefaults::GetWaveAngleImpactBetamax() const
    {
        return 80;
    }
}

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

#include "GrassRevetmentWaveRunupClosedSodDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveRunupClosedSodDefaults::GetCriticalCumulativeOverload() const
    {
        return 7000;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetCriticalFrontVelocity() const
    {
        return 6.6;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetIncreasedLoadTransitionAlphaM() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetReducedStrengthTransitionAlphaS() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 0.92;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetRepresentativeWaveRunup2PAru() const
    {
        return 1.65;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetRepresentativeWaveRunup2PBru() const
    {
        return 4;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetRepresentativeWaveRunup2PCru() const
    {
        return 1.5;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetRepresentativeWaveRunup2PGammab() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetRepresentativeWaveRunup2PGammaf() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetWaveAngleImpactAbeta() const
    {
        return 0.0022;
    }

    double GrassRevetmentWaveRunupClosedSodDefaults::GetWaveAngleImpactBetamax() const
    {
        return 80;
    }
}

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

#include "GrassRevetmentWaveRunupDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveRunupDefaults::GetIncreasedLoadTransitionAlphaM()
    {
        return 1;
    }

    double GrassRevetmentWaveRunupDefaults::GetReducedStrengthTransitionAlphaS()
    {
        return 1;
    }

    double GrassRevetmentWaveRunupDefaults::GetAverageNumberOfWavesCtm()
    {
        return 0.92;
    }

    double GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru()
    {
        return 1.65;
    }

    double GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru()
    {
        return 4;
    }

    double GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru()
    {
        return 1.5;
    }

    double GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab()
    {
        return 1;
    }

    double GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf()
    {
        return 1;
    }

    double GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta()
    {
        return 0.0022;
    }

    double GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax()
    {
        return 80;
    }
}

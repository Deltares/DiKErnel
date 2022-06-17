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

#include "GrassRevetmentWaveRunupOpenSodTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetCriticalCumulativeOverload() const
    {
        return 7000;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetCriticalFrontVelocity() const
    {
        return 4.3;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetIncreasedLoadTransitionAlphaM() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetReducedStrengthTransitionAlphaS() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 0.92;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetRepresentativeWaveRunup2PAru() const
    {
        return 1.65;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetRepresentativeWaveRunup2PBru() const
    {
        return 4;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetRepresentativeWaveRunup2PCru() const
    {
        return 1.5;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetRepresentativeWaveRunup2PGammab() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetRepresentativeWaveRunup2PGammaf() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetWaveAngleImpactAbeta() const
    {
        return 0.0022;
    }

    double GrassRevetmentWaveRunupOpenSodTopLayerDefaults::GetWaveAngleImpactBetamax() const
    {
        return 80;
    }
}

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

#include "GrassRevetmentWaveRunupClosedSodTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetCriticalCumulativeOverload() const
    {
        return 7000;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetCriticalFrontVelocity() const
    {
        return 6.6;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetIncreasedLoadTransitionAlphaM() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetReducedStrengthTransitionAlphaS() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 0.92;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetRepresentativeWaveRunup2PAru() const
    {
        return 1.65;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetRepresentativeWaveRunup2PBru() const
    {
        return 4;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetRepresentativeWaveRunup2PCru() const
    {
        return 1.5;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetRepresentativeWaveRunup2PGammab() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetRepresentativeWaveRunup2PGammaf() const
    {
        return 1;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetWaveAngleImpactAbeta() const
    {
        return 0.0022;
    }

    double GrassRevetmentWaveRunupClosedSodTopLayerDefaults::GetWaveAngleImpactBetamax() const
    {
        return 80;
    }
}

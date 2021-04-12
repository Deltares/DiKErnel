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

#include "GrassRevetmentWaveRunupRepresentative2P.h"

namespace DiKErnel::Integration
{
    GrassRevetmentWaveRunupRepresentative2P::GrassRevetmentWaveRunupRepresentative2P(
        const double representative2PAru,
        const double representative2PBru,
        const double representative2PCru,
        const double gammaB,
        const double gammaF):
        _representative2PAru(representative2PAru),
        _representative2PBru(representative2PBru),
        _representative2PCru(representative2PCru),
        _gammaB(gammaB),
        _gammaF(gammaF) {}

    double GrassRevetmentWaveRunupRepresentative2P::GetRepresentative2PAru() const
    {
        return _representative2PAru;
    }

    double GrassRevetmentWaveRunupRepresentative2P::GetRepresentative2PBru() const
    {
        return _representative2PBru;
    }

    double GrassRevetmentWaveRunupRepresentative2P::GetRepresentative2PCru() const
    {
        return _representative2PCru;
    }

    double GrassRevetmentWaveRunupRepresentative2P::GetGammaB() const
    {
        return _gammaB;
    }

    double GrassRevetmentWaveRunupRepresentative2P::GetGammaF() const
    {
        return _gammaF;
    }
}

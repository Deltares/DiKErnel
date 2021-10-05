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

#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentWaveRunupRayleighLocationConstructionProperties::GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
        string name,
        const double x,
        const double tanA,
        const double positionZ,
        const GrassRevetmentTopLayerType topLayerType)
        : GrassRevetmentWaveRunupLocationConstructionProperties(move(name), x, tanA, positionZ, topLayerType) {}

    #pragma region Set methods

    void GrassRevetmentWaveRunupRayleighLocationConstructionProperties::SetFixedNumberOfWaves(
        unique_ptr<int> fixedNumberOfWaves)
    {
        _fixedNumberOfWaves = move(fixedNumberOfWaves);
    }

    void GrassRevetmentWaveRunupRayleighLocationConstructionProperties::SetFrontVelocityCu(
        unique_ptr<double> frontVelocityCu)
    {
        _frontVelocityCu = move(frontVelocityCu);
    }

    #pragma endregion

    #pragma region Get methods

    const int* GrassRevetmentWaveRunupRayleighLocationConstructionProperties::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves.get();
    }

    const double* GrassRevetmentWaveRunupRayleighLocationConstructionProperties::GetFrontVelocityCu() const
    {
        return _frontVelocityCu.get();
    }

    #pragma endregion
}

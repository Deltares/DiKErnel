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

#include "GrassRevetmentOvertoppingLocationConstructionProperties.h"

#include <utility>

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentOvertoppingLocationConstructionProperties::GrassRevetmentOvertoppingLocationConstructionProperties(
        const double x,
        const GrassRevetmentTopLayerType topLayerType)
        : RevetmentLocationConstructionPropertiesBase(x),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetCriticalCumulativeOverload(
        unique_ptr<double> criticalCumulativeOverload)
    {
        _criticalCumulativeOverload = move(criticalCumulativeOverload);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetCriticalFrontVelocity(
        unique_ptr<double> criticalFrontVelocity)
    {
        _criticalFrontVelocity = move(criticalFrontVelocity);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetIncreasedLoadTransitionAlphaM(
        unique_ptr<double> increasedLoadTransitionAlphaM)
    {
        _increasedLoadTransitionAlphaM = move(increasedLoadTransitionAlphaM);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetReducedStrengthTransitionAlphaS(
        unique_ptr<double> reducedStrengthTransitionAlphaS)
    {
        _reducedStrengthTransitionAlphaS = move(reducedStrengthTransitionAlphaS);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetFixedNumberOfWaves(
        unique_ptr<int> fixedNumberOfWaves)
    {
        _fixedNumberOfWaves = move(fixedNumberOfWaves);
    }

    void GrassRevetmentOvertoppingLocationConstructionProperties::SetFrontVelocityCwo(
        unique_ptr<double> frontVelocityCwo)
    {
        _frontVelocityCwo = move(frontVelocityCwo);
    }

    #pragma endregion

    #pragma region Get methods

    GrassRevetmentTopLayerType GrassRevetmentOvertoppingLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetCriticalCumulativeOverload() const
    {
        return _criticalCumulativeOverload.get();
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetCriticalFrontVelocity() const
    {
        return _criticalFrontVelocity.get();
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM.get();
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS.get();
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const int* GrassRevetmentOvertoppingLocationConstructionProperties::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves.get();
    }

    const double* GrassRevetmentOvertoppingLocationConstructionProperties::GetFrontVelocityCwo() const
    {
        return _frontVelocityCwo.get();
    }

    #pragma endregion
}

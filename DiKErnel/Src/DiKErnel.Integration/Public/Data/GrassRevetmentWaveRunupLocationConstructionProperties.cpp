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

#include "GrassRevetmentWaveRunupLocationConstructionProperties.h"

#include <utility>

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentWaveRunupLocationConstructionProperties::GrassRevetmentWaveRunupLocationConstructionProperties(
        string name,
        const double positionZ,
        const GrassRevetmentTopLayerType topLayerType)
        : RevetmentLocationConstructionPropertiesBase(move(name), positionZ),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetCriticalCumulativeOverload(
        std::unique_ptr<double> criticalCumulativeOverload)
    {
        _criticalCumulativeOverload = move(criticalCumulativeOverload);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetCriticalFrontVelocity(
        std::unique_ptr<double> criticalFrontVelocity)
    {
        _criticalFrontVelocity = move(criticalFrontVelocity);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetIncreasedLoadTransitionAlphaM(
        std::unique_ptr<double> increasedLoadTransitionAlphaM)
    {
        _increasedLoadTransitionAlphaM = move(increasedLoadTransitionAlphaM);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetReducedStrengthTransitionAlphaS(
        std::unique_ptr<double> reducedStrengthTransitionAlphaS)
    {
        _reducedStrengthTransitionAlphaS = move(reducedStrengthTransitionAlphaS);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetAverageNumberOfWavesCtm(
        std::unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetRepresentativeWaveRunup2PAru(
        std::unique_ptr<double> representativeWaveRunup2PAru)
    {
        _representativeWaveRunup2PAru = move(representativeWaveRunup2PAru);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetRepresentativeWaveRunup2PBru(
        std::unique_ptr<double> representativeWaveRunup2PBru)
    {
        _representativeWaveRunup2PBru = move(representativeWaveRunup2PBru);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetRepresentativeWaveRunup2PCru(
        std::unique_ptr<double> representativeWaveRunup2PCru)
    {
        _representativeWaveRunup2PCru = move(representativeWaveRunup2PCru);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetWaveAngleImpactAbeta(
        std::unique_ptr<double> waveAngleImpactAbeta)
    {
        _waveAngleImpactAbeta = move(waveAngleImpactAbeta);
    }

    void GrassRevetmentWaveRunupLocationConstructionProperties::SetWaveAngleImpactBetamax(
        std::unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
    }

    #pragma endregion

    #pragma region Get methods

    GrassRevetmentTopLayerType GrassRevetmentWaveRunupLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetCriticalCumulativeOverload() const
    {
        return _criticalCumulativeOverload.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetCriticalFrontVelocity() const
    {
        return _criticalFrontVelocity.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetRepresentativeWaveRunup2PAru() const
    {
        return _representativeWaveRunup2PAru.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetRepresentativeWaveRunup2PBru() const
    {
        return _representativeWaveRunup2PBru.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetRepresentativeWaveRunup2PCru() const
    {
        return _representativeWaveRunup2PCru.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetWaveAngleImpactAbeta() const
    {
        return _waveAngleImpactAbeta.get();
    }

    const double* GrassRevetmentWaveRunupLocationConstructionProperties::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}

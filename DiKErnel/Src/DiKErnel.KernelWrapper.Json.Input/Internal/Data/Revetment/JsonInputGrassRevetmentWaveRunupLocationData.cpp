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

#include "JsonInputGrassRevetmentWaveRunupLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassRevetmentWaveRunupLocationData::JsonInputGrassRevetmentWaveRunupLocationData(
        const JsonInputGrassRevetmentTopLayerType topLayerType)
        : _topLayerType(topLayerType) { }

    #pragma region Set methods

    void JsonInputGrassRevetmentWaveRunupLocationData::SetCriticalCumulativeOverload(
        unique_ptr<double> criticalCumulativeOverload)
    {
        _criticalCumulativeOverload = move(criticalCumulativeOverload);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetCriticalFrontVelocity(
        unique_ptr<double> criticalFrontVelocity)
    {
        _criticalFrontVelocity = move(criticalFrontVelocity);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetIncreasedLoadTransitionAlphaM(
        unique_ptr<double> increasedLoadTransitionAlphaM)
    {
        _increasedLoadTransitionAlphaM = move(increasedLoadTransitionAlphaM);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetReducedStrengthTransitionAlphaS(
        unique_ptr<double> reducedStrengthTransitionAlphaS)
    {
        _reducedStrengthTransitionAlphaS = move(reducedStrengthTransitionAlphaS);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunup2PAru(
        unique_ptr<double> representativeWaveRunup2PAru)
    {
        _representativeWaveRunup2PAru = move(representativeWaveRunup2PAru);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunup2PBru(
        unique_ptr<double> representativeWaveRunup2PBru)
    {
        _representativeWaveRunup2PBru = move(representativeWaveRunup2PBru);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunup2PCru(
        unique_ptr<double> representativeWaveRunup2PCru)
    {
        _representativeWaveRunup2PCru = move(representativeWaveRunup2PCru);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetWaveAngleImpactAbeta(
        unique_ptr<double> waveAngleImpactAbeta)
    {
        _waveAngleImpactAbeta = move(waveAngleImpactAbeta);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetWaveAngleImpactBetamax(
        unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputGrassRevetmentTopLayerType JsonInputGrassRevetmentWaveRunupLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetCriticalCumulativeOverload() const
    {
        return _criticalCumulativeOverload.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetCriticalFrontVelocity() const
    {
        return _criticalFrontVelocity.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunup2PAru() const
    {
        return _representativeWaveRunup2PAru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunup2PBru() const
    {
        return _representativeWaveRunup2PBru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunup2PCru() const
    {
        return _representativeWaveRunup2PCru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetWaveAngleImpactAbeta() const
    {
        return _waveAngleImpactAbeta.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}

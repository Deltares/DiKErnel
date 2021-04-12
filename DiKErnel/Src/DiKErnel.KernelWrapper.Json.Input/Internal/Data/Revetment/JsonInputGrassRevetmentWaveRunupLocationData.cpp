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

    void JsonInputGrassRevetmentWaveRunupLocationData::SetAverageNumberWaveTimeStepCtm(
        unique_ptr<double> averageNumberWaveTimeStepCtm)
    {
        _averageNumberWaveTimeStepCtm = move(averageNumberWaveTimeStepCtm);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunUp2PAru(
        unique_ptr<double> representativeWaveRunUp2PAru)
    {
        _representativeWaveRunUp2PAru = move(representativeWaveRunUp2PAru);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunUp2PBru(
        unique_ptr<double> representativeWaveRunUp2PBru)
    {
        _representativeWaveRunUp2PBru = move(representativeWaveRunUp2PBru);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetRepresentativeWaveRunUp2PCru(
        unique_ptr<double> representativeWaveRunUp2PCru)
    {
        _representativeWaveRunUp2PCru = move(representativeWaveRunUp2PCru);
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

    void JsonInputGrassRevetmentWaveRunupLocationData::SetCumulativeOverloadTimeStepNf(
        std::unique_ptr<double> cumulativeOverloadTimeStepNf)
    {
        _cumulativeOverloadTimeStepNf = move(cumulativeOverloadTimeStepNf);
    }

    void JsonInputGrassRevetmentWaveRunupLocationData::SetFrontVelocityCu(
        std::unique_ptr<double> frontVelocityCu)
    {
        _frontVelocityCu = move(frontVelocityCu);
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

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetAverageNumberWaveTimeStepCtm() const
    {
        return _averageNumberWaveTimeStepCtm.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunUp2PAru() const
    {
        return _representativeWaveRunUp2PAru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunUp2PBru() const
    {
        return _representativeWaveRunUp2PBru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetRepresentativeWaveRunUp2PCru() const
    {
        return _representativeWaveRunUp2PCru.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetWaveAngleImpactAbeta() const
    {
        return _waveAngleImpactAbeta.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetCumulativeOverloadTimeStepNf() const
    {
        return _cumulativeOverloadTimeStepNf.get();
    }

    const double* JsonInputGrassRevetmentWaveRunupLocationData::GetFrontVelocityCu() const
    {
        return _frontVelocityCu.get();
    }

    #pragma endregion
}

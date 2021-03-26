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

#include "JsonInputGrassWaveImpactRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassWaveImpactRevetmentLocationData::JsonInputGrassWaveImpactRevetmentLocationData(
        const TopLayerType topLayerType)
        : JsonInputRevetmentLocationData(0, 0),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

    void JsonInputGrassWaveImpactRevetmentLocationData::SetFailureTimeAgwi(
        std::unique_ptr<double> failureTimeAgwi)
    {
        _failureTimeAgwi = move(failureTimeAgwi);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetFailureTimeBgwi(
        std::unique_ptr<double> failureTimeBgwi)
    {
        _failureTimeBgwi = move(failureTimeBgwi);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetFailureTimeCgwi(
        std::unique_ptr<double> failureTimeCgwi)
    {
        _failureTimeCgwi = move(failureTimeCgwi);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetMinimumWaveHeightTemax(
        std::unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetMinimumWaveHeightTemin(
        std::unique_ptr<double> minimumWaveHeightTemin)
    {
        _minimumWaveHeightTemin = move(minimumWaveHeightTemin);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetWaveAngleImpactNwa(
        std::unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetWaveAngleImpactQwa(
        std::unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetWaveAngleImpactRwa(
        std::unique_ptr<double> waveAngleImpactRwa)
    {
        _waveAngleImpactRwa = move(waveAngleImpactRwa);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputGrassWaveImpactRevetmentLocationData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputGrassWaveImpactRevetmentLocationData::TopLayerType JsonInputGrassWaveImpactRevetmentLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetFailureTimeAgwi() const
    {
        return _failureTimeAgwi.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetFailureTimeBgwi() const
    {
        return _failureTimeBgwi.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetFailureTimeCgwi() const
    {
        return _failureTimeCgwi.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetMinimumWaveHeightTemin() const
    {
        return _minimumWaveHeightTemin.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetWaveAngleImpactNwa() const
    {
        return _waveAngleImpactNwa.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetWaveAngleImpactQwa() const
    {
        return _waveAngleImpactQwa.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetWaveAngleImpactRwa() const
    {
        return _waveAngleImpactRwa.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputGrassWaveImpactRevetmentLocationData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    #pragma endregion
}

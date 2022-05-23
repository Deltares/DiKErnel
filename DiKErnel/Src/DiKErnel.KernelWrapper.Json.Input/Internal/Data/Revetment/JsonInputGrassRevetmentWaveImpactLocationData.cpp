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

#include "JsonInputGrassRevetmentWaveImpactLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassRevetmentWaveImpactLocationData::JsonInputGrassRevetmentWaveImpactLocationData(
        const JsonInputGrassRevetmentTopLayerType topLayerType)
        : _topLayerType(topLayerType) { }

    #pragma region Set methods

    void JsonInputGrassRevetmentWaveImpactLocationData::SetTimeLineAgwi(
        unique_ptr<double> timeLineAgwi)
    {
        _timeLineAgwi = move(timeLineAgwi);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetTimeLineBgwi(
        unique_ptr<double> timeLineBgwi)
    {
        _timeLineBgwi = move(timeLineBgwi);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetTimeLineCgwi(
        unique_ptr<double> timeLineCgwi)
    {
        _timeLineCgwi = move(timeLineCgwi);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetMinimumWaveHeightTemax(
        unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetMaximumWaveHeightTemin(
        unique_ptr<double> maximumWaveHeightTemin)
    {
        _maximumWaveHeightTemin = move(maximumWaveHeightTemin);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetWaveAngleImpactNwa(
        unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetWaveAngleImpactQwa(
        unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetWaveAngleImpactRwa(
        unique_ptr<double> waveAngleImpactRwa)
    {
        _waveAngleImpactRwa = move(waveAngleImpactRwa);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputGrassRevetmentWaveImpactLocationData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputGrassRevetmentTopLayerType JsonInputGrassRevetmentWaveImpactLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetTimeLineAgwi() const
    {
        return _timeLineAgwi.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetTimeLineBgwi() const
    {
        return _timeLineBgwi.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetTimeLineCgwi() const
    {
        return _timeLineCgwi.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetMaximumWaveHeightTemin() const
    {
        return _maximumWaveHeightTemin.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetWaveAngleImpactNwa() const
    {
        return _waveAngleImpactNwa.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetWaveAngleImpactQwa() const
    {
        return _waveAngleImpactQwa.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetWaveAngleImpactRwa() const
    {
        return _waveAngleImpactRwa.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputGrassRevetmentWaveImpactLocationData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    #pragma endregion
}

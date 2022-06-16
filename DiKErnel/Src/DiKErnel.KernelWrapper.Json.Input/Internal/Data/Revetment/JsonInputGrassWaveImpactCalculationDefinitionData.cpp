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

#include "JsonInputGrassWaveImpactCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetTimeLineAgwi(
        unique_ptr<double> timeLineAgwi)
    {
        _timeLineAgwi = move(timeLineAgwi);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetTimeLineBgwi(
        unique_ptr<double> timeLineBgwi)
    {
        _timeLineBgwi = move(timeLineBgwi);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetTimeLineCgwi(
        unique_ptr<double> timeLineCgwi)
    {
        _timeLineCgwi = move(timeLineCgwi);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetMinimumWaveHeightTemax(
        unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetMaximumWaveHeightTemin(
        unique_ptr<double> maximumWaveHeightTemin)
    {
        _maximumWaveHeightTemin = move(maximumWaveHeightTemin);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactNwa(
        unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactQwa(
        unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactRwa(
        unique_ptr<double> waveAngleImpactRwa)
    {
        _waveAngleImpactRwa = move(waveAngleImpactRwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetTimeLineAgwi() const
    {
        return _timeLineAgwi.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetTimeLineBgwi() const
    {
        return _timeLineBgwi.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetTimeLineCgwi() const
    {
        return _timeLineCgwi.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetMaximumWaveHeightTemin() const
    {
        return _maximumWaveHeightTemin.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactNwa() const
    {
        return _waveAngleImpactNwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactQwa() const
    {
        return _waveAngleImpactQwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactRwa() const
    {
        return _waveAngleImpactRwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    #pragma endregion
}

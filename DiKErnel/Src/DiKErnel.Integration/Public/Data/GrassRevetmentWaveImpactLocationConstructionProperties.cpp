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

#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"

#include <utility>

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentWaveImpactLocationConstructionProperties::GrassRevetmentWaveImpactLocationConstructionProperties(
        string name,
        const double x,
        const GrassRevetmentTopLayerType topLayerType)
        : RevetmentLocationConstructionPropertiesBase(move(name), x),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetTimeLineAgwi(
        unique_ptr<double> timeLineAgwi)
    {
        _timeLineAgwi = move(timeLineAgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetTimeLineBgwi(
        unique_ptr<double> timeLineBgwi)
    {
        _timeLineBgwi = move(timeLineBgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetTimeLineCgwi(
        unique_ptr<double> timeLineCgwi)
    {
        _timeLineCgwi = move(timeLineCgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetMinimumWaveHeightTemax(
        unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetMaximumWaveHeightTemin(
        unique_ptr<double> maximumWaveHeightTemin)
    {
        _maximumWaveHeightTemin = move(maximumWaveHeightTemin);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactNwa(
        unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactQwa(
        unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactRwa(
        unique_ptr<double> waveAngleImpactRwa)
    {
        _waveAngleImpactRwa = move(waveAngleImpactRwa);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    #pragma endregion

    #pragma region Get methods

    GrassRevetmentTopLayerType GrassRevetmentWaveImpactLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetTimeLineAgwi() const
    {
        return _timeLineAgwi.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetTimeLineBgwi() const
    {
        return _timeLineBgwi.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetTimeLineCgwi() const
    {
        return _timeLineCgwi.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetMaximumWaveHeightTemin() const
    {
        return _maximumWaveHeightTemin.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetWaveAngleImpactNwa() const
    {
        return _waveAngleImpactNwa.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetWaveAngleImpactQwa() const
    {
        return _waveAngleImpactQwa.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetWaveAngleImpactRwa() const
    {
        return _waveAngleImpactRwa.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    #pragma endregion
}

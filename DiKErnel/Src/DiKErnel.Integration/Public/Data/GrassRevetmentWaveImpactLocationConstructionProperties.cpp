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

    using TopLayerType = GrassRevetmentWaveImpactLocationConstructionProperties::TopLayerType;

    GrassRevetmentWaveImpactLocationConstructionProperties::GrassRevetmentWaveImpactLocationConstructionProperties(
        string name,
        const double tanA,
        const double positionZ,
        const TopLayerType topLayerType)
        : RevetmentLocationConstructionPropertiesBase(move(name), tanA, positionZ),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetFailureTimeAgwi(
        std::unique_ptr<double> failureTimeAgwi)
    {
        _failureTimeAgwi = move(failureTimeAgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetFailureTimeBgwi(
        std::unique_ptr<double> failureTimeBgwi)
    {
        _failureTimeBgwi = move(failureTimeBgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetFailureTimeCgwi(
        std::unique_ptr<double> failureTimeCgwi)
    {
        _failureTimeCgwi = move(failureTimeCgwi);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetMinimumWaveHeightTemax(
        std::unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetMaximumWaveHeightTemin(
        std::unique_ptr<double> maximumWaveHeightTemin)
    {
        _maximumWaveHeightTemin = move(maximumWaveHeightTemin);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactNwa(
        std::unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactQwa(
        std::unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void GrassRevetmentWaveImpactLocationConstructionProperties::SetWaveAngleImpactRwa(
        std::unique_ptr<double> waveAngleImpactRwa)
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

    TopLayerType GrassRevetmentWaveImpactLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetFailureTimeAgwi() const
    {
        return _failureTimeAgwi.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetFailureTimeBgwi() const
    {
        return _failureTimeBgwi.get();
    }

    const double* GrassRevetmentWaveImpactLocationConstructionProperties::GetFailureTimeCgwi() const
    {
        return _failureTimeCgwi.get();
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

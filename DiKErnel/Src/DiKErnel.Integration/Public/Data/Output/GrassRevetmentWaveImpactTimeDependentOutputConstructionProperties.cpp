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

#include "GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties(
        const double incrementDamage,
        const double damage,
        unique_ptr<int> timeOfFailure)
        : TimeDependentOutputConstructionProperties(incrementDamage, damage, move(timeOfFailure)) {}

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetLoadingRevetment(
        const bool loadingRevetment)
    {
        _loadingRevetment = loadingRevetment;
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetUpperLimitLoading(
        const double upperLimitLoading)
    {
        _upperLimitLoading = upperLimitLoading;
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetLowerLimitLoading(
        const double lowerLimitLoading)
    {
        _lowerLimitLoading = lowerLimitLoading;
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetMinimumWaveHeight(
        unique_ptr<double> minimumWaveHeight)
    {
        _minimumWaveHeight = move(minimumWaveHeight);
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetMaximumWaveHeight(
        unique_ptr<double> maximumWaveHeight)
    {
        _maximumWaveHeight = move(maximumWaveHeight);
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetWaveAngleImpact(
        unique_ptr<double> waveAngleImpact)
    {
        _waveAngleImpact = move(waveAngleImpact);
    }

    void GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetWaveHeightImpact(
        unique_ptr<double> waveHeightImpact)
    {
        _waveHeightImpact = move(waveHeightImpact);
    }

    bool GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetLoadingRevetment() const
    {
        return _loadingRevetment;
    }

    double GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetUpperLimitLoading() const
    {
        return _upperLimitLoading;
    }

    double GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetLowerLimitLoading() const
    {
        return _lowerLimitLoading;
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetMinimumWaveHeight() const
    {
        return _minimumWaveHeight.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetMaximumWaveHeight() const
    {
        return _maximumWaveHeight.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetWaveAngleImpact() const
    {
        return _waveAngleImpact.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetWaveHeightImpact() const
    {
        return _waveHeightImpact.get();
    }
}

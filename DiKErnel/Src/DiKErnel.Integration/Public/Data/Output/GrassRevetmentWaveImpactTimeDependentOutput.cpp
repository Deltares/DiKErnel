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

#include "GrassRevetmentWaveImpactTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentWaveImpactTimeDependentOutput::GrassRevetmentWaveImpactTimeDependentOutput(
        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties& constructionProperties)
        : TimeDependentOutput(constructionProperties),
          _loadingRevetment(move(constructionProperties._loadingRevetment)),
          _upperLimitLoading(move(constructionProperties._upperLimitLoading)),
          _lowerLimitLoading(move(constructionProperties._lowerLimitLoading)),
          _minimumWaveHeight(move(constructionProperties._minimumWaveHeight)),
          _maximumWaveHeight(move(constructionProperties._maximumWaveHeight)),
          _waveAngleImpact(move(constructionProperties._waveAngleImpact)),
          _waveHeightImpact(move(constructionProperties._waveHeightImpact)) {}

    bool GrassRevetmentWaveImpactTimeDependentOutput::GetLoadingRevetment() const
    {
        return *_loadingRevetment;
    }

    double GrassRevetmentWaveImpactTimeDependentOutput::GetUpperLimitLoading() const
    {
        return *_upperLimitLoading;
    }

    double GrassRevetmentWaveImpactTimeDependentOutput::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoading;
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutput::GetMinimumWaveHeight() const
    {
        return _minimumWaveHeight.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutput::GetMaximumWaveHeight() const
    {
        return _maximumWaveHeight.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutput::GetWaveAngleImpact() const
    {
        return _waveAngleImpact.get();
    }

    const double* GrassRevetmentWaveImpactTimeDependentOutput::GetWaveHeightImpact() const
    {
        return _waveHeightImpact.get();
    }
}

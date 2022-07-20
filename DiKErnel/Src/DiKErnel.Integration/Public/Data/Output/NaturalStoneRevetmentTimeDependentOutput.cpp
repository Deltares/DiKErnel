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

#include "NaturalStoneRevetmentTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace std;

    NaturalStoneRevetmentTimeDependentOutput::NaturalStoneRevetmentTimeDependentOutput(
        NaturalStoneRevetmentTimeDependentOutputConstructionProperties& constructionProperties)
        : TimeDependentOutput(constructionProperties),
          _outerSlope(move(constructionProperties._outerSlope)),
          _slopeUpperLevel(move(constructionProperties._slopeUpperLevel)),
          _slopeUpperPosition(move(constructionProperties._slopeUpperPosition)),
          _slopeLowerLevel(move(constructionProperties._slopeLowerLevel)),
          _slopeLowerPosition(move(constructionProperties._slopeLowerPosition)),
          _loadingRevetment(move(constructionProperties._loadingRevetment)),
          _surfSimilarityParameter(move(constructionProperties._surfSimilarityParameter)),
          _waveSteepnessDeepWater(move(constructionProperties._waveSteepnessDeepWater)),
          _upperLimitLoading(move(constructionProperties._upperLimitLoading)),
          _lowerLimitLoading(move(constructionProperties._lowerLimitLoading)),
          _depthMaximumWaveLoad(move(constructionProperties._depthMaximumWaveLoad)),
          _distanceMaximumWaveElevation(move(constructionProperties._distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpact(move(constructionProperties._normativeWidthOfWaveImpact)),
          _hydraulicLoad(move(constructionProperties._hydraulicLoad)),
          _waveAngleImpact(move(constructionProperties._waveAngleImpact)),
          _resistance(move(constructionProperties._resistance)),
          _referenceTimeDegradation(move(constructionProperties._referenceTimeDegradation)),
          _referenceDegradation(move(constructionProperties._referenceDegradation)) {}

    double NaturalStoneRevetmentTimeDependentOutput::GetOuterSlope() const
    {
        return *_outerSlope;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeUpperLevel() const
    {
        return *_slopeUpperLevel;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeUpperPosition() const
    {
        return *_slopeUpperPosition;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeLowerLevel() const
    {
        return *_slopeLowerLevel;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeLowerPosition() const
    {
        return *_slopeLowerPosition;
    }

    bool NaturalStoneRevetmentTimeDependentOutput::GetLoadingRevetment() const
    {
        return *_loadingRevetment;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSurfSimilarityParameter() const
    {
        return *_surfSimilarityParameter;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetWaveSteepnessDeepWater() const
    {
        return *_waveSteepnessDeepWater;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetUpperLimitLoading() const
    {
        return *_upperLimitLoading;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoading;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetDepthMaximumWaveLoad() const
    {
        return *_depthMaximumWaveLoad;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetDistanceMaximumWaveElevation() const
    {
        return *_distanceMaximumWaveElevation;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpact;
    }

    const double* NaturalStoneRevetmentTimeDependentOutput::GetHydraulicLoad() const
    {
        return _hydraulicLoad.get();
    }

    const double* NaturalStoneRevetmentTimeDependentOutput::GetWaveAngleImpact() const
    {
        return _waveAngleImpact.get();
    }

    const double* NaturalStoneRevetmentTimeDependentOutput::GetResistance() const
    {
        return _resistance.get();
    }

    const double* NaturalStoneRevetmentTimeDependentOutput::GetReferenceTimeDegradation() const
    {
        return _referenceTimeDegradation.get();
    }

    const double* NaturalStoneRevetmentTimeDependentOutput::GetReferenceDegradation() const
    {
        return _referenceDegradation.get();
    }
}

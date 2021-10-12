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

#include "NaturalStoneRevetmentTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace std;

    NaturalStoneRevetmentTimeDependentOutput::NaturalStoneRevetmentTimeDependentOutput(
        const double incrementDamage,
        const double damage,
        unique_ptr<int> timeOfFailure,
        const double outerSlope,
        const double slopeUpperLevel,
        const double slopeUpperPosition,
        const double slopeLowerLevel,
        const double slopeLowerPosition,
        const bool loadingRevetment,
        const double surfSimilarityParameter,
        const double waveSteepnessDeepWater,
        const double upperLimitLoading,
        const double lowerLimitLoading,
        const double depthMaximumWaveLoad,
        const double distanceMaximumWaveElevation,
        const double normativeWidthOfWaveImpact,
        unique_ptr<double> hydraulicLoad,
        unique_ptr<double> waveAngleImpact,
        unique_ptr<double> resistance,
        unique_ptr<double> referenceTimeDegradation,
        unique_ptr<double> referenceDegradation)
        : TimeDependentOutput(incrementDamage, damage, move(timeOfFailure)),
          _outerSlope(outerSlope),
          _slopeUpperLevel(slopeUpperLevel),
          _slopeUpperPosition(slopeUpperPosition),
          _slopeLowerLevel(slopeLowerLevel),
          _slopeLowerPosition(slopeLowerPosition),
          _loadingRevetment(loadingRevetment),
          _surfSimilarityParameter(surfSimilarityParameter),
          _waveSteepnessDeepWater(waveSteepnessDeepWater),
          _upperLimitLoading(upperLimitLoading),
          _lowerLimitLoading(lowerLimitLoading),
          _depthMaximumWaveLoad(depthMaximumWaveLoad),
          _distanceMaximumWaveElevation(distanceMaximumWaveElevation),
          _normativeWidthOfWaveImpact(normativeWidthOfWaveImpact),
          _hydraulicLoad(move(hydraulicLoad)),
          _waveAngleImpact(move(waveAngleImpact)),
          _resistance(move(resistance)),
          _referenceTimeDegradation(move(referenceTimeDegradation)),
          _referenceDegradation(move(referenceDegradation)) {}

    double NaturalStoneRevetmentTimeDependentOutput::GetOuterSlope() const
    {
        return _outerSlope;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeUpperLevel() const
    {
        return _slopeUpperLevel;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeUpperPosition() const
    {
        return _slopeUpperPosition;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeLowerLevel() const
    {
        return _slopeLowerLevel;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSlopeLowerPosition() const
    {
        return _slopeLowerPosition;
    }

    bool NaturalStoneRevetmentTimeDependentOutput::GetLoadingRevetment() const
    {
        return _loadingRevetment;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetSurfSimilarityParameter() const
    {
        return _surfSimilarityParameter;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetWaveSteepnessDeepWater() const
    {
        return _waveSteepnessDeepWater;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetUpperLimitLoading() const
    {
        return _upperLimitLoading;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetLowerLimitLoading() const
    {
        return _lowerLimitLoading;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetDepthMaximumWaveLoad() const
    {
        return _depthMaximumWaveLoad;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetDistanceMaximumWaveElevation() const
    {
        return _distanceMaximumWaveElevation;
    }

    double NaturalStoneRevetmentTimeDependentOutput::GetNormativeWidthOfWaveImpact() const
    {
        return _normativeWidthOfWaveImpact;
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

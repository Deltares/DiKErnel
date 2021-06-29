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
        const double damage,
        unique_ptr<int> timeOfFailure,
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
        unique_ptr<double> referenceDegradation,
        const double incrementDamage)
        : TimeDependentOutput(damage, move(timeOfFailure)),
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
          _referenceDegradation(move(referenceDegradation)),
          _incrementDamage(incrementDamage) {}
}

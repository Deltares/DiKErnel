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

#include "NaturalStoneRevetment.h"

#include <algorithm>
#include <cmath>

#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double NaturalStoneRevetment::IncrementDamage(
        const double hydraulicLoad,
        const double resistance,
        const double incrementDegradation,
        const double waveAngleImpact)
    {
        return hydraulicLoad / resistance * incrementDegradation * waveAngleImpact;
    }

    double NaturalStoneRevetment::HydraulicLoad(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double hydraulicLoadOnXib,
        const double hydraulicLoadOnAp,
        const double hydraulicLoadOnBp,
        const double hydraulicLoadOnCp,
        const double hydraulicLoadOnNp,
        const double hydraulicLoadOnAs,
        const double hydraulicLoadOnBs,
        const double hydraulicLoadOnCs,
        const double hydraulicLoadOnNs)
    {
        const auto usePurgingBreakers = hydraulicLoadOnXib - surfSimilarityParameter >= 0.0;
        const auto hydraulicLoadOnA = usePurgingBreakers
                                          ? hydraulicLoadOnAp
                                          : hydraulicLoadOnAs;
        const auto hydraulicLoadOnB = usePurgingBreakers
                                          ? hydraulicLoadOnBp
                                          : hydraulicLoadOnBs;
        const auto hydraulicLoadOnC = usePurgingBreakers
                                          ? hydraulicLoadOnCp
                                          : hydraulicLoadOnCs;
        const auto hydraulicLoadOnN = usePurgingBreakers
                                          ? hydraulicLoadOnNp
                                          : hydraulicLoadOnNs;

        return waveHeightHm0 / (hydraulicLoadOnA * pow(surfSimilarityParameter, hydraulicLoadOnN)
            + hydraulicLoadOnB * surfSimilarityParameter
            + hydraulicLoadOnC);
    }

    double NaturalStoneRevetment::UpperLimitLoading(
        const double depthMaximumWaveLoad,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingOfAul,
        const double upperLimitLoadingOfBul,
        const double upperLimitLoadingOfCul)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoad
                + max(depthMaximumWaveLoad + upperLimitLoadingOfAul,
                      upperLimitLoadingOfBul * waveHeightHm0 * min(surfSimilarityParameter,
                                                                   upperLimitLoadingOfCul));
    }

    double NaturalStoneRevetment::LowerLimitLoading(
        const double depthMaximumWaveLoad,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingOfAll,
        const double lowerLimitLoadingOfBll,
        const double lowerLimitLoadingOfCll)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoad
                + min(depthMaximumWaveLoad - lowerLimitLoadingOfAll,
                      lowerLimitLoadingOfBll * waveHeightHm0 * min(surfSimilarityParameter,
                                                                   lowerLimitLoadingOfCll));
    }

    double NaturalStoneRevetment::DepthMaximumWaveLoad(
        const double distanceMaximumWaveElevation,
        const double normativeWidthOfWaveImpact,
        const double slopeAngle)
    {
        return (distanceMaximumWaveElevation - 0.5 * normativeWidthOfWaveImpact * cos(Generic::Radians(slopeAngle)))
                * tan(Generic::Radians(slopeAngle));
    }

    double NaturalStoneRevetment::DistanceMaximumWaveElevation(
        const double impactShallowWater,
        const double waveSteepnessDeepWater,
        const double waveHeightHm0,
        const double distanceMaximumWaveElevationAsmax,
        const double distanceMaximumWaveElevationBsmax)
    {
        return waveHeightHm0
                * (distanceMaximumWaveElevationAsmax / sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationBsmax)
                * impactShallowWater;
    }

    double NaturalStoneRevetment::ImpactShallowWater()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::NormativeWidthOfWaveImpact(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double normativeWidthOfWaveImpactAwi,
        const double normativeWidthOfWaveImpactBwi)
    {
        return (normativeWidthOfWaveImpactAwi - normativeWidthOfWaveImpactBwi * surfSimilarityParameter)
                * waveHeightHm0;
    }

    double NaturalStoneRevetment::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactOnBetamax)
    {
        return pow(cos(Generic::Radians(min(waveAngleImpactOnBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetment::Resistance(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::IncrementDegradation(
        const double referenceTimeDegradation,
        const double wavePeriodTm10,
        const double incrementTime)
    {
        return Degradation(referenceTimeDegradation + incrementTime, wavePeriodTm10)
                - Degradation(referenceTimeDegradation, wavePeriodTm10);
    }

    double NaturalStoneRevetment::Degradation(
        const double referenceTimeDegradation,
        const double wavePeriodTm10)
    {
        return pow(referenceTimeDegradation / (wavePeriodTm10 * 1000.0), 0.1);
    }

    double NaturalStoneRevetment::ReferenceTimeDegradation(
        const double referenceDegradation,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceDegradation, 10.0);
    }

    double NaturalStoneRevetment::ReferenceDegradation(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double initialDamage)
    {
        return initialDamage * (resistance / hydraulicLoad) * (1.0 / waveAngleImpact);
    }

    double NaturalStoneRevetment::DurationInTimeStepFailure(
        const double referenceTimeFailure,
        const double referenceTimeDegradation)
    {
        return referenceTimeFailure - referenceTimeDegradation;
    }

    double NaturalStoneRevetment::ReferenceTimeFailure(
        const double referenceFailure,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceFailure, 10.0);
    }

    double NaturalStoneRevetment::ReferenceFailure(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double failureNumber)
    {
        return failureNumber * (resistance / hydraulicLoad) * (1.0 / waveAngleImpact);
    }
}

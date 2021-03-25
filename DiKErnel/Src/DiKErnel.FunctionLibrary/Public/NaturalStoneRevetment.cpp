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

#include "Revetment.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double NaturalStoneRevetment::CalculateIncrementDamageOfNaturalStone(
        const double hydraulicLoadOnNaturalStone,
        const double resistanceOfNaturalStone,
        const double incrementDegradationOfNaturalStone,
        const double loadingOfRevetment,
        const double waveAngleImpactOnNaturalStone)
    {
        return hydraulicLoadOnNaturalStone / resistanceOfNaturalStone * incrementDegradationOfNaturalStone * loadingOfRevetment
                * waveAngleImpactOnNaturalStone;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoadOnNaturalStone(
        const double waveHeightHm0,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs,
        const double surfSimilarityParameter)
    {
        const auto usePurgingBreakers = hydraulicLoadOnNaturalStoneXib - surfSimilarityParameter >= 0.0;
        const auto hydraulicLoadOnNaturalStoneA = usePurgingBreakers
                                                      ? hydraulicLoadOnNaturalStoneAp
                                                      : hydraulicLoadOnNaturalStoneAs;
        const auto hydraulicLoadOnNaturalStoneB = usePurgingBreakers
                                                      ? hydraulicLoadOnNaturalStoneBp
                                                      : hydraulicLoadOnNaturalStoneBs;
        const auto hydraulicLoadOnNaturalStoneC = usePurgingBreakers
                                                      ? hydraulicLoadOnNaturalStoneCp
                                                      : hydraulicLoadOnNaturalStoneCs;
        const auto hydraulicLoadOnNaturalStoneN = usePurgingBreakers
                                                      ? hydraulicLoadOnNaturalStoneNp
                                                      : hydraulicLoadOnNaturalStoneNs;

        return waveHeightHm0 / (hydraulicLoadOnNaturalStoneA * pow(surfSimilarityParameter, hydraulicLoadOnNaturalStoneN)
            + hydraulicLoadOnNaturalStoneB * surfSimilarityParameter
            + hydraulicLoadOnNaturalStoneC);
    }

    double NaturalStoneRevetment::CalculateUpperLimitLoadingOfNaturalStone(
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingOfNaturalStoneAul,
        const double upperLimitLoadingOfNaturalStoneBul,
        const double upperLimitLoadingOfNaturalStoneCul,
        const double depthMaximumWaveLoadNaturalStone,
        const double surfSimilarityParameter)
    {
        return waterLevel
                - 2 * depthMaximumWaveLoadNaturalStone
                + max(depthMaximumWaveLoadNaturalStone + upperLimitLoadingOfNaturalStoneAul,
                      upperLimitLoadingOfNaturalStoneBul * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               upperLimitLoadingOfNaturalStoneCul));
    }

    double NaturalStoneRevetment::CalculateLowerLimitLoadingOfNaturalStone(
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingOfNaturalStoneAll,
        const double lowerLimitLoadingOfNaturalStoneBll,
        const double lowerLimitLoadingOfNaturalStoneCll,
        const double depthMaximumWaveLoadNaturalStone,
        const double surfSimilarityParameter)
    {
        return waterLevel
                - 2 * depthMaximumWaveLoadNaturalStone
                + min(depthMaximumWaveLoadNaturalStone - lowerLimitLoadingOfNaturalStoneAll,
                      lowerLimitLoadingOfNaturalStoneBll * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               lowerLimitLoadingOfNaturalStoneCll));
    }

    double NaturalStoneRevetment::CalculateDepthMaximumWaveLoadNaturalStone(
        const double distanceMaximumWaveElevationNaturalStone,
        const double normativeWidthOfWaveImpact,
        const double slopeAngle)
    {
        return (distanceMaximumWaveElevationNaturalStone - 0.5 * normativeWidthOfWaveImpact * cos(Revetment::DegreesToRadians(slopeAngle)))
                * tan(Revetment::DegreesToRadians(slopeAngle));
    }

    double NaturalStoneRevetment::CalculateDistanceMaximumWaveElevationNaturalStone(
        const double waveHeightHm0,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax,
        const double impactShallowWaterNaturalStone,
        const double waveSteepnessDeepWater)
    {
        return waveHeightHm0
                * (distanceMaximumWaveElevationNaturalStoneAsmax / sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationNaturalStoneBsmax)
                * impactShallowWaterNaturalStone;
    }

    double NaturalStoneRevetment::CalculateImpactShallowWaterNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::CalculateNormativeWidthOfWaveImpactNaturalStone(
        const double waveHeightHm0,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi,
        const double surfSimilarityParameter)
    {
        return (normativeWidthOfWaveImpactNaturalStoneAwi - normativeWidthOfWaveImpactNaturalStoneBwi * surfSimilarityParameter)
                * waveHeightHm0;
    }

    double NaturalStoneRevetment::CalculateResistanceOfNaturalStone(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::CalculateIncrementDegradationOfNaturalStone(
        const double wavePeriodTm10,
        const double incrementOfTime,
        const double referenceTimeDegradationOfNaturalStone)
    {
        return CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone + incrementOfTime, wavePeriodTm10)
                - CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone, wavePeriodTm10);
    }

    double NaturalStoneRevetment::CalculateReferenceTimeDegradationOfNaturalStone(
        const double wavePeriodTm10,
        const double referenceDegradationOfNaturalStone)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceDegradationOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::CalculateDegradationOfNaturalStone(
        const double referenceTimeDegradation,
        const double wavePeriodTm10)
    {
        return pow(referenceTimeDegradation / (wavePeriodTm10 * 1000.0), 0.1);
    }

    double NaturalStoneRevetment::CalculateReferenceDegradationOfNaturalStone(
        const double initialDamage,
        const double resistanceOfNaturalStone,
        const double hydraulicLoadOnNaturalStone,
        const double waveAngleImpactOnNaturalStone)
    {
        return initialDamage * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpactOnNaturalStone(
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax)
    {
        return pow(cos(Revetment::DegreesToRadians(min(waveAngleImpactOnNaturalStoneBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetment::CalculateDurationInTimeStepFailureNaturalStone(
        const double referenceTimeFailureOfNaturalStone,
        const double referenceTimeDegradationOfNaturalStone)
    {
        return referenceTimeFailureOfNaturalStone - referenceTimeDegradationOfNaturalStone;
    }

    double NaturalStoneRevetment::CalculateReferenceTimeFailureOfNaturalStone(
        const double wavePeriodTm10,
        const double referenceFailureOfNaturalStone)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceFailureOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::CalculateReferenceFailureOfNaturalStone(
        const double failureNumber,
        const double resistanceOfNaturalStone,
        const double hydraulicLoadOnNaturalStone,
        const double waveAngleImpactOnNaturalStone)
    {
        return failureNumber * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }
}

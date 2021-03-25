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
        const double startTime,
        const double endTime,
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double positionZ,
        const double upperLimitLoadingOfRevetment,
        const double lowerLimitLoadingOfRevetment,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(
            relativeDensity,
            thicknessTopLayer);
        const auto incrementDegradationOfNaturalStone = CalculateIncrementDegradationOfNaturalStone(
            startTime,
            endTime,
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto loadingOfRevetment = Revetment::CalculateLoadingOfRevetment(
            positionZ,
            upperLimitLoadingOfRevetment,
            lowerLimitLoadingOfRevetment);
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone(
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax);

        return hydraulicLoadOnNaturalStone / resistanceOfNaturalStone * incrementDegradationOfNaturalStone * loadingOfRevetment
                * waveAngleImpactOnNaturalStone;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoadOnNaturalStone(
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto surfSimilarityParameter = Revetment::CalculateSurfSimilarityParameter(
            tanA,
            waveHeightHm0,
            wavePeriodTm10);
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
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi,
        const double upperLimitLoadingOfNaturalStoneAul,
        const double upperLimitLoadingOfNaturalStoneBul,
        const double upperLimitLoadingOfNaturalStoneCul)
    {
        const auto depthMaximumWaveLoadNaturalStone = CalculateDepthMaximumWaveLoadNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            distanceMaximumWaveElevationNaturalStoneAsmax,
            distanceMaximumWaveElevationNaturalStoneBsmax,
            normativeWidthOfWaveImpactNaturalStoneAwi,
            normativeWidthOfWaveImpactNaturalStoneBwi);
        const auto surfSimilarityParameter = Revetment::CalculateSurfSimilarityParameter(
            tanA,
            waveHeightHm0,
            wavePeriodTm10);

        return waterLevel
                - 2 * depthMaximumWaveLoadNaturalStone
                + max(depthMaximumWaveLoadNaturalStone + upperLimitLoadingOfNaturalStoneAul,
                      upperLimitLoadingOfNaturalStoneBul * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               upperLimitLoadingOfNaturalStoneCul));
    }

    double NaturalStoneRevetment::CalculateLowerLimitLoadingOfNaturalStone(
        const double waterLevel,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi,
        const double lowerLimitLoadingOfNaturalStoneAll,
        const double lowerLimitLoadingOfNaturalStoneBll,
        const double lowerLimitLoadingOfNaturalStoneCll)
    {
        const auto depthMaximumWaveLoadNaturalStone = CalculateDepthMaximumWaveLoadNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            distanceMaximumWaveElevationNaturalStoneAsmax,
            distanceMaximumWaveElevationNaturalStoneBsmax,
            normativeWidthOfWaveImpactNaturalStoneAwi,
            normativeWidthOfWaveImpactNaturalStoneBwi);
        const auto surfSimilarityParameter = Revetment::CalculateSurfSimilarityParameter(
            tanA,
            waveHeightHm0,
            wavePeriodTm10);

        return waterLevel
                - 2 * depthMaximumWaveLoadNaturalStone
                + min(depthMaximumWaveLoadNaturalStone - lowerLimitLoadingOfNaturalStoneAll,
                      lowerLimitLoadingOfNaturalStoneBll * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               lowerLimitLoadingOfNaturalStoneCll));
    }

    double NaturalStoneRevetment::CalculateDepthMaximumWaveLoadNaturalStone(
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi)
    {
        const auto distanceMaximumWaveElevationNaturalStone = CalculateDistanceMaximumWaveElevationNaturalStone(
            waveHeightHm0,
            wavePeriodTm10,
            distanceMaximumWaveElevationNaturalStoneAsmax,
            distanceMaximumWaveElevationNaturalStoneBsmax);
        const auto normativeWidthOfWaveImpact = CalculateNormativeWidthOfWaveImpactNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            normativeWidthOfWaveImpactNaturalStoneAwi,
            normativeWidthOfWaveImpactNaturalStoneBwi);
        const auto slopeAngle = Revetment::CalculateSlopeAngle(tanA);

        return (distanceMaximumWaveElevationNaturalStone - 0.5 * normativeWidthOfWaveImpact * cos(Revetment::DegreesToRadians(slopeAngle)))
                * tan(Revetment::DegreesToRadians(slopeAngle));
    }

    double NaturalStoneRevetment::CalculateDistanceMaximumWaveElevationNaturalStone(
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax)
    {
        const auto impactShallowWaterNaturalStone = CalculateImpactShallowWaterNaturalStone();
        const auto waveSteepnessDeepWater = Revetment::CalculateWaveSteepnessDeepWater(
            waveHeightHm0,
            wavePeriodTm10);

        return waveHeightHm0
                * (distanceMaximumWaveElevationNaturalStoneAsmax / sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationNaturalStoneBsmax)
                * impactShallowWaterNaturalStone;
    }

    double NaturalStoneRevetment::CalculateImpactShallowWaterNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::CalculateNormativeWidthOfWaveImpactNaturalStone(
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi)
    {
        const auto surfSimilarityParameter = Revetment::CalculateSurfSimilarityParameter(
            tanA,
            waveHeightHm0,
            wavePeriodTm10);

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
        const double startTime,
        const double endTime,
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto incrementOfTime = Revetment::CalculateIncrementOfTime(
            startTime,
            endTime);

        const auto referenceTimeDegradationOfNaturalStone = CalculateReferenceTimeDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);

        return CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone + incrementOfTime, wavePeriodTm10)
                - CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone, wavePeriodTm10);
    }

    double NaturalStoneRevetment::CalculateReferenceTimeDegradationOfNaturalStone(
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto referenceDegradationOfNaturalStone = CalculateReferenceDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);

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
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(
            relativeDensity,
            thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone(
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax
        );

        return initialDamage * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpactOnNaturalStone(
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax)
    {
        return pow(cos(Revetment::DegreesToRadians(min(waveAngleImpactOnNaturalStoneBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetment::CalculateDurationInTimeStepFailureNaturalStone(
        const double initialDamage,
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto referenceTimeFailureOfNaturalStone = CalculateReferenceTimeFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto referenceTimeDegradationOfNaturalStone = CalculateReferenceTimeDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);

        return referenceTimeFailureOfNaturalStone - referenceTimeDegradationOfNaturalStone;
    }

    double NaturalStoneRevetment::CalculateReferenceTimeFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto referenceFailureOfNaturalStone = CalculateReferenceFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer,
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);

        return 1000.0 * wavePeriodTm10 * pow(referenceFailureOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::CalculateReferenceFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax,
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
    {
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(relativeDensity, thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone(
            waveAngle,
            waveAngleImpactOnNaturalStoneBetamax);

        return failureNumber * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }
}

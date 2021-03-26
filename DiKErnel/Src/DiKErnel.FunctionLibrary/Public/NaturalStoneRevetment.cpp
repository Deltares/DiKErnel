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

    double NaturalStoneRevetment::IncrementDamageOfNaturalStone(
        const double hydraulicLoadOnNaturalStone,
        const double resistanceOfNaturalStone,
        const double incrementDegradationOfNaturalStone,
        const double loadingOfRevetment,
        const double waveAngleImpactOnNaturalStone)
    {
        return hydraulicLoadOnNaturalStone / resistanceOfNaturalStone * incrementDegradationOfNaturalStone * loadingOfRevetment
                * waveAngleImpactOnNaturalStone;
    }

    double NaturalStoneRevetment::HydraulicLoadOnNaturalStone(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
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

    double NaturalStoneRevetment::UpperLimitLoadingOfNaturalStone(
        const double depthMaximumWaveLoadNaturalStone,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingOfNaturalStoneAul,
        const double upperLimitLoadingOfNaturalStoneBul,
        const double upperLimitLoadingOfNaturalStoneCul)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoadNaturalStone
                + max(depthMaximumWaveLoadNaturalStone + upperLimitLoadingOfNaturalStoneAul,
                      upperLimitLoadingOfNaturalStoneBul * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               upperLimitLoadingOfNaturalStoneCul));
    }

    double NaturalStoneRevetment::LowerLimitLoadingOfNaturalStone(
        const double depthMaximumWaveLoadNaturalStone,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingOfNaturalStoneAll,
        const double lowerLimitLoadingOfNaturalStoneBll,
        const double lowerLimitLoadingOfNaturalStoneCll)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoadNaturalStone
                + min(depthMaximumWaveLoadNaturalStone - lowerLimitLoadingOfNaturalStoneAll,
                      lowerLimitLoadingOfNaturalStoneBll * waveHeightHm0 * min(surfSimilarityParameter,
                                                                               lowerLimitLoadingOfNaturalStoneCll));
    }

    double NaturalStoneRevetment::DepthMaximumWaveLoadNaturalStone(
        const double distanceMaximumWaveElevationNaturalStone,
        const double normativeWidthOfWaveImpact,
        const double slopeAngle)
    {
        return (distanceMaximumWaveElevationNaturalStone - 0.5 * normativeWidthOfWaveImpact * cos(Revetment::DegreesToRadians(slopeAngle)))
                * tan(Revetment::DegreesToRadians(slopeAngle));
    }

    double NaturalStoneRevetment::DistanceMaximumWaveElevationNaturalStone(
        const double impactShallowWaterNaturalStone,
        const double waveSteepnessDeepWater,
        const double waveHeightHm0,
        const double distanceMaximumWaveElevationNaturalStoneAsmax,
        const double distanceMaximumWaveElevationNaturalStoneBsmax)
    {
        return waveHeightHm0
                * (distanceMaximumWaveElevationNaturalStoneAsmax / sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationNaturalStoneBsmax)
                * impactShallowWaterNaturalStone;
    }

    double NaturalStoneRevetment::ImpactShallowWaterNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::NormativeWidthOfWaveImpactNaturalStone(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double normativeWidthOfWaveImpactNaturalStoneAwi,
        const double normativeWidthOfWaveImpactNaturalStoneBwi)
    {
        return (normativeWidthOfWaveImpactNaturalStoneAwi - normativeWidthOfWaveImpactNaturalStoneBwi * surfSimilarityParameter)
                * waveHeightHm0;
    }

    double NaturalStoneRevetment::WaveAngleImpactOnNaturalStone(
        const double waveAngle,
        const double waveAngleImpactOnNaturalStoneBetamax)
    {
        return pow(cos(Revetment::DegreesToRadians(min(waveAngleImpactOnNaturalStoneBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetment::ResistanceOfNaturalStone(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::IncrementDegradationOfNaturalStone(
        const double referenceTimeDegradationOfNaturalStone,
        const double wavePeriodTm10,
        const double incrementOfTime)
    {
        return DegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone + incrementOfTime, wavePeriodTm10)
                - DegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone, wavePeriodTm10);
    }

    double NaturalStoneRevetment::DegradationOfNaturalStone(
        const double referenceTimeDegradation,
        const double wavePeriodTm10)
    {
        return pow(referenceTimeDegradation / (wavePeriodTm10 * 1000.0), 0.1);
    }

    double NaturalStoneRevetment::ReferenceTimeDegradationOfNaturalStone(
        const double referenceDegradationOfNaturalStone,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceDegradationOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::ReferenceDegradationOfNaturalStone(
        const double resistanceOfNaturalStone,
        const double hydraulicLoadOnNaturalStone,
        const double waveAngleImpactOnNaturalStone,
        const double initialDamage)
    {
        return initialDamage * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1.0 / waveAngleImpactOnNaturalStone);
    }

    double NaturalStoneRevetment::DurationInTimeStepFailureNaturalStone(
        const double referenceTimeFailureOfNaturalStone,
        const double referenceTimeDegradationOfNaturalStone)
    {
        return referenceTimeFailureOfNaturalStone - referenceTimeDegradationOfNaturalStone;
    }

    double NaturalStoneRevetment::ReferenceTimeFailureOfNaturalStone(
        const double referenceFailureOfNaturalStone,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(referenceFailureOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::ReferenceFailureOfNaturalStone(
        const double resistanceOfNaturalStone,
        const double hydraulicLoadOnNaturalStone,
        const double waveAngleImpactOnNaturalStone,
        const double failureNumber)
    {
        return failureNumber * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1.0 / waveAngleImpactOnNaturalStone);
    }
}

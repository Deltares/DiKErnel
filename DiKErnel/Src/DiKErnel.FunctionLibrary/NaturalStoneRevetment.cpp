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

#include <cmath>

#include "Revetment.h"

namespace DiKErnel::FunctionLibrary
{
    double NaturalStoneRevetment::CalculateDamageOfNaturalStone(
        const double startTime,
        const double endTime,
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
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
        return initialDamage + CalculateIncrementDamageOfNaturalStone(
            startTime,
            endTime,
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
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
    }

    double NaturalStoneRevetment::CalculateIncrementDamageOfNaturalStone(
        const double startTime,
        const double endTime,
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
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
            hydraulicLoadOnNaturalStoneXib,
            hydraulicLoadOnNaturalStoneAp,
            hydraulicLoadOnNaturalStoneBp,
            hydraulicLoadOnNaturalStoneCp,
            hydraulicLoadOnNaturalStoneNp,
            hydraulicLoadOnNaturalStoneAs,
            hydraulicLoadOnNaturalStoneBs,
            hydraulicLoadOnNaturalStoneCs,
            hydraulicLoadOnNaturalStoneNs);
        const auto loadingOfRevetment = Revetment::CalculateLoadingOfRevetment();
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

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
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

        return initialDamage * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpactOnNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::CalculateDurationInTimeStepFailureNaturalStone(
        const double initialDamage,
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
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
        const auto referenceTimeFailureOfNaturalStone = CalculateReferenceTimeFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer,
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
        const auto referenceTimeDegradationOfNaturalStone = CalculateReferenceTimeDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
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

        return referenceTimeFailureOfNaturalStone - referenceTimeDegradationOfNaturalStone;
    }

    double NaturalStoneRevetment::CalculateReferenceTimeFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
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
        const auto referenceFailureOfNaturalStone = CalculateReferenceFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer,
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

        return 1000.0 * wavePeriodTm10 * pow(referenceFailureOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::CalculateReferenceFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
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
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

        return failureNumber * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }
}

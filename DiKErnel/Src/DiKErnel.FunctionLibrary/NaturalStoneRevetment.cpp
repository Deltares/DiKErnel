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
        const double wavePeriodTm10)
    {
        return initialDamage + CalculateIncrementDamageOfNaturalStone(
            startTime,
            endTime,
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            wavePeriodTm10);
    }

    double NaturalStoneRevetment::CalculateIncrementDamageOfNaturalStone(
        const double startTime,
        const double endTime,
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double wavePeriodTm10)
    {
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone();
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(
            relativeDensity,
            thicknessTopLayer);
        const auto incrementDegradationOfNaturalStone = CalculateIncrementDegradationOfNaturalStone(
            startTime,
            endTime,
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            wavePeriodTm10);
        const auto loadingOfRevetment = Revetment::CalculateLoadingOfRevetment();
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

        return hydraulicLoadOnNaturalStone / resistanceOfNaturalStone * incrementDegradationOfNaturalStone * loadingOfRevetment
                * waveAngleImpactOnNaturalStone;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoadOnNaturalStone()
    {
        return 1.0;
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
        const double wavePeriodTm10)
    {
        const auto incrementOfTime = Revetment::CalculateIncrementOfTime(
            startTime,
            endTime);

        const auto referenceTimeDegradationOfNaturalStone = CalculateReferenceTimeDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            wavePeriodTm10);

        return CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone + incrementOfTime, wavePeriodTm10)
                - CalculateDegradationOfNaturalStone(referenceTimeDegradationOfNaturalStone, wavePeriodTm10);
    }

    double NaturalStoneRevetment::CalculateReferenceTimeDegradationOfNaturalStone(
        const double initialDamage,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double wavePeriodTm10)
    {
        const auto referenceDegradationOfNaturalStone = CalculateReferenceDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer);

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
        const double thicknessTopLayer)
    {
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(relativeDensity, thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone();
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
        const double wavePeriodTm10)
    {
        const auto referenceTimeFailureOfNaturalStone = CalculateReferenceTimeFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer,
            wavePeriodTm10);
        const auto referenceTimeDegradationOfNaturalStone = CalculateReferenceTimeDegradationOfNaturalStone(
            initialDamage,
            relativeDensity,
            thicknessTopLayer,
            wavePeriodTm10);

        return referenceTimeFailureOfNaturalStone - referenceTimeDegradationOfNaturalStone;
    }

    double NaturalStoneRevetment::CalculateReferenceTimeFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double wavePeriodTm10)
    {
        const auto referenceFailureOfNaturalStone = CalculateReferenceFailureOfNaturalStone(
            failureNumber,
            relativeDensity,
            thicknessTopLayer);

        return 1000.0 * wavePeriodTm10 * pow(referenceFailureOfNaturalStone, 10.0);
    }

    double NaturalStoneRevetment::CalculateReferenceFailureOfNaturalStone(
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(relativeDensity, thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone();
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

        return failureNumber * (resistanceOfNaturalStone / hydraulicLoadOnNaturalStone) * (1 / waveAngleImpactOnNaturalStone);
    }
}

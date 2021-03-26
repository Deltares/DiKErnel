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

#include "NaturalStoneRevetmentDeprecated.h"

#include <algorithm>
#include <cmath>

#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double NaturalStoneRevetmentDeprecated::CalculateDamage(
        const double initialDamage,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double waveAngleMaximum,
        const double hydraulicLoadXIb)
    {
        const auto incrementDamageOfNaturalStoneRevetment = CalculateIncrementDamage(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            waveAngleMaximum,
            initialDamage,
            hydraulicLoadXIb);

        return initialDamage + incrementDamageOfNaturalStoneRevetment;
    }

    double NaturalStoneRevetmentDeprecated::CalculateIncrementDamage(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double waveAngleMaximum,
        const double initialDamage,
        const double hydraulicLoadXIb)
    {
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            hydraulicLoadXIb);

        const auto resistanceOfNaturalStoneRevetment = CalculateResistance(relativeDensity, thicknessTopLayer);

        const auto loadResistanceCalculatedValue = hydraulicLoadOnNaturalStoneRevetment / resistanceOfNaturalStoneRevetment;

        const auto incrementDegradationOfNaturalStoneRevetment = CalculateIncrementDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            waveAngleMaximum,
            initialDamage,
            hydraulicLoadXIb);

        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        return loadResistanceCalculatedValue * incrementDegradationOfNaturalStoneRevetment * waveAngleImpactOnNaturalStoneRevetment;
    }

    double NaturalStoneRevetmentDeprecated::CalculateHydraulicLoad(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double hydraulicLoadXIb)
    {
        const auto surfSimilarityParameter = CalculateSurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

        double coefficientA;
        double coefficientB;
        double coefficientC;
        double coefficientN;

        if (hydraulicLoadXIb > surfSimilarityParameter)
        {
            coefficientA = hydraulicLoadAp;
            coefficientB = hydraulicLoadBp;
            coefficientC = hydraulicLoadCp;
            coefficientN = hydraulicLoadNp;
        }
        else
        {
            coefficientA = hydraulicLoadAs;
            coefficientB = hydraulicLoadBs;
            coefficientC = hydraulicLoadCs;
            coefficientN = hydraulicLoadNs;
        }

        const auto denominator = coefficientA * pow(surfSimilarityParameter, coefficientN) + coefficientB * surfSimilarityParameter + coefficientC;

        return spectralWaveHeight / denominator;
    }

    double NaturalStoneRevetmentDeprecated::CalculateSurfSimilarityParameter(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod)
    {
        const auto spectralWaveHeightRelatedValue = 2.0 * Generic::Pi() * spectralWaveHeight;

        const auto spectralWavePeriodRelatedValue = 9.81 * pow(spectralWavePeriod, 2.0);

        const auto denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);

        return slopeAngle / denominator;
    }

    double NaturalStoneRevetmentDeprecated::CalculateResistance(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetmentDeprecated::CalculateIncrementDegradation(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double waveAngleMaximum,
        const double initialDamage,
        const double hydraulicLoadXIb)
    {
        const auto timeStep = CalculateIncrementOfTime(startTime, endTime);

        const auto referenceTimeDegradationOfNaturalStoneRevetment = CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            waveAngleMaximum,
            initialDamage,
            hydraulicLoadXIb);

        const auto degradation = CalculateDegradation(
            referenceTimeDegradationOfNaturalStoneRevetment + timeStep,
            spectralWavePeriod);

        const auto previousDegradation = CalculateDegradation(
            referenceTimeDegradationOfNaturalStoneRevetment,
            spectralWavePeriod);

        return degradation - previousDegradation;
    }

    double NaturalStoneRevetmentDeprecated::CalculateDegradation(
        const double referenceTimeDegradation,
        const double spectralWavePeriod)
    {
        const auto numerator = referenceTimeDegradation / spectralWavePeriod;

        const int denominator = 1000.0;

        return pow(numerator / denominator, 0.1);
    }

    double NaturalStoneRevetmentDeprecated::CalculateReferenceTimeDegradation(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double waveAngleMaximum,
        const double initialDamage,
        const double hydraulicLoadXIb)
    {
        const auto referenceDegradationOfNaturalStoneRevetment = CalculateReferenceDegradation(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            waveAngleMaximum,
            hydraulicLoadXIb);

        return 1000.0 * spectralWavePeriod * pow(referenceDegradationOfNaturalStoneRevetment, 10.0);
    }

    double NaturalStoneRevetmentDeprecated::CalculateReferenceDegradation(
        const double damagePreviousTimeStep,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double waveAngleMaximum,
        const double hydraulicLoadXIb)
    {
        const auto resistanceOfNaturalStoneRevetment = CalculateResistance(relativeDensity, thicknessTopLayer);

        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            hydraulicLoadAp,
            hydraulicLoadBp,
            hydraulicLoadCp,
            hydraulicLoadNp,
            hydraulicLoadAs,
            hydraulicLoadBs,
            hydraulicLoadCs,
            hydraulicLoadNs,
            hydraulicLoadXIb);

        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        return damagePreviousTimeStep * resistanceOfNaturalStoneRevetment / hydraulicLoadOnNaturalStoneRevetment
                * (1.0 / waveAngleImpactOnNaturalStoneRevetment);
    }

    double NaturalStoneRevetmentDeprecated::CalculateWaveAngleImpact(
        const double waveAngle,
        const double waveAngleMaximum)
    {
        const auto smallestAngle = min(waveAngleMaximum, waveAngle);
        const auto waveAngleRadians = ConvertDegreesToRadians(smallestAngle);
        const auto absoluteWaveAngleRadians = fabs(waveAngleRadians);
        const auto cosine = cos(absoluteWaveAngleRadians);
        const auto exponent = 2.0 / 3;

        return pow(cosine, exponent);
    }

    double NaturalStoneRevetmentDeprecated::CalculateIncrementOfTime(
        const double startTime,
        const double endTime)
    {
        return endTime - startTime;
    }

    double NaturalStoneRevetmentDeprecated::ConvertDegreesToRadians(
        const double degrees)
    {
        return degrees * (Generic::Pi() / 180);
    }
}

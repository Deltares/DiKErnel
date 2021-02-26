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

#include "Constants.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;
    using namespace DomainLibrary;

    double NaturalStoneRevetment::CalculateDamage(
        const double initialDamage,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double waveAngleMaximum,
        const double similarityParameterThreshold)
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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        return initialDamage + incrementDamageOfNaturalStoneRevetment;
    }

    double NaturalStoneRevetment::CalculateIncrementDamage(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double waveAngleMaximum,
        const double initialDamage,
        const double similarityParameterThreshold)
    {
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            similarityParameterThreshold);

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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        return loadResistanceCalculatedValue * incrementDegradationOfNaturalStoneRevetment * waveAngleImpactOnNaturalStoneRevetment;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoad(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double similarityParameterThreshold)
    {
        const auto surfSimilarityParameter = CalculateSurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

        double coefficientA;
        double coefficientB;
        double coefficientC;
        double coefficientN;

        if (similarityParameterThreshold > surfSimilarityParameter)
        {
            coefficientA = plungingCoefficientA;
            coefficientB = plungingCoefficientB;
            coefficientC = plungingCoefficientC;
            coefficientN = plungingCoefficientN;
        }
        else
        {
            coefficientA = surgingCoefficientA;
            coefficientB = surgingCoefficientB;
            coefficientC = surgingCoefficientC;
            coefficientN = surgingCoefficientN;
        }

        const auto denominator = coefficientA * pow(surfSimilarityParameter, coefficientN) + coefficientB * surfSimilarityParameter + coefficientC;

        return spectralWaveHeight / denominator;
    }

    double NaturalStoneRevetment::CalculateSurfSimilarityParameter(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod)
    {
        const auto spectralWaveHeightRelatedValue = 2.0 * Constants::PI * spectralWaveHeight;

        const auto spectralWavePeriodRelatedValue = Constants::GRAVITATIONAL_ACCELERATION * pow(spectralWavePeriod, 2.0);

        const auto denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);

        return slopeAngle / denominator;
    }

    double NaturalStoneRevetment::CalculateResistance(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::CalculateIncrementDegradation(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double startTime,
        const double endTime,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double waveAngleMaximum,
        const double initialDamage,
        const double similarityParameterThreshold)
    {
        const auto timeStep = CalculateIncrementOfTime(startTime, endTime);

        const auto referenceTimeDegradationOfNaturalStoneRevetment = CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        const auto degradation = CalculateDegradation(
            referenceTimeDegradationOfNaturalStoneRevetment + timeStep,
            spectralWavePeriod);

        const auto previousDegradation = CalculateDegradation(
            referenceTimeDegradationOfNaturalStoneRevetment,
            spectralWavePeriod);

        return degradation - previousDegradation;
    }

    double NaturalStoneRevetment::CalculateDegradation(
        const double referenceTimeDegradation,
        const double spectralWavePeriod)
    {
        const auto numerator = referenceTimeDegradation / spectralWavePeriod;

        const int denominator = 1000.0;

        return pow(numerator / denominator, 0.1);
    }

    double NaturalStoneRevetment::CalculateReferenceTimeDegradation(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double waveAngleMaximum,
        const double initialDamage,
        const double similarityParameterThreshold)
    {
        const auto referenceDegradationOfNaturalStoneRevetment = CalculateReferenceDegradation(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            similarityParameterThreshold);

        return 1000.0 * spectralWavePeriod * pow(referenceDegradationOfNaturalStoneRevetment, 10.0);
    }

    double NaturalStoneRevetment::CalculateReferenceDegradation(
        const double damagePreviousTimeStep,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double waveAngleMaximum,
        const double similarityParameterThreshold)
    {
        const auto resistanceOfNaturalStoneRevetment = CalculateResistance(relativeDensity, thicknessTopLayer);

        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            similarityParameterThreshold);

        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        return damagePreviousTimeStep * resistanceOfNaturalStoneRevetment / hydraulicLoadOnNaturalStoneRevetment
                * (1.0 / waveAngleImpactOnNaturalStoneRevetment);
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpact(
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

    double NaturalStoneRevetment::CalculateIncrementOfTime(
        const double startTime,
        const double endTime)
    {
        return endTime - startTime;
    }

    double NaturalStoneRevetment::ConvertDegreesToRadians(
        const double degrees)
    {
        return degrees * (Constants::PI / 180);
    }
}

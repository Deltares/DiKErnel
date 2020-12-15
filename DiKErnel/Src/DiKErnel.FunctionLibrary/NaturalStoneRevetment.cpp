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

using namespace DiKErnel::DomainLibrary;

namespace DiKErnel::FunctionLibrary
{
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
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
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
            ap,
            np,
            bp,
            cp,
            as,
            ns,
            bs,
            cs);

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
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
    {
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(slopeAngle, spectralWaveHeight, spectralWavePeriod,
                                                                                 ap,
                                                                                 np,
                                                                                 bp,
                                                                                 cp,
                                                                                 as,
                                                                                 ns,
                                                                                 bs,
                                                                                 cs);
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
            ap,
            np,
            bp,
            cp,
            as,
            ns,
            bs,
            cs);

        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle);

        return loadResistanceCalculatedValue * incrementDegradationOfNaturalStoneRevetment * waveAngleImpactOnNaturalStoneRevetment;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoad(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
    {
        const auto xiFactor = 2.9;
        const auto surfSimilarityParameter = CalculateSurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

        const auto denominator = xiFactor > surfSimilarityParameter
                                     ? ap * pow(surfSimilarityParameter, np) + bp * surfSimilarityParameter + cp
                                     : as * pow(surfSimilarityParameter, ns) + bs * surfSimilarityParameter + cs;

        return spectralWaveHeight / denominator;
    }

    double NaturalStoneRevetment::CalculateSurfSimilarityParameter(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod)
    {
        const auto spectralWaveHeightRelatedValue = 2.0 * Constants::PI * spectralWaveHeight;
        const auto spectralWavePeriodRelatedValue = Constants::GRAVITY * pow(spectralWavePeriod, 2.0);

        const auto denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);
        const auto slopeAngleRadians = ConvertDegreesToRadians(slopeAngle);
        const auto numerator = tan(slopeAngleRadians);

        return numerator / denominator;
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
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
    {
        const auto timeStep = CalculateIncrementOfTime(startTime, endTime);
        const auto referenceTimeDegradationOfNaturalStoneRevetment = CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            ap,
            np,
            bp,
            cp,
            as,
            ns,
            bs,
            cs);

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
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
    {
        const auto referenceDegradationOfNaturalStoneRevetment = CalculateReferenceDegradation(
            0.1,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            ap,
            np,
            bp,
            cp,
            as,
            ns,
            bs,
            cs);

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
        const double ap,
        const double np,
        const double bp,
        const double cp,
        const double as,
        const double ns,
        const double bs,
        const double cs
    )
    {
        const auto resistanceOfNaturalStoneRevetment = CalculateResistance(relativeDensity, thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoad(slopeAngle, spectralWaveHeight, spectralWavePeriod,
                                                                                 ap,
                                                                                 np,
                                                                                 bp,
                                                                                 cp,
                                                                                 as,
                                                                                 ns,
                                                                                 bs,
                                                                                 cs);
        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpact(waveAngle);

        return damagePreviousTimeStep * resistanceOfNaturalStoneRevetment / hydraulicLoadOnNaturalStoneRevetment
                * (1.0 / waveAngleImpactOnNaturalStoneRevetment);
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpact(
        const double waveAngle)
    {
        const auto smallestAngle = std::min(78.0, waveAngle);
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

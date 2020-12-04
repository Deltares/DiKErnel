#include "pch.h"
#include "Calculator.h"
#include <cmath>
#include <iostream>

namespace DamageOfNaturalStoneRevetmentCalculator
{
    double pi = 2 * acos(0.0);

    double Calculator::CalculateDamageOfNaturalStoneRevetment(
        const double initialDamage,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double initialTime,
        const double currentTime)
    {
        const auto incrementDamageOfNaturalStoneRevetment = CalculateIncrementDamageOfNaturalStoneRevetment(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            initialTime,
            currentTime);

        return initialDamage + incrementDamageOfNaturalStoneRevetment;
    }

    double Calculator::CalculateIncrementDamageOfNaturalStoneRevetment(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double initialTime,
        const double currentTime)
    {
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);
        const auto resistanceOfNaturalStoneRevetment = CalculateResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);
        const auto loadResistanceCalculatedValue = hydraulicLoadOnNaturalStoneRevetment / resistanceOfNaturalStoneRevetment;

        const auto incrementDegradationOfNaturalStoneRevetment = CalculateIncrementDegradationOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, initialTime, currentTime);
        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpactOnNaturalStoneRevetment(waveAngle);

        return loadResistanceCalculatedValue * incrementDegradationOfNaturalStoneRevetment * waveAngleImpactOnNaturalStoneRevetment;
    }

    double Calculator::CalculateHydraulicLoadOnNaturalStoneRevetment(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod)
    {
        const auto xiFactor = 2.9;
        const auto surfSimilarityParameter = CalculateSurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);
        const auto ap = 4.0;
        const auto np = -0.9;
        const auto bp = 0.0;
        const auto cp = 0.0;

        const auto as = 0.8;
        const auto ns = 0.6;
        const auto bs = 0.0;
        const auto cs = 0.0;

        const auto denominator = xiFactor > surfSimilarityParameter
                                     ? ap * pow(surfSimilarityParameter, np) + bp * surfSimilarityParameter + cp
                                     : as * pow(surfSimilarityParameter, ns) + bs * surfSimilarityParameter + cs;

        return spectralWaveHeight / denominator;
    }

    double Calculator::CalculateSurfSimilarityParameter(
        const double slopeAngle,
        const double spectralWaveHeight,
        const double spectralWavePeriod)
    {
        const auto spectralWaveHeightRelatedValue = 2.0 * pi * spectralWaveHeight;
        const auto spectralWavePeriodRelatedValue = 9.81 * pow(spectralWavePeriod, 2.0);

        const auto denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);
        const auto slopeAngleRadians = ConvertDegreesToRadians(slopeAngle);
        const auto numerator = tan(slopeAngleRadians);

        return numerator / denominator;
    }

    double Calculator::CalculateResistanceOfNaturalStoneRevetment(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double Calculator::CalculateIncrementDegradationOfNaturalStoneRevetment(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle,
        const double initialTime,
        const double currentTime)
    {
        const auto timeStep = CalculateIncrementOfTime(initialTime, currentTime);
        const auto referenceTimeDegradationOfNaturalStoneRevetment = CalculateReferenceTimeDegradationOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

        const auto degradation = CalculateDegradationOfNaturalStoneRevetment(referenceTimeDegradationOfNaturalStoneRevetment + timeStep, spectralWavePeriod);
        const auto previousDegradation = CalculateDegradationOfNaturalStoneRevetment(referenceTimeDegradationOfNaturalStoneRevetment, spectralWavePeriod);

        return degradation - previousDegradation;
    }

    double Calculator::CalculateDegradationOfNaturalStoneRevetment(
        const double referenceTimeDegradationOfNaturalStoneRevetment,
        const double spectralWavePeriod)
    {
        const auto numerator = referenceTimeDegradationOfNaturalStoneRevetment / spectralWavePeriod;
        const int denominator = 1000.0;

        return pow(numerator / denominator, 0.1);
    }

    double Calculator::CalculateIncrementOfTime(
        const double initialTime,
        const double currentTime)
    {
        return currentTime - initialTime;
    }

    double Calculator::CalculateReferenceTimeDegradationOfNaturalStoneRevetment(
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle)
    {
        const auto referenceDegradationOfNaturalStoneRevetment = CalculateReferenceDegradationOfNaturalStoneRevetment(0.1, slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

        return 1000.0 * spectralWavePeriod * pow(referenceDegradationOfNaturalStoneRevetment, 10.0);
    }

    double Calculator::CalculateReferenceDegradationOfNaturalStoneRevetment(
        const double damagePreviousTimeStep,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double spectralWaveHeight,
        const double spectralWavePeriod,
        const double waveAngle)
    {
        const auto resistanceOfNaturalStoneRevetment = CalculateResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);
        const auto hydraulicLoadOnNaturalStoneRevetment = CalculateHydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);
        const auto waveAngleImpactOnNaturalStoneRevetment = CalculateWaveAngleImpactOnNaturalStoneRevetment(waveAngle);

        return damagePreviousTimeStep * resistanceOfNaturalStoneRevetment / hydraulicLoadOnNaturalStoneRevetment * (1.0 / waveAngleImpactOnNaturalStoneRevetment);
    }

    double Calculator::CalculateWaveAngleImpactOnNaturalStoneRevetment(
        const double waveAngle)
    {
        const auto smallestAngle = std::min(78.0, waveAngle);

        const auto waveAngleRadians = ConvertDegreesToRadians(smallestAngle);
        const auto absoluteWaveAngleRadians = fabs(waveAngleRadians);
        const auto cosine = cos(absoluteWaveAngleRadians);
        const auto exponent = 2.0 / 3;

        return pow(cosine, exponent);
    }

    double Calculator::ConvertDegreesToRadians(
        const double degrees)
    {
        return degrees * (pi / 180);
    }
}

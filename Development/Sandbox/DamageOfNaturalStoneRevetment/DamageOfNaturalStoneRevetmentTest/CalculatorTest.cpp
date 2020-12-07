#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../DamageOfNaturalStoneRevetment/Calculator.h"

namespace DamageOfNaturalStoneRevetmentCalculator
{
    namespace Test
    {
        double initialDamage = 0.1;
        double waveAngle = 60.0;
        double slopeAngle = 15.0;
        double spectralWaveHeight = 1.6;
        double spectralWavePeriod = 4.0;
        double exampleReferenceTimeDegradationOfNaturalStoneRevetment = 7.0;
        double relativeDensity = 1.65;
        double thicknessTopLayer = 0.3;
        double initialTime = 0.0;
        double currentTime = 36.0;

        TEST_CASE("CalculateDamageOfNaturalStoneRevetment")
        {
            // Call
            auto damage = Calculator::CalculateDamageOfNaturalStoneRevetment(
                initialDamage,
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle,
                initialTime,
                currentTime);

            // Assert
            REQUIRE(damage == Approx(0.33458768058794083));
        }

        TEST_CASE("CalculateIncrementDamageOfNaturalStoneRevetment")
        {
            // Call
            auto damage = Calculator::CalculateIncrementDamageOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, initialTime, currentTime);

            // Assert
            REQUIRE(damage == Approx(0.23458768058794083));
        }

        TEST_CASE("CalculateHydraulicLoadOnNaturalStoneRevetment")
        {
            // Call
            auto hydraulicLoadOnNaturalStoneRevetment = Calculator::CalculateHydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);

            // Assert
            REQUIRE(hydraulicLoadOnNaturalStoneRevetment == Approx(0.42109231069183717));
        }

        TEST_CASE("CalculateSurfSimilarityParameter")
        {
            // Call
            auto surfSimilarityParameter = Calculator::CalculateSurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

            // Assert
            REQUIRE(surfSimilarityParameter == Approx(1.0587587730209971));
        }

        TEST_CASE("CalculateResistanceOfNaturalStoneRevetment")
        {
            // Call
            auto surfSimilarityParameter = Calculator::CalculateResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);

            // Assert
            REQUIRE(surfSimilarityParameter == Approx(0.49499999999999994));
        }

        TEST_CASE("CalculateIncrementDegradationOfNaturalStoneRevetment")
        {
            // Call
            auto incrementDegradationOfNaturalStoneRevetment = Calculator::CalculateIncrementDegradationOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, 0.0, 36.0);

            // Assert
            REQUIRE(incrementDegradationOfNaturalStoneRevetment == Approx(0.43774354728651044));
        }

        TEST_CASE("CalculateDegradationOfNaturalStoneRevetment")
        {
            // Call
            auto degradationOfNaturalStoneRevetment = Calculator::CalculateDegradationOfNaturalStoneRevetment(exampleReferenceTimeDegradationOfNaturalStoneRevetment, spectralWavePeriod);

            // Assert
            REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.53003409246204658));
        }

        TEST_CASE("CalculateIncrementOfTime")
        {
            // Call
            auto surfSimilarityParameter = Calculator::CalculateIncrementOfTime(initialTime, currentTime);

            // Assert
            REQUIRE(surfSimilarityParameter == 36);
        }

        TEST_CASE("CalculateReferenceTimeDegradationOfNaturalStoneRevetment")
        {
            // Call
            auto referenceTimeDegradationOfNaturalStoneRevetment = Calculator::CalculateReferenceTimeDegradationOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

            // Assert
            REQUIRE(referenceTimeDegradationOfNaturalStoneRevetment == Approx(0.00020474132396956532));
        }

        TEST_CASE("CalculateReferenceDegradationOfNaturalStoneRevetment")
        {
            // Call
            auto referenceDegradationOfNaturalStoneRevetment = Calculator::CalculateReferenceDegradationOfNaturalStoneRevetment(initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

            // Assert
            REQUIRE(referenceDegradationOfNaturalStoneRevetment == Approx(0.18660125126324004));
        }

        TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentPositiveAngle")
        {
            // Call
            auto degradationOfNaturalStoneRevetment = Calculator::CalculateWaveAngleImpactOnNaturalStoneRevetment(waveAngle);

            // Assert
            REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.62996052494743671));
        }

        TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentNegativeAngle")
        {
            // Call
            auto degradationOfNaturalStoneRevetment = Calculator::CalculateWaveAngleImpactOnNaturalStoneRevetment(-60);

            // Assert
            REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.62996052494743671));
        }
    }
}

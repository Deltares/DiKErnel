#include "catch2/catch.hpp"

#include "NaturalStoneRevetment.h"

namespace DiKErnel::FunctionLibrary::Test
{
    double initialDamage = 0.1;
    double waveAngle = 60.0;
    double slopeAngle = 15.0;
    double spectralWaveHeight = 1.6;
    double spectralWavePeriod = 4.0;
    double relativeDensity = 1.65;
    double thicknessTopLayer = 0.3;
    double initialTime = 0.0;
    double currentTime = 36.0;

    TEST_CASE("CalculatDamage_Always_ReturnsDamage")
    {
        // Call
        auto damage = NaturalStoneRevetment::CalculateDamage(
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

    TEST_CASE("CalculateIncrementDamage_Always_ReturnsIncrementDamage")
    {
        // Call
        auto damage = NaturalStoneRevetment::CalculateIncrementDamage(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            initialTime,
            currentTime);

        // Assert
        REQUIRE(damage == Approx(0.23458768058794083));
    }

    TEST_CASE("CalculateHydraulicLoad_Always_ReturnsHydraulicLoad")
    {
        // Call
        auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Assert
        REQUIRE(hydraulicLoad == Approx(0.42109231069183717));
    }

    TEST_CASE("CalculateSurfSimilarityParameter_Always_ReturnsSurfSimilarityParameter")
    {
        // Call
        auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Assert
        REQUIRE(surfSimilarityParameter == Approx(1.0587587730209971));
    }

    TEST_CASE("CalculateResistance_Always_ReturnsResistance")
    {
        // Call
        auto resistance = NaturalStoneRevetment::CalculateResistance(
            relativeDensity,
            thicknessTopLayer);

        // Assert
        REQUIRE(resistance == Approx(0.49499999999999994));
    }

    TEST_CASE("CalculateIncrementDegradation_Always_ReturnsIncrementDegradation")
    {
        // Call
        auto incrementDegradation = NaturalStoneRevetment::CalculateIncrementDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            0.0,
            36.0);

        // Assert
        REQUIRE(incrementDegradation == Approx(0.43774354728651044));
    }

    TEST_CASE("CalculateDegradation_Always_ReturnsDegradation")
    {
        // Call
        auto degradation = NaturalStoneRevetment::CalculateDegradation(7.0, spectralWavePeriod);

        // Assert
        REQUIRE(degradation == Approx(0.53003409246204658));
    }

    TEST_CASE("CalculateReferenceTimeDegradation_Always_ReturnsReferenceTimeDegradation")
    {
        // Call
        auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle);

        // Assert
        REQUIRE(referenceTimeDegradation == Approx(0.00020474132396956532));
    }

    TEST_CASE("CalculateReferenceDegradation_Always_ReturnsReferenceDegradation")
    {
        // Call
        auto referenceDegradation = NaturalStoneRevetment::CalculateReferenceDegradation(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle);

        // Assert
        REQUIRE(referenceDegradation == Approx(0.18660125126324004));
    }

    TEST_CASE("CalculateWaveAngleImpact_WithPositiveAngle_ReturnsWaveAngleImpact")
    {
        // Call
        auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle);

        // Assert
        REQUIRE(waveAngleImpact == Approx(0.62996052494743671));
    }

    TEST_CASE("CalculateWaveAngleImpact_WithNegativeAngle_ReturnsWaveAngleImpact")
    {
        // Call
        auto degradationOfNaturalStoneRevetment = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle);

        // Assert
        REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.62996052494743671));
    }
}

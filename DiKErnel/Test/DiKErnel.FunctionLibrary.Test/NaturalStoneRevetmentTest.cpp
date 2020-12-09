#include "catch2/catch.hpp"

#include "NaturalStoneRevetment.h"

namespace DiKErnel::FunctionLibrary::Test::NaturalStoneRevetmentTest
{
    TEST_CASE("GivenInput")
    {
        // Given
        const auto initialDamage = 0.1;
        const auto waveAngle = 60.0;
        const auto slopeAngle = 15.0;
        const auto spectralWaveHeight = 1.6;
        const auto spectralWavePeriod = 4.0;
        const auto relativeDensity = 1.65;
        const auto thicknessTopLayer = 0.3;
        const auto initialTime = 0.0;
        const auto currentTime = 36.0;

        SECTION("WhenCalculateDamage_ThenExpectedResult")
        {
            // When
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

            // Then
            REQUIRE(damage == Approx(0.33458768058794083));
        }

        SECTION("WhenCalculateIncrementDamage_ThenExpectedResult")
        {
            // Call
            auto incrementDamage = NaturalStoneRevetment::CalculateIncrementDamage(
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle,
                initialTime,
                currentTime);

            // Assert
            REQUIRE(incrementDamage == Approx(0.23458768058794083));
        }

        SECTION("WhenCalculateHydraulicLoad_ThenExpectedResult")
        {
            // Call
            auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
                slopeAngle,
                spectralWaveHeight,
                spectralWavePeriod);

            // Assert
            REQUIRE(hydraulicLoad == Approx(0.42109231069183717));
        }

        SECTION("WhenCalculateSurfSimilarityParameter_ThenExpectedResult")
        {
            // Call
            auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
                slopeAngle,
                spectralWaveHeight,
                spectralWavePeriod);

            // Assert
            REQUIRE(surfSimilarityParameter == Approx(1.0587587730209971));
        }

        SECTION("WhenCalculateResistance_ThenExpectedResult")
        {
            // Call
            auto resistance = NaturalStoneRevetment::CalculateResistance(
                relativeDensity,
                thicknessTopLayer);

            // Assert
            REQUIRE(resistance == Approx(0.49499999999999994));
        }

        SECTION("WhenCalculateIncrementDegradation_ThenExpectedResult")
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

        SECTION("WhenCalculateDegradation_ThenExpectedResult")
        {
            // Call
            auto degradation = NaturalStoneRevetment::CalculateDegradation(7.0, spectralWavePeriod);

            // Assert
            REQUIRE(degradation == Approx(0.53003409246204658));
        }

        SECTION("WhenCalculateReferenceTimeDegradation_ThenExpectedResult")
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

        SECTION("WhenCalculateReferenceDegradation_ThenExpectedResult")
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

        SECTION("WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult")
        {
            // Call
            auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle);

            // Assert
            REQUIRE(waveAngleImpact == Approx(0.62996052494743671));
        }

        SECTION("WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult")
        {
            // Call
            auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle);

            // Assert
            REQUIRE(waveAngleImpact == Approx(0.62996052494743671));
        }
    }
}

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
            // When
            auto incrementDamage = NaturalStoneRevetment::CalculateIncrementDamage(
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle,
                initialTime,
                currentTime);

            // Then
            REQUIRE(incrementDamage == Approx(0.23458768058794083));
        }

        SECTION("WhenCalculateHydraulicLoadWithSurfSimilarityParameterSmallerThanXiFactory_ThenExpectedResult")
        {
            // When
            auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
                slopeAngle,
                spectralWaveHeight,
                spectralWavePeriod);

            // Then
            REQUIRE(hydraulicLoad == Approx(0.42109231069183717));
        }


        SECTION("WhenCalculateHydraulicLoadWithSurfSimilarityParameterBiggerThanXiFactory_ThenExpectedResult")
        {
            // When
            auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
                slopeAngle * 4,
                spectralWaveHeight / 4,
                spectralWavePeriod / 4);

            // Then
            REQUIRE(hydraulicLoad == Approx(0.23900384271534394));
        }

        SECTION("WhenCalculateSurfSimilarityParameter_ThenExpectedResult")
        {
            // When
            auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
                slopeAngle,
                spectralWaveHeight,
                spectralWavePeriod);

            // Then
            REQUIRE(surfSimilarityParameter == Approx(1.0587587730209971));
        }

        SECTION("WhenCalculateResistance_ThenExpectedResult")
        {
            // When
            auto resistance = NaturalStoneRevetment::CalculateResistance(
                relativeDensity,
                thicknessTopLayer);

            // Then
            REQUIRE(resistance == Approx(0.49499999999999994));
        }

        SECTION("WhenCalculateIncrementDegradation_ThenExpectedResult")
        {
            // When
            auto incrementDegradation = NaturalStoneRevetment::CalculateIncrementDegradation(
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle,
                0.0,
                36.0);

            // Then
            REQUIRE(incrementDegradation == Approx(0.43774354728651044));
        }

        SECTION("WhenCalculateDegradation_ThenExpectedResult")
        {
            // When
            auto degradation = NaturalStoneRevetment::CalculateDegradation(7.0, spectralWavePeriod);

            // Then
            REQUIRE(degradation == Approx(0.53003409246204658));
        }

        SECTION("WhenCalculateReferenceTimeDegradation_ThenExpectedResult")
        {
            // When
            auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle);

            // Then
            REQUIRE(referenceTimeDegradation == Approx(0.00020474132396956532));
        }

        SECTION("WhenCalculateReferenceDegradation_ThenExpectedResult")
        {
            // When
            auto referenceDegradation = NaturalStoneRevetment::CalculateReferenceDegradation(
                initialDamage,
                slopeAngle,
                relativeDensity,
                thicknessTopLayer,
                spectralWaveHeight,
                spectralWavePeriod,
                waveAngle);

            // Then
            REQUIRE(referenceDegradation == Approx(0.18660125126324004));
        }

        SECTION("WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult")
        {
            // When
            auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle);

            // Then
            REQUIRE(waveAngleImpact == Approx(0.62996052494743671));
        }

        SECTION("WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult")
        {
            // When
            auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle);

            // Then
            REQUIRE(waveAngleImpact == Approx(0.62996052494743671));
        }
    }
}

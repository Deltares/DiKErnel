#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../DamageOfNaturalStoneRevetment/Calculator.h"
using namespace DamageOfNaturalStoneRevetmentCalculator;

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

TEST_CASE("DamageOfNaturalStoneRevetment")
{
    // Call
    double damage = Calculator::DamageOfNaturalStoneRevetment(initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, initialTime, currentTime);

    // Assert
    REQUIRE(damage == Approx(0.33458768058794083));
}

TEST_CASE("IncrementDamageOfNaturalStoneRevetment")
{
    // Call
    double damage = Calculator::IncrementDamageOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, initialTime, currentTime);

    // Assert
    REQUIRE(damage == Approx(0.23458768058794083));
}

TEST_CASE("HydraulicLoadOnNaturalStoneRevetment")
{
    // Call
    double hydraulicLoadOnNaturalStoneRevetment = Calculator::HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);

    // Assert
    REQUIRE(hydraulicLoadOnNaturalStoneRevetment == Approx(0.42109231069183717));
}

TEST_CASE("HeavisideFunction")
{
    // Call
    std::tuple<int, int> heaviside = Calculator::HeavisideFunction(2.9, 0.50);

    // Assert
    REQUIRE(heaviside == std::tuple<int, int>{1, 0});
}

TEST_CASE("SurfSimilarityParameter")
{
    // Call
    double surfSimilarityParameter = Calculator::SurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

    // Assert
    REQUIRE(surfSimilarityParameter == Approx(1.0587587730209971));
}

TEST_CASE("ResistanceOfNaturalStoneRevetment")
{
    // Call
    double surfSimilarityParameter = Calculator::ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);

    // Assert
    REQUIRE(surfSimilarityParameter == Approx(0.49499999999999994));
}

TEST_CASE("IncrementDegradationOfNaturalStoneRevetment")
{
    // Call
    double incrementDegradationOfNaturalStoneRevetment = Calculator::IncrementDegradationOfNaturalStoneRevetment(slopeAngle,relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, 0.0, 36.0);

    // Assert
    REQUIRE(incrementDegradationOfNaturalStoneRevetment == Approx(0.43774354728651044));
}

TEST_CASE("DegradationOfNaturalStoneRevetment")
{
    // Call
    double degradationOfNaturalStoneRevetment = Calculator::DegradationOfNaturalStoneRevetment(exampleReferenceTimeDegradationOfNaturalStoneRevetment, spectralWavePeriod);

    // Assert
    REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.53003409246204658));
}

TEST_CASE("IncrementOfTime")
{
    // Call
    double surfSimilarityParameter = Calculator::IncrementOfTime(initialTime, currentTime);

    // Assert
    REQUIRE(surfSimilarityParameter == 36);
}

TEST_CASE("ReferenceTimeDegradationOfNaturalStoneRevetment")
{
    // Call
    double referenceTimeDegradationOfNaturalStoneRevetment = Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

    // Assert
    REQUIRE(referenceTimeDegradationOfNaturalStoneRevetment == Approx(0.00020474132396956532));
}

TEST_CASE("ReferenceDegradationOfNaturalStoneRevetment")
{
    // Call
    double referenceDegradationOfNaturalStoneRevetment = Calculator::ReferenceDegradationOfNaturalStoneRevetment(initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle);

    // Assert
    REQUIRE(referenceDegradationOfNaturalStoneRevetment == Approx(0.18660125126324004));
}

TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentPositiveAngle")
{
    // Call
    double degradationOfNaturalStoneRevetment = Calculator::WaveAngleImpactOnNaturalStoneRevetment(waveAngle);

    // Assert
    REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.62996052494743671));
}

TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentNegativeAngle")
{
    // Call
    double degradationOfNaturalStoneRevetment = Calculator::WaveAngleImpactOnNaturalStoneRevetment(-60);

    // Assert
    REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.62996052494743671));
}

#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../DamageOfNaturalStoneRevetment/Calculator.h"
using namespace DamageOfNaturalStoneRevetmentCalculator;

double initialDamage = 0.0;
double waveAngle = 60.0;
double slopeAngle = 15.0;
double spectralWaveHeight = 4.0;
double spectralWavePeriod = 7.0;
double tau = 7.0;
double relativeDensity = 1.6;
double thicknessTopLayer = 0.2;

TEST_CASE("DamageOfNaturalStoneRevetment")
{
    // Call
    double damage = Calculator::DamageOfNaturalStoneRevetment(initialDamage, slopeAngle, spectralWaveHeight, spectralWavePeriod, relativeDensity, thicknessTopLayer, tau, waveAngle);

    // Assert
    REQUIRE(damage == Approx(1.8918112130009428));
}

TEST_CASE("IncrementDamageOfNaturalStoneRevetment")
{
    // Call
    double damage = Calculator::IncrementDamageOfNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod, relativeDensity, thicknessTopLayer, tau, waveAngle);

    // Assert
    REQUIRE(damage == Approx(1.8918112130009428));
}

TEST_CASE("HydraulicLoadOnNaturalStoneRevetment")
{
    // Call
    double hydraulicLoadOnNaturalStoneRevetment = Calculator::HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);

    // Assert
    REQUIRE(hydraulicLoadOnNaturalStoneRevetment == Approx(0.48049009754286925));
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
    REQUIRE(surfSimilarityParameter == Approx(0.44291057156446628));
}

TEST_CASE("ResistanceOfNaturalStoneRevetment")
{
    // Call
    double surfSimilarityParameter = Calculator::ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);

    // Assert
    REQUIRE(surfSimilarityParameter == Approx(0.32000000000000006));
}

TEST_CASE("IncrementDegradationOfNaturalStoneRevetment")
{
    // Call
    double incrementDegradationOfNaturalStoneRevetment = Calculator::IncrementDegradationOfNaturalStoneRevetment(tau, spectralWavePeriod);

    // Assert
    REQUIRE(incrementDegradationOfNaturalStoneRevetment == Approx(1.9999999999999998));
}

TEST_CASE("DegradationOfNaturalStoneRevetment")
{
    // Call
    double degradationOfNaturalStoneRevetment = Calculator::DegradationOfNaturalStoneRevetment(tau, spectralWavePeriod);

    // Assert
    REQUIRE(degradationOfNaturalStoneRevetment == Approx(0.50118723362727224));
}

TEST_CASE("IncrementOfTime")
{
    // Call
    double surfSimilarityParameter = Calculator::IncrementOfTime(160, 200);

    // Assert
    REQUIRE(surfSimilarityParameter == 40);
}

TEST_CASE("ReferenceTimeDegradationOfNaturalStoneRevetment")
{
    // Call
    double referenceTimeDegradationOfNaturalStoneRevetment = Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, slopeAngle);

    // Assert
    REQUIRE(referenceTimeDegradationOfNaturalStoneRevetment == Approx(12207.311985307844));
}

TEST_CASE("ReferenceDegradationOfNaturalStoneRevetment")
{
    // Call
    double referenceDegradationOfNaturalStoneRevetment = Calculator::ReferenceDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, spectralWavePeriod, waveAngle, slopeAngle);

    // Assert
    REQUIRE(referenceDegradationOfNaturalStoneRevetment == Approx(1.0571879404538673));
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

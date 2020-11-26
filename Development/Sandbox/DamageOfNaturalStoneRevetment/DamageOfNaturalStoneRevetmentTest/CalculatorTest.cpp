#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../DamageOfNaturalStoneRevetment/Calculator.h"

double initialDamage = 0.0;
double waveAngle = 60;
double slopeAngle = 15;
double spectralWaveHeight = 4;
double spectralWavePeriod = 7;
double tau = 7;
double relativeDensity = 1.6;
double thicknessTopLayer = 0.2;

TEST_CASE("DamageOfNaturalStoneRevetment")
{
	// Call
	double damage = Calculator::DamageOfNaturalStoneRevetment(initialDamage, slopeAngle, spectralWaveHeight, spectralWavePeriod, relativeDensity, thicknessTopLayer, tau, waveAngle);

	// Assert
	REQUIRE(damage == 0.4);
}

TEST_CASE("IncrementDamageOfNaturalStoneRevetment")
{
	// Call
	double damage = Calculator::IncrementDamageOfNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod, relativeDensity, thicknessTopLayer, tau, waveAngle);

	// Assert
	REQUIRE(damage == 1.8918112130009428);
}

TEST_CASE("HydraulicLoadOnNaturalStoneRevetment")
{
	// Call
	double hydraulicLoadOnNaturalStoneRevetment = Calculator::HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);

	// Assert
	REQUIRE(hydraulicLoadOnNaturalStoneRevetment == 0.48049009754286925);
}

TEST_CASE("HeavisideFunction")
{
	// Call
	std::tuple<int, int> heavyside = Calculator::HeavisideFunction(2.9, 0.50);

	// Assert
	REQUIRE(heavyside == std::tuple<int, int>{1, 0});
}

TEST_CASE("SurfSimilarityParameter")
{
	// Call
	double surfSimilarityParameter = Calculator::SurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);

	// Assert
	REQUIRE(surfSimilarityParameter == 0.44291057156446628);
}

TEST_CASE("ResistanceOfNaturalStoneRevetment")
{
	// Call
	double surfSimilarityParameter = Calculator::ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);

	// Assert
	REQUIRE(surfSimilarityParameter == 0.32000000000000006);
}

TEST_CASE("IncrementDegradationOfNaturalStoneRevetment")
{
	// Call
	double incrementDegradationOfNaturalStoneRevetment = Calculator::IncrementDegradationOfNaturalStoneRevetment(tau, spectralWavePeriod);

	// Assert
	REQUIRE(incrementDegradationOfNaturalStoneRevetment == 2.0);
}

TEST_CASE("DegradationOfNaturalStoneRevetment")
{
	// Call
	double degradationOfNaturalStoneRevetment = Calculator::DegradationOfNaturalStoneRevetment(tau, spectralWavePeriod);

	// Assert
	REQUIRE(degradationOfNaturalStoneRevetment == 0.41256292359026653);
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
	double referenceTimeDegradationOfNaturalStoneRevetment = Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, waveAngle, slopeAngle, spectralWavePeriod);

	// Assert
	REQUIRE(referenceTimeDegradationOfNaturalStoneRevetment == 0.0);
}

TEST_CASE("ReferenceDegradationOfNaturalStoneRevetment")
{
	// Call
	double referenceDegradationOfNaturalStoneRevetment = Calculator::ReferenceDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, waveAngle, slopeAngle, spectralWavePeriod);

	// Assert
	REQUIRE(referenceDegradationOfNaturalStoneRevetment == 0.5);
}

TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentPositiveAngle")
{
	// Call
	double degradationOfNaturalStoneRevetment = Calculator::WaveAngleImpactOnNaturalStoneRevetment(waveAngle);

	// Assert
	REQUIRE(degradationOfNaturalStoneRevetment == 0.62996052494743671);
}

TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentNegativeAngle")
{
	// Call
	double degradationOfNaturalStoneRevetment = Calculator::WaveAngleImpactOnNaturalStoneRevetment(-60);

	// Assert
	REQUIRE(degradationOfNaturalStoneRevetment == 0.62996052494743671);
}

#include "pch.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../DamageOfNaturalStoneRevetment/Calculator.h"

TEST_CASE("DamageOfNaturalStoneRevetment")
{
	// Call
	double damage = Calculator::DamageOfNaturalStoneRevetment(0.1, 0.3);

	// Assert
	REQUIRE(damage == 0.4);
}

TEST_CASE("SurfSimilarityParameter")
{
	// Call
	double surfSimilarityParameter = Calculator::SurfSimilarityParameter(15, 4, 7);

	// Assert
	REQUIRE(surfSimilarityParameter == 0.44291057156446628);
}

TEST_CASE("ResistanceOfNaturalStoneRevetment")
{
	// Call
	double surfSimilarityParameter = Calculator::ResistanceOfNaturalStoneRevetment(0.8, 0.4);

	// Assert
	REQUIRE(surfSimilarityParameter == 0.32000000000000006);
}

TEST_CASE("IncrementOfTime")
{
	// Call
	double surfSimilarityParameter = Calculator::IncrementOfTime(16, 20);

	// Assert
	REQUIRE(surfSimilarityParameter == 4);
}

TEST_CASE("DegradationOfNaturalStoneRevetment")
{
	// Call
	double degradationOfNaturalStoneRevetment = Calculator::DegradationOfNaturalStoneRevetment(1, 7);

	// Assert
	REQUIRE(degradationOfNaturalStoneRevetment == 0.41256292359026653);
}

TEST_CASE("WaveAngleImpactOnNaturalStoneRevetmentPositiveAngle")
{
	// Call
	double degradationOfNaturalStoneRevetment = Calculator::WaveAngleImpactOnNaturalStoneRevetment(60);

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

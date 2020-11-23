#include "pch.h"

#include "../DamageOfNaturalStoneRevetment/Calculator.h"

TEST(TestCaseName, TestName) {

	// Call
	double damage = Calculator::DamageOfNaturalStoneRevetment(0.1, 0.3);

	// Assert
	EXPECT_EQ(damage, 0.4);
}

TEST(TestCaseName, SurfSimilarityParameter)
{
	// Call
	double surfSimilarityParameter = Calculator::SurfSimilarityParameter(17, 2.3, 50);

	// Assert
	EXPECT_EQ(surfSimilarityParameter, 20.355326326151559);
}


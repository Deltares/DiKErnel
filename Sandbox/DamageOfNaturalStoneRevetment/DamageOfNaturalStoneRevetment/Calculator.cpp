#include "pch.h"
#include "Calculator.h"
#include <cmath>

double Calculator::DamageOfNaturalStoneRevetment(double initialDamage, double damageOverTime)
{
	return initialDamage + damageOverTime;	
}

double Calculator::SurfSimilarityParameter(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod)
{
	double pi = 2 * acos(0.0);
	double spectralWaveHeightRelatedValue = 2 * pi * spectralWaveHeight;
	double spectralWavePeriodRelatedValue = 9.81 * spectralWavePeriod;

	double denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);
	double numerator = tan(slopeAngle);
	
	double surfSimilarityParameter = numerator / denominator;

	return surfSimilarityParameter;
}

double Calculator::ResistanceOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer)
{
	return relativeDensity * thicknessTopLayer;	
}

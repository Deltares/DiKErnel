#include "pch.h"
#include "Calculator.h"
#include <cmath>

double Calculator::DamageOfNaturalStoneRevetment(double initialDamage, double damageOverTime)
{
	return initialDamage + damageOverTime;	
}

double Calculator::IncrementDamageOfNaturalStoneRevetment()
{
	return HydraulicLoadOnNaturalStoneRevetment(1)/ResistanceOfNaturalStoneRevetment(1,2) * IncrementDegradationOfNaturalStoneRevetment() * WaveAngleImpactOnNaturalStoneRevetment(1);	
}

double Calculator::HydraulicLoadOnNaturalStoneRevetment(double spectralWaveHeight)
{
	return 2.0;
}

int Calculator::HeavisideFunction(int theta)
{
	if (theta < 0)
	{
		return 0;
	}

	return 1;
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

double Calculator::IncrementDegradationOfNaturalStoneRevetment()
{
	return 2.0;
}

double Calculator::DegradationOfNaturalStoneRevetment(double spectralWavePeriod)
{
	// The tau value needs to filled.
	double numerator = 5 / spectralWavePeriod;
	int denominator = 1000;

	return pow(numerator / denominator, 0.1);	
}

double Calculator::IncrementOfTime(double initialTime, double currentTime)
{
	return currentTime - initialTime;
}

double Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(double spectralWavePeriod)
{
	return 1000 * spectralWavePeriod * pow(ReferenceDegradationOfNaturalStoneRevetment(), 10);	
}

double Calculator::ReferenceDegradationOfNaturalStoneRevetment()
{
	return (ResistanceOfNaturalStoneRevetment(1,2) / HydraulicLoadOnNaturalStoneRevetment(1)) * (1 / WaveAngleImpactOnNaturalStoneRevetment(1));	
}

double Calculator::WaveAngleImpactOnNaturalStoneRevetment(double waveAngle)
{
	return 2.0;
}





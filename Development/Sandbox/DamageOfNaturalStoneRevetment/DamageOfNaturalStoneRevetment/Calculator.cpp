#include "pch.h"
#include "Calculator.h"
#include <cmath>
#include <iostream>

double Calculator::DamageOfNaturalStoneRevetment(double initialDamage, double slopeAngle, double spectralWaveHeight, double spectralWavePeriod, double relativeDensity, double thicknessTopLayer, double tau, double waveAngle)
{
	return initialDamage + IncrementDamageOfNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod, relativeDensity, thicknessTopLayer, tau, waveAngle);
}

double Calculator::IncrementDamageOfNaturalStoneRevetment(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod, double relativeDensity, double thicknessTopLayer, double tau, double waveAngle)
{
	return HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod)/ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer)
	* IncrementDegradationOfNaturalStoneRevetment(tau, spectralWavePeriod)
	* WaveAngleImpactOnNaturalStoneRevetment(waveAngle);
}

double Calculator::HydraulicLoadOnNaturalStoneRevetment(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod)
{
	int theta = HeavisideFunction(1);
	double xiFactor = 2.0;
	double coefficientAS = 3.0;
	double coefficientBP = 4.0;
	double coefficientCP = 5.0;
	double coefficientNP = 2.0;
	
	double surfSimilarityParameter = SurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);
	double partialQuotation = (coefficientAS * pow(surfSimilarityParameter, coefficientNP) + (coefficientBP * surfSimilarityParameter) + coefficientCP);
	
	double firstPart = theta * (xiFactor - surfSimilarityParameter) * partialQuotation;

	double secondPart = theta * (surfSimilarityParameter - xiFactor) * partialQuotation;
	
	double denominator = firstPart + secondPart;

	return spectralWaveHeight / denominator;
}

int Calculator::HeavisideFunction(int xValue)
{
	if (xValue < 0)
	{
		return 0;
	}

	return 1;
}

double Calculator::SurfSimilarityParameter(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod)
{
	const double pi = 2 * acos(0.0);
	double spectralWaveHeightRelatedValue = 2 * pi * spectralWaveHeight;
	double spectralWavePeriodRelatedValue = 9.81 * spectralWavePeriod;

	double denominator = sqrt(spectralWaveHeightRelatedValue / spectralWavePeriodRelatedValue);
	double slopeAngleRadians = ConvertToRadians(slopeAngle);
	double numerator = tan(slopeAngleRadians);
	
	double surfSimilarityParameter = numerator / denominator;

	return surfSimilarityParameter;
}

double Calculator::ResistanceOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer)
{
	return relativeDensity * thicknessTopLayer;	
}

double Calculator::IncrementDegradationOfNaturalStoneRevetment(double tau, double spectralWavePeriod)
{
	double fDegratation = DegradationOfNaturalStoneRevetment(tau, spectralWavePeriod);

	return fDegratation + 2.0 - fDegratation;
}

double Calculator::DegradationOfNaturalStoneRevetment(double tau, double spectralWavePeriod)
{
	double numerator = tau / spectralWavePeriod;
	int denominator = 1000;

	return pow(numerator / denominator, 0.1);
}

double Calculator::IncrementOfTime(double initialTime, double currentTime)
{
	return currentTime - initialTime;
}

double Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double waveAngle, double slopeAngle, double spectralWavePeriod)
{
	return 1000 * spectralWavePeriod * pow(ReferenceDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, waveAngle, slopeAngle, spectralWavePeriod), 10.0);
}

double Calculator::ReferenceDegradationOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double waveAngle, double slopeAngle, double spectralWavePeriod)
{
	return (ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer) / HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod)) * (1 / WaveAngleImpactOnNaturalStoneRevetment(waveAngle));
}

double Calculator::WaveAngleImpactOnNaturalStoneRevetment(double waveAngle)
{
	if (waveAngle > 90 || waveAngle < -90)
	{
		std::cout << "Wave angle not between -90 % 90 degrees.";
		return 0.0;
	}

	double smallestAngle = std::min(78.0, waveAngle);
	
	double waveAngleRadians = ConvertToRadians(smallestAngle);
	double absoluteWaveAngleRadians = fabs(waveAngleRadians);
	double cosinus = cos(absoluteWaveAngleRadians);
	double exponent = (2.0 / 3);
	
	return pow(cosinus, exponent);
}

double Calculator::ConvertToRadians(double degrees)
{
	const double pi = 2 * acos(0.0);
	return degrees * (pi / 180);	
}







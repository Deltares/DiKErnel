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
	double xiFactor = 2.9;
	double surfSimilarityParameter = SurfSimilarityParameter(slopeAngle, spectralWaveHeight, spectralWavePeriod);
	std::tuple<int,int> theta = HeavisideFunction(xiFactor, surfSimilarityParameter);
	double coefficientAP = 4.0;
	double coefficientNP = -0.9;
	double coefficientBP = 0.0;
	double coefficientCP = 0.0;

	double coefficientAS = 0.8;
	double coefficientNS = 0.6;
	double coefficientBS = 0.0;
	double coefficientCS = 0.0;

	double firstPartialDenominator = (coefficientAP * pow(surfSimilarityParameter, coefficientNP) + (coefficientBP * surfSimilarityParameter) + coefficientCP);
	double secondPartialDenominator = (coefficientAS * pow(surfSimilarityParameter, coefficientNS) + (coefficientBS * surfSimilarityParameter) + coefficientCS);
	
	double firstPart = std::get<0>(theta) * firstPartialDenominator;

	double secondPart = std::get<1>(theta) * secondPartialDenominator;
	
	double denominator = firstPart + secondPart;

	return spectralWaveHeight / denominator;
}

std::tuple<int,int> Calculator::HeavisideFunction(double xiFactor, double surfSimilarityParameter)
{
	if (xiFactor > surfSimilarityParameter)
	{
		return std::tuple<int, int>{1, 0};
	}

	return std::tuple<int, int>{0, 1};
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
	int denominator = 1000.0;

	return pow(numerator / denominator, 0.1);
}

double Calculator::IncrementOfTime(double initialTime, double currentTime)
{
	return currentTime - initialTime;
}

double Calculator::ReferenceTimeDegradationOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double waveAngle, double slopeAngle, double spectralWavePeriod)
{
	return 1000.0 * spectralWavePeriod * pow(ReferenceDegradationOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer, spectralWaveHeight, waveAngle, slopeAngle, spectralWavePeriod), 10.0);
}

double Calculator::ReferenceDegradationOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double waveAngle, double slopeAngle, double spectralWavePeriod)
{
	double resistanceOfNaturalStoneRevetment = ResistanceOfNaturalStoneRevetment(relativeDensity, thicknessTopLayer);
	double hydraulicLoadOnNaturalStoneRevetment = HydraulicLoadOnNaturalStoneRevetment(slopeAngle, spectralWaveHeight, spectralWavePeriod);
	double waveAngleImpactOnNaturalStoneRevetment = WaveAngleImpactOnNaturalStoneRevetment(waveAngle);

	return (resistanceOfNaturalStoneRevetment / hydraulicLoadOnNaturalStoneRevetment) * (1.0 / waveAngleImpactOnNaturalStoneRevetment);
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







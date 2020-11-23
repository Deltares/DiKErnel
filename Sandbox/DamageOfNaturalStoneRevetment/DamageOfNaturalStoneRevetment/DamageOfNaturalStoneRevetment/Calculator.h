#pragma once
class Calculator
{
public:
	/// <summary>
	/// Calculates the total natural stone revetment.
	/// </summary>
	/// <param name="initialDamage">The initial damage at the start of the calculation.</param>
	/// <param name="damageOverTime">The damage which occurs during the timespan of the calculation.</param>
	/// <returns>The total damage of natural stone revetment, a value between 0 and 1.</returns>
	static double DamageOfNaturalStoneRevetment(double initialDamage, double damageOverTime);

	void IncrementDamageOfNaturalStoneRevetment();

	void HydraulicLoadOnNaturalStoneRevetment();

	void HeavisideFunction();

	/// <summary>
	/// Calculates the surf similarity parameter.
	/// </summary>
	/// <param name="slopeAngle">The slope angle [°] at the current location.</param>
	/// <param name="spectralWaveHeight">The spectral wave height [m] between t??? and t?.</param>
	/// <param name="spectralWavePeriod">The spectral wave period [s] between t??? and t?.</param>
	/// <returns>The surf similarity parameter at the current time and place.</returns>
	static double SurfSimilarityParameter(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod);

	void ResitanceofNaturalStoneRevetment();

	void IncrementDegradationOfNaturalStoneRevetment();

	void DegradationOfNaturalStoneRevetment();

	void IncrementOfTime();

	void ReferenceTimeDegradationOfNaturalStoneRevetment();

	void ReferenceDegradationOfNaturalStoneRevetment();

	void WaveAngleImpactOnNaturalStoneRevetment();	
};
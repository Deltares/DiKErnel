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
	/// <param name="spectralWaveHeight">The spectral wave height [m] between ti-1 and ti.</param>
	/// <param name="spectralWavePeriod">The spectral wave period [s] between ti-1 and ti.</param>
	/// <returns>The surf similarity parameter at the current time and place.</returns>
	static double SurfSimilarityParameter(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod);

	/// <summary>
	/// Calculates the resistance of natural stone revetment.
	/// </summary>
	/// <param name="relativeDensity">The relative density [-] at the current location.</param>
	/// <param name="thicknessTopLayer">The thickness of the top layer [m] at the current location.</param>
	/// <returns>The resistance of natural stone revetment.</returns>
	static double ResistanceOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer);

	void IncrementDegradationOfNaturalStoneRevetment();

	void DegradationOfNaturalStoneRevetment();

	/// <summary>
	/// Calculates the elapsed time in this timestep.
	/// </summary>
	/// <param name="initialTime">The start of the timestep [s].</param>
	/// <param name="currentTime">The end of the timestep [s].</param>
	/// <returns>The elapsed time of the timestep.</returns>
	static double IncrementOfTime(double initialTime, double currentTime);

	void ReferenceTimeDegradationOfNaturalStoneRevetment();

	void ReferenceDegradationOfNaturalStoneRevetment();

	void WaveAngleImpactOnNaturalStoneRevetment();	
};
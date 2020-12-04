#pragma once

namespace DamageOfNaturalStoneRevetmentCalculator
{
    class Calculator
    {
        public:
            /**
             * @brief Calculates the total natural stone revetment.
             * @param initialDamage The initial damage at the start of the calculation.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @param waveAngle The incoming wave angle [°] relative to the normal line between ti-1 and ti.
             * @param initialTime The start of the timestep [s].
             * @param currentTime The end of the timestep [s].
             * @return The total damage of natural stone revetment, a value between 0 and 1.
            */
            static double CalculateDamageOfNaturalStoneRevetment(double initialDamage, double slopeAngle, double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double spectralWavePeriod, double waveAngle, double initialTime, double currentTime);

            /**
             * @brief Calculates the incremented damage of natural stone revetment.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @param waveAngle The incoming wave angle [°] relative to the normal line between ti-1 and ti.
             * @param initialTime The start of the timestep [s].
             * @param currentTime The end of the timestep [s].
             * @return The incremented damage at the current time and place.
            */
            static double CalculateIncrementDamageOfNaturalStoneRevetment(double slopeAngle, double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double spectralWavePeriod, double waveAngle, double initialTime, double currentTime);

            /**
             * @brief Calculates the hydraulic load on natural stone revetment.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @return The hydraulic load on natural stone revetment at the current time and place.
            */
            static double CalculateHydraulicLoadOnNaturalStoneRevetment(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod);

            /**
             * @brief Calculates the surf similarity parameter.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @return The surf similarity parameter at the current time and place.
            */
            static double CalculateSurfSimilarityParameter(double slopeAngle, double spectralWaveHeight, double spectralWavePeriod);

            /**
             * @brief Calculates the resistance of natural stone revetment.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @return The resistance of natural stone revetment.
            */
            static double CalculateResistanceOfNaturalStoneRevetment(double relativeDensity, double thicknessTopLayer);

            /**
             * @brief Calculates the increment degradation of natural stone revetment at the current time and location.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @param waveAngle The incoming wave angle [°] relative to the normal line between ti-1 and ti.
             * @param initialTime The start of the timestep [s].
             * @param currentTime The end of the timestep [s].
             * @return The increment of degradation of natural stone revetment at the current time and location.
            */
            static double CalculateIncrementDegradationOfNaturalStoneRevetment(double slopeAngle, double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double spectralWavePeriod, double waveAngle, double initialTime, double currentTime);

            /**
             * @brief Calculates the degradation of natural stone revetment.
             * @param referenceTimeDegradationOfNaturalStoneRevetment The calculated reference time degradation of natural stone revetment value to use.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @return The total degradation at the current time.
            */
            static double CalculateDegradationOfNaturalStoneRevetment(double referenceTimeDegradationOfNaturalStoneRevetment, double spectralWavePeriod);

            /**
             * @brief Calculates the elapsed time in this timestep.
             * @param initialTime The start of the timestep [s].
             * @param currentTime The end of the timestep [s].
             * @return The elapsed time of the timestep.
            */
            static double CalculateIncrementOfTime(double initialTime, double currentTime);

            /**
             * @brief Calculates the reference time degradation of natural stone revetment.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @param waveAngle The incoming wave angle [°] relative to the normal line between ti-1 and ti.
             * @return The reference time degradation of natural stone revetment at the current time and place.
            */
            static double CalculateReferenceTimeDegradationOfNaturalStoneRevetment(double slopeAngle, double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double spectralWavePeriod, double waveAngle);

            /**
             * @brief Calculates the reference degradation of natural stone revetment.
             * @param damagePreviousTimeStep The total damage from the previous timestep.
             * @param slopeAngle The slope angle [°] at the current location.
             * @param relativeDensity The relative density [-] at the current location.
             * @param thicknessTopLayer The thickness of the top layer [m] at the current location.
             * @param spectralWaveHeight The spectral wave height [m] between ti-1 and ti.
             * @param spectralWavePeriod The spectral wave period [s] between ti-1 and ti.
             * @param waveAngle The incoming wave angle [°] relative to the normal line between ti-1 and ti.
             * @return The reference degradation of natural stone revetment at the current time and place.
            */
            static double CalculateReferenceDegradationOfNaturalStoneRevetment(double damagePreviousTimeStep, double slopeAngle, double relativeDensity, double thicknessTopLayer, double spectralWaveHeight, double spectralWavePeriod, double waveAngle);

            /**
             * @brief Calculates the wave angle impact of natural stone revetment.
             * @param waveAngle The incoming wave handle [°] relative to the normal line between ti-1 and ti.
             * @return The wave angle impact at the current time.
            */
            static double CalculateWaveAngleImpactOnNaturalStoneRevetment(double waveAngle);

            /**
             * @brief Converts a value in degrees to a value in radians.
             * @param degrees The amount of degrees [°].
             * @return The amount of radians.
            */
            static double ConvertDegreesToRadians(double degrees);
    };
}

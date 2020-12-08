#pragma once

namespace DamageOfNaturalStoneRevetmentCalculator
{
    /*!
     * \brief Calculator for calculating natural stone revetment.
     */
    class Calculator
    {
        public:
            /*!
             * \brief Calculates the total natural stone revetment.
             * \param initialDamage
             *        The initial damage at the start of the calculation.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \param initialTime
             *        The start of the timestep.
             *        Unit = [s]
             * \param currentTime
             *        The end of the timestep.
             *        Unit = [s]
             * \return The total damage of natural stone revetment.
             *         Unit = [-]
             *         Range = [0, 1]
             */
            static double CalculateDamageOfNaturalStoneRevetment(
                double initialDamage,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double initialTime,
                double currentTime);

            /*!
             * \brief Calculates the incremented damage of natural stone revetment.
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \param initialTime
             *        The start of the timestep.
             *        Unit = [s]
             * \param currentTime
             *        The end of the timestep.
             *        Unit = [s]
             * \return The incremented damage at the current time and place.
             *         Unit = [-]
             */
            static double CalculateIncrementDamageOfNaturalStoneRevetment(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double initialTime,
                double currentTime);

            /*!
             * \brief Calculates the hydraulic load on natural stone revetment.
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The hydraulic load on natural stone revetment at the current time and place.
             *         Unit = [-]
             */
            static double CalculateHydraulicLoadOnNaturalStoneRevetment(
                double slopeAngle,
                double spectralWaveHeight,
                double spectralWavePeriod);

            /*!
             * \brief Calculates the surf similarity parameter.
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The surf similarity parameter at the current time and place.
             *         Unit = [-]
             */
            static double CalculateSurfSimilarityParameter(
                double slopeAngle,
                double spectralWaveHeight,
                double spectralWavePeriod);

            /*!
             * \brief Calculates the resistance of natural stone revetment.
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \return The resistance of natural stone revetment.
             *         Unit = [-]
             */
            static double CalculateResistanceOfNaturalStoneRevetment(
                double relativeDensity,
                double thicknessTopLayer);

            /*!
             * \brief Calculates the increment degradation of natural stone revetment at the current time and location.
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \param initialTime
             *        The start of the timestep.
             *        Unit = [s]
             * \param currentTime
             *        The end of the timestep.
             *        Unit = [s]
             * \return The increment of degradation of natural stone revetment at the current time and location.
             *         Unit = [-]
             */
            static double CalculateIncrementDegradationOfNaturalStoneRevetment(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double initialTime,
                double currentTime);

            /*!
             * \brief Calculates the degradation of natural stone revetment.
             * \param referenceTimeDegradationOfNaturalStoneRevetment
             *        The calculated reference time degradation of natural stone revetment value to use.
             *        Unit = [-]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The total degradation at the current time.
             *         Unit = [-]
             */
            static double CalculateDegradationOfNaturalStoneRevetment(
                double referenceTimeDegradationOfNaturalStoneRevetment,
                double spectralWavePeriod);

            /*!
             * \brief Calculates the elapsed time in this timestep.
             * \param initialTime
             *        The start of the timestep.
             *        Unit = [s]
             * \param currentTime
             *        The end of the timestep.
             *        Unit = [s]
             * \return The elapsed time of the timestep.
             *         Unit = [s]
             */
            static double CalculateIncrementOfTime(
                double initialTime,
                double currentTime);

            /*!
             * \brief Calculates the reference time degradation of natural stone revetment.
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \return The reference time degradation of natural stone revetment at the current time and place.
             *         Unit = [-]
             */
            static double CalculateReferenceTimeDegradationOfNaturalStoneRevetment(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle);

            /*!
             * \brief Calculates the reference degradation of natural stone revetment.
             * \param damagePreviousTimeStep
             *        The total damage from the previous timestep.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle  at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \return The reference degradation of natural stone revetment at the current time and place.
             *         Unit = [-]
             */
            static double CalculateReferenceDegradationOfNaturalStoneRevetment(
                double damagePreviousTimeStep,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle);

            /*!
             * \brief Calculates the wave angle impact of natural stone revetment.
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between
             *        ti-1 and ti.
             *        Unit = [°]
             * \return The wave angle impact at the current time.
             *         Unit = [-]
             */
            static double CalculateWaveAngleImpactOnNaturalStoneRevetment(
                double waveAngle);

        private:
            static double pi;

            static double ConvertDegreesToRadians(
                double degrees);
    };
}

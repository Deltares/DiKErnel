// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all methods to perform a calculation with natural stone revetment.
     */
    class NaturalStoneRevetment
    {
        public:
            /*!
             * \brief Calculates the total damage.
             * \param initialDamage
             *        The initial damage at the start of the calculation.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle at the current location.
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
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \param startTime
             *        The start time.
             *        Unit = [s]
             * \param endTime
             *        The end time.
             *        Unit = [s]
             * \return The calculated total damage.
             *         Unit = [-]
             *         Range = [0, 1]
             */
            static double CalculateDamage(
                const double initialDamage,
                const double slopeAngle,
                const double relativeDensity,
                const double thicknessTopLayer,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double waveAngle,
                const double startTime,
                const double endTime,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs,
                const double waveAngleMaximum,
                const double damagePreviousTimestep);

            /*!
             * \brief Calculates the increment damage.
             * \param slopeAngle
             *        The slope angle at the current location.
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
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \param startTime
             *        The start time.
             *        Unit = [s]
             * \param endTime
             *        The end time.
             *        Unit = [s]
             * \return The calculated increment damage.
             *         Unit = [-]
             */
            static double CalculateIncrementDamage(
                const double slopeAngle,
                const double relativeDensity,
                const double thicknessTopLayer,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double waveAngle,
                const double startTime,
                const double endTime,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs,
                const double waveAngleMaximum,
                const double damagePreviousTimestep);

            /*!
             * \brief Calculates the hydraulic load.
             * \param slopeAngle
             *        The slope angle at the current location.
             *        Unit = [°]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The calculated hydraulic load.
             *         Unit = [-]
             */
            static double CalculateHydraulicLoad(
                const double slopeAngle,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs);

            /*!
             * \brief Calculates the surf similarity parameter.
             * \param slopeAngle
             *        The slope angle at the current location.
             *        Unit = [°]
             * \param spectralWaveHeight
             *        The spectral wave height between ti-1 and ti.
             *        Unit = [m]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The calculated surf similarity parameter.
             *         Unit = [-]
             */
            static double CalculateSurfSimilarityParameter(
                double slopeAngle,
                double spectralWaveHeight,
                double spectralWavePeriod);

            /*!
             * \brief Calculates the resistance.
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \return The calculated resistance.
             *         Unit = [-]
             */
            static double CalculateResistance(
                double relativeDensity,
                double thicknessTopLayer);

            /*!
                 * \brief Calculates the increment degradation.
                 * \param slopeAngle
                 *        The slope angle at the current location.
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
                 *        The incoming wave angle relative to the normal line between ti-1 and ti.
                 *        Unit = [°]
                 * \param startTime
                 *        The start time.
                 *        Unit = [s]
                 * \param endTime
                 *        The end time.
                 *        Unit = [s]
                 * \return The calculated increment degradation.
                 *         Unit = [-]
                 */
            static double CalculateIncrementDegradation(
                const double slopeAngle,
                const double relativeDensity,
                const double thicknessTopLayer,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double waveAngle,
                const double startTime,
                const double endTime,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs,
                const double waveAngleMaximum,
                const double damagePreviousTimestep);

            /*!
             * \brief Calculates the degradation.
             * \param referenceTimeDegradation
             *        The reference time degradation.
             *        Unit = [-]
             * \param spectralWavePeriod
             *        The spectral wave period between ti-1 and ti.
             *        Unit = [s]
             * \return The calculated degradation.
             *         Unit = [-]
             */
            static double CalculateDegradation(
                double referenceTimeDegradation,
                double spectralWavePeriod);

            /*!
             * \brief Calculates the reference time degradation.
             * \param slopeAngle
             *        The slope angle at the current location.
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
             * \return The calculated reference time degradation.
             *         Unit = [-]
             */
            static double CalculateReferenceTimeDegradation(
                const double slopeAngle,
                const double relativeDensity,
                const double thicknessTopLayer,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double waveAngle,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs,
                const double waveAngleMaximum,
                const double damagePreviousTimestep);

            /*!
             * \brief Calculates the reference degradation.
             * \param damagePreviousTimeStep
             *        The total damage from the previous time step.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle at the current location.
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
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \return The calculated reference degradation.
             *         Unit = [-]
             */
            static double CalculateReferenceDegradation(
                const double damagePreviousTimeStep,
                const double slopeAngle,
                const double relativeDensity,
                const double thicknessTopLayer,
                const double spectralWaveHeight,
                const double spectralWavePeriod,
                const double waveAngle,
                const double ap,
                const double np,
                const double bp,
                const double cp,
                const double as,
                const double ns,
                const double bs,
                const double cs,
                const double waveAngleMaximum);

            /*!
             * \brief Calculates the wave angle impact.
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \return The calculated wave angle impact.
             *         Unit = [-]
             */
            static double CalculateWaveAngleImpact(
                const double waveAngle,
                const double waveAngleMaximum);

        private:
            static double CalculateIncrementOfTime(
                double startTime,
                double endTime);

            static double ConvertDegreesToRadians(
                double degrees);
    };
}

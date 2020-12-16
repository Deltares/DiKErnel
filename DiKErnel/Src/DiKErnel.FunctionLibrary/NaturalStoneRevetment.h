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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
             * \return The calculated total damage.
             *         Unit = [-]
             *         Range = [0, 1]
             */
            static double CalculateDamage(
                double initialDamage,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double startTime,
                double endTime,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double waveAngleMaximum,
                double xiFactor);

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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param initialDamage
             *        The cumulative damage from previous timestep.
             *        Unit = [-]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
             * \return The calculated increment damage.
             *         Unit = [-]
             */
            static double CalculateIncrementDamage(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double startTime,
                double endTime,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double waveAngleMaximum,
                double initialDamage,
                double xiFactor);

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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
             * \return The calculated hydraulic load.
             *         Unit = [-]
             */
            static double CalculateHydraulicLoad(
                double slopeAngle,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double xiFactor);

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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param initialDamage
             *        The cumulative damage from previous timestep.
             *        Unit = [-]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
                 * \return The calculated increment degradation.
                 *         Unit = [-]
                 */
            static double CalculateIncrementDegradation(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double startTime,
                double endTime,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double waveAngleMaximum,
                double initialDamage,
                double xiFactor);

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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param initialDamage
             *        The cumulative damage from previous timestep.
             *        Unit = [-]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
             * \return The calculated reference time degradation.
             *         Unit = [-]
             */
            static double CalculateReferenceTimeDegradation(
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double waveAngleMaximum,
                double initialDamage,
                double xiFactor);

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
             * \param ap
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param bp
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param cp
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param np
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param as
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param bs
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param cs
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param ns
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param xiFactor
             *        The similarity parameter threshold,
             *        determines whether there is plunging or surging.
             *        Unit = [-]
             * \return The calculated reference degradation.
             *         Unit = [-]
             */
            static double CalculateReferenceDegradation(
                double damagePreviousTimeStep,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double waveAngle,
                double ap,
                double bp,
                double cp,
                double np,
                double as,
                double bs,
                double cs,
                double ns,
                double waveAngleMaximum,
                double xiFactor);

            /*!
             * \brief Calculates the wave angle impact.
             * \param waveAngle
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \return The calculated wave angle impact.
             *         Unit = [-]
             */
            static double CalculateWaveAngleImpact(
                double waveAngle,
                double waveAngleMaximum);

        private:
            static double CalculateIncrementOfTime(
                double startTime,
                double endTime);

            static double ConvertDegreesToRadians(
                double degrees);
    };
}

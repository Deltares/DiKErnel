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
     * \brief Class that holds all methods to perform calculations for natural stone based
     *        revetments.
     */
    class NaturalStoneRevetment
    {
        public:
            /*!
             * \brief Calculates the total damage.
             * \param initialDamage
             *        The damage at the start of the calculation.
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
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
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
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double waveAngleMaximum,
                double similarityParameterThreshold);

            /*!
             * \brief Calculates the increment of damage.
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
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param initialDamage
             *        The cumulative damage from the previous time step.
             *        Unit = [-]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
             *        Unit = [-]
             * \return The calculated increment of damage.
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
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double waveAngleMaximum,
                double initialDamage,
                double similarityParameterThreshold);

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
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
             *        Unit = [-]
             * \return The calculated hydraulic load.
             *         Unit = [-]
             */
            static double CalculateHydraulicLoad(
                double slopeAngle,
                double spectralWaveHeight,
                double spectralWavePeriod,
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double similarityParameterThreshold);

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
            * \brief Calculates the increment of degradation.
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
            * \param plungingCoefficientA
            *        The A coefficient for plunging.
            *        Unit = [-]
            * \param plungingCoefficientB
            *        The B coefficient for plunging.
            *        Unit = [-]
            * \param plungingCoefficientC
            *        The C coefficient for plunging.
            *        Unit = [-]
            * \param plungingCoefficientN
            *        The N coefficient for plunging.
            *        Unit = [-]
            * \param surgingCoefficientA
            *        The A coefficient for surging.
            *        Unit = [-]
            * \param surgingCoefficientB
            *        The B coefficient for surging.
            *        Unit = [-]
            * \param surgingCoefficientC
            *        The C coefficient for surging.
            *        Unit = [-]
            * \param surgingCoefficientN
            *        The N coefficient for surging.
            *        Unit = [-]
            * \param waveAngleMaximum
            *        The maximum incoming wave angle.
            *        Unit = [°]
            * \param initialDamage
            *        The cumulative damage from the previous time step.
            *        Unit = [-]
            * \param similarityParameterThreshold
            *        The similarity parameter threshold, which determines whether there is
            *        plunging or surging.
            *        Unit = [-]
            * \return The calculated increment of degradation.
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
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double waveAngleMaximum,
                double initialDamage,
                double similarityParameterThreshold);

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
             *        The incoming wave angle relative to the normal line between ti-1 and ti.
             *        Unit = [°]
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param initialDamage
             *        The cumulative damage from the previous time step.
             *        Unit = [-]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
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
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double waveAngleMaximum,
                double initialDamage,
                double similarityParameterThreshold);

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
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param waveAngleMaximum
             *        The maximum incoming wave angle.
             *        Unit = [°]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
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
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double waveAngleMaximum,
                double similarityParameterThreshold);

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

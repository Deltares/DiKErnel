// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "NaturalStoneRevetmentHydraulicLoadInput.h"
#include "NaturalStoneRevetmentLimitLoadingInput.h"
#include "NaturalStoneRevetmentOuterSlopeInput.h"

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all natural stone revetment specific calculation routines.
     */
    class NaturalStoneRevetmentFunctions
    {
        public:
            /*!
             * \brief Calculates the increment of damage.
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [m]
             * \param resistance
             *        The resistance.
             *        Unit = [m]
             * \param incrementDegradation
             *        The increment of degradation.
             *        Unit = [-]
             * \param waveAngleImpact
             *        The wave impact with respect to the wave angle.
             *        Unit = [-]
             * \return The increment of damage.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double IncrementDamage(
                double hydraulicLoad,
                double resistance,
                double incrementDegradation,
                double waveAngleImpact);

            /*!
             * \brief Calculates the hydraulic load.
             * \param input
             *        The input to use for the calculation.
             * \return The hydraulic load.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double HydraulicLoad(
                const NaturalStoneRevetmentHydraulicLoadInput& input);

            /*!
             * \brief Calculates the outer slope.
             * \param input
             *        The input to use for the calculation.
             * \return The outer slope.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double OuterSlope(
                const NaturalStoneRevetmentOuterSlopeInput& input);

            /*!
             * \brief Calculates the slope upper level.
             * \param outerToeHeight
             *        The height of the outer toe.
             *        Unit = [m]
             * \param outerCrestHeight
             *        The height of the outer crest.
             *        Unit = [m]
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param slopeUpperLevelAus
             *        The Aus coefficient.
             *        Unit = [-]
             * \return The slope upper level.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double SlopeUpperLevel(
                double outerToeHeight,
                double outerCrestHeight,
                double waterLevel,
                double waveHeightHm0,
                double slopeUpperLevelAus);

            /*!
             * \brief Calculates the slope lower level.
             * \param outerToeHeight
             *        The height of the outer toe.
             *        Unit = [m]
             * \param slopeUpperLevel
             *        The slope upper level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param slopeLowerLevelAls
             *        The Als coefficient.
             *        Unit = [-]
             * \return The slope lower level.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double SlopeLowerLevel(
                double outerToeHeight,
                double slopeUpperLevel,
                double waveHeightHm0,
                double slopeLowerLevelAls);

            /*!
             * \brief Calculates the upper limit of loading.
             * \param input
             *        The input to use for the calculation.
             * \return The upper limit of loading.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double UpperLimitLoading(
                const NaturalStoneRevetmentLimitLoadingInput& input);

            /*!
             * \brief Calculates the lower limit of loading.
             * \param input
             *        The input to use for the calculation.
             * \return The lower limit of loading.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double LowerLimitLoading(
                const NaturalStoneRevetmentLimitLoadingInput& input);

            /*!
             * \brief Calculates the depth of the maximum wave load.
             * \param distanceMaximumWaveElevation
             *        The maximum distance of wave elevation.
             *        Unit = [m]
             * \param normativeWidthWaveImpact
             *        The normative width of wave impact.
             *        Unit = [m]
             * \param slopeAngle
             *        The slope angle.
             *        Unit = [deg]
             * \return The depth of the maximum wave load.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double DepthMaximumWaveLoad(
                double distanceMaximumWaveElevation,
                double normativeWidthWaveImpact,
                double slopeAngle);

            /*!
             * \brief Calculates the maximum distance of wave elevation.
             * \param impactShallowWater
             *        The impact in shallow water.
             *        Unit = [-]
             * \param waveSteepnessDeepWater
             *        The wave steepness in deep water
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param distanceMaximumWaveElevationAsmax
             *        The Asmax coefficient.
             *        Unit = [-]
             * \param distanceMaximumWaveElevationBsmax
             *        The Bsmax coefficient.
             *        Unit = [-]
             * \return The maximum distance of wave elevation.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double DistanceMaximumWaveElevation(
                double impactShallowWater,
                double waveSteepnessDeepWater,
                double waveHeightHm0,
                double distanceMaximumWaveElevationAsmax,
                double distanceMaximumWaveElevationBsmax);

            /*!
             * \brief Calculates the normative width of wave impact.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param normativeWidthWaveImpactAwi
             *        The Awi coefficient.
             *        Unit = [-]
             * \param normativeWidthWaveImpactBwi
             *        The Bwi coefficient.
             *        Unit = [-]
             * \return The normative width of wave impact.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double NormativeWidthWaveImpact(
                double surfSimilarityParameter,
                double waveHeightHm0,
                double normativeWidthWaveImpactAwi,
                double normativeWidthWaveImpactBwi);

            /*!
             * \brief Calculates the wave impact with respect to the wave angle.
             * \param waveAngle
             *        The wave angle.
             *        Unit = [deg]
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             *        Unit = [deg]
             * \return The wave impact with respect to the wave angle.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double WaveAngleImpact(
                double waveAngle,
                double waveAngleImpactBetamax);

            /*!
             * \brief Calculates the resistance.
             * \param relativeDensity
             *        The relative density.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             *        Unit = [m]
             * \return The resistance.
             *         Unit = [m]
             */
            [[nodiscard]]
            static double Resistance(
                double relativeDensity,
                double thicknessTopLayer);

            /*!
             * \brief Calculates the increment of degradation.
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             *        Unit = [s]
             * \param incrementTime
             *        The increment of time.
             *        Unit = [s]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \return The increment of degradation.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double IncrementDegradation(
                double referenceTimeDegradation,
                double incrementTime,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference time of degradation.
             * \param referenceDegradation
             *        The reference of degradation.
             *        Unit = [-]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \return The reference time of degradation.
             *         Unit = [s]
             */
            [[nodiscard]]
            static double ReferenceTimeDegradation(
                double referenceDegradation,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of degradation.
             * \param resistance
             *        The resistance.
             *        Unit = [m]
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [m]
             * \param waveAngleImpact
             *        The wave impact with respect to the wave angle.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return The reference of degradation.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double ReferenceDegradation(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double initialDamage);

            /*!
             * \brief Calculates the duration in the time step of failure.
             * \param referenceTimeFailure
             *        The reference time of failure.
             *        Unit = [s]
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             *        Unit = [s]
             * \return The duration in the time step of failure.
             *         Unit = [s]
             */
            [[nodiscard]]
            static double DurationInTimeStepFailure(
                double referenceTimeFailure,
                double referenceTimeDegradation);

            /*!
             * \brief Calculates the reference time of failure.
             * \param referenceFailure
             *        The reference of failure.
             *        Unit = [-]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [s]
             * \return The reference time of failure.
             *         Unit = [s]
             */
            [[nodiscard]]
            static double ReferenceTimeFailure(
                double referenceFailure,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of failure.
             * \param resistance
             *        The resistance.
             *        Unit = [m]
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [m]
             * \param waveAngleImpact
             *        The wave impact with respect to the wave angle.
             *        Unit = [-]
             * \param failureNumber
             *        The failure number.
             *        Unit = [-]
             * \return The reference of failure.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double ReferenceFailure(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double failureNumber);

        private:
            [[nodiscard]]
            static double SingleSlopePart(
                double slopeUpperLevel,
                double slopeLowerLevel,
                double slopeUpperPosition,
                double slopeLowerPosition);

            [[nodiscardd]]
            static double OuterSlopeWithBerm(
                const NaturalStoneRevetmentOuterSlopeInput& input);

            [[nodiscard]]
            static double SlopeLowerSlopeBerm(
                double crestOuterBermPosition,
                double crestOuterBermHeight,
                double slopeLowerLevel,
                double slopeLowerPosition);

            [[nodiscard]]
            static double SlopeBermUpperSlope(
                double notchOuterBermPosition,
                double notchOuterBermHeight,
                double slopeUpperLevel,
                double slopeUpperPosition);

            [[nodiscard]]
            static double SlopeLowerUpperSlope(
                double slopeUpperLevel,
                double slopeLowerLevel,
                double distanceBermUpperSlope,
                double distanceBermLowerSlope);

            [[nodiscard]]
            static double DistanceBermUpperSlope(
                double crestOuterBermHeight,
                double notchOuterBermPosition,
                double notchOuterBermHeight,
                double slopeUpperLevel,
                double slopeUpperPosition);

            [[nodiscard]]
            static double DistanceBermLowerSlope(
                double crestOuterBermPosition,
                double crestOuterBermHeight,
                double notchOuterBermHeight,
                double slopeLowerLevel,
                double slopeLowerPosition);

            [[nodiscard]]
            static double Degradation(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            [[nodiscard]]
            static double ReferenceTime(
                double reference,
                double wavePeriodTm10);

            [[nodiscard]]
            static double Reference(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double value);
    };
}

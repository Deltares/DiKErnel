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
     * \brief Class that holds all natural stone revetment specific calculation routines.
     */
    class NaturalStoneRevetment
    {
        public:
            /*!
             * \brief Calculates the increment of damage.
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [-]
             * \param resistance
             *        The resistance.
             *        Unit = [-]
             * \param incrementDegradation
             *        The increment of degradation.
             *        Unit = [-]
             * \param waveAngleImpact
             *        The angle of the wave impact.
             *        Unit = [-]
             * \return The increment of damage.
             *         Unit = [-]
             */
            static double IncrementDamage(
                double hydraulicLoad,
                double resistance,
                double incrementDegradation,
                double waveAngleImpact);

            /*!
             * \brief Calculates the hydraulic load.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [-]
             * \param hydraulicLoadA
             *        The A coefficient.
             *        Unit = [-]
             * \param hydraulicLoadB
             *        The B coefficient.
             *        Unit = [-]
             * \param hydraulicLoadC
             *        The C coefficient.
             *        Unit = [-]
             * \param hydraulicLoadN
             *        The N coefficient.
             *        Unit = [-]
             * \return The hydraulic load.
             *         Unit = [-]
             */
            static double HydraulicLoad(
                double surfSimilarityParameter,
                double waveHeightHm0,
                double hydraulicLoadA,
                double hydraulicLoadB,
                double hydraulicLoadC,
                double hydraulicLoadN);

            /*!
             * \brief Calculates the upper limit of loading.
             * \param depthMaximumWaveLoad
             *        The maximum wave load depth.
             *        Unit = [-]
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waterLevel
             *        The water level.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [-]
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             *        Unit = [-]
             * \param upperLimitLoadingBul
             *        The Bul coefficient.
             *        Unit = [-]
             * \param upperLimitLoadingCul
             *        The Cul coefficient.
             *        Unit = [-]
             * \return The upper limit of loading.
             *         Unit = [-]
             */
            static double UpperLimitLoading(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0,
                double upperLimitLoadingAul,
                double upperLimitLoadingBul,
                double upperLimitLoadingCul);

            /*!
             * \brief Calculates the lower limit of loading.
             * \param depthMaximumWaveLoad
             *        The maximum wave load depth.
             *        Unit = [-]
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waterLevel
             *        The water level.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [-]
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             *        Unit = [-]
             * \param lowerLimitLoadingBll
             *        The Bll coefficient.
             *        Unit = [-]
             * \param lowerLimitLoadingCll
             *        The Cll coefficient.
             *        Unit = [-]
             * \return The lower limit of loading.
             *         Unit = [-]
             */
            static double LowerLimitLoading(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0,
                double lowerLimitLoadingAll,
                double lowerLimitLoadingBll,
                double lowerLimitLoadingCll);

            /*!
             * \brief Calculates the maximum wave load depth.
             * \param distanceMaximumWaveElevation
             *        The maximum distance of wave elevation.
             *        Unit = [-]
             * \param normativeWidthWaveImpact
             *        The normative width of wave impact.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle.
             *        Unit = [-]
             * \return The maximum wave load depth.
             *         Unit = [-]
             */
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
             *        Unit = [-]
             * \param distanceMaximumWaveElevationAsmax
             *        The Asmax coefficient.
             *        Unit = [-]
             * \param distanceMaximumWaveElevationBsmax
             *        The Bsmax coefficient.
             *        Unit = [-]
             * \return The maximum distance of wave elevation.
             *         Unit = [-]
             */
            static double DistanceMaximumWaveElevation(
                double impactShallowWater,
                double waveSteepnessDeepWater,
                double waveHeightHm0,
                double distanceMaximumWaveElevationAsmax,
                double distanceMaximumWaveElevationBsmax);

            /*!
             * \brief Calculates the impact in shallow water.
             * \return The impact in shallow water.
             *         Unit = [-]
             */
            static double ImpactShallowWater();

            /*!
             * \brief Calculates the normative width of wave impact.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             *        Unit = [-]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [-]
             * \param normativeWidthWaveImpactAwi
             *        The Awi coefficient.
             *        Unit = [-]
             * \param normativeWidthWaveImpactBwi
             *        The Bwi coefficient.
             *        Unit = [-]
             * \return The normative width of wave impact.
             *         Unit = [-]
             */
            static double NormativeWidthWaveImpact(
                double surfSimilarityParameter,
                double waveHeightHm0,
                double normativeWidthWaveImpactAwi,
                double normativeWidthWaveImpactBwi);

            /*!
             * \brief Calculates the angle of wave impact.
             * \param waveAngle
             *        The wave angle.
             *        Unit = [-]
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             *        Unit = [-]
             * \return The angle of wave impact.
             *         Unit = [-]
             */
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
             *        Unit = [-]
             * \return The resistance.
             *         Unit = [-]
             */
            static double Resistance(
                double relativeDensity,
                double thicknessTopLayer);

            /*!
             * \brief Calculates the increment of degradation.
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             *        Unit = [-]
             * \param incrementTime
             *        The increment of time.
             *        Unit = [-]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [-]
             * \return The increment of degradation.
             *         Unit = [-]
             */
            static double IncrementDegradation(
                double referenceTimeDegradation,
                double incrementTime,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the degradation.
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             *        Unit = [-]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [-]
             * \return The degradation.
             *         Unit = [-]
             */
            static double Degradation(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference time of degradation.
             * \param referenceDegradation
             *        The reference of degradation.
             *        Unit = [-]
             * \param wavePeriodTm10
             *        The wave period.
             *        Unit = [-]
             * \return The reference time of degradation.
             *         Unit = [-]
             */
            static double ReferenceTimeDegradation(
                double referenceDegradation,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of degradation.
             * \param resistance
             *        The resistance.
             *        Unit = [-]
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [-]
             * \param waveAngleImpact
             *        The angle of wave impact.
             *        Unit = [-]
             * \param initialDamage
             *        The initial damage.
             *        Unit = [-]
             * \return The reference of degradation.
             *         Unit = [-]
             */
            static double ReferenceDegradation(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double initialDamage);

            /*!
             * \brief Calculates the duration in the time step of failure.
             * \param referenceTimeFailure
             *        The reference time of failure.
             *        Unit = [-]
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             *        Unit = [-]
             * \return The duration in the time step of failure.
             *         Unit = [-]
             */
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
             *        Unit = [-]
             * \return The reference time of failure.
             *         Unit = [-]
             */
            static double ReferenceTimeFailure(
                double referenceFailure,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of failure.
             * \param resistance
             *        The resistance.
             *        Unit = [-]
             * \param hydraulicLoad
             *        The hydraulic load.
             *        Unit = [-]
             * \param waveAngleImpact
             *        The angle of wave impact.
             *        Unit = [-]
             * \param failureNumber
             *        The failure number.
             *        Unit = [-]
             * \return The reference of failure.
             *         Unit = [-]
             */
            static double ReferenceFailure(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double failureNumber);
    };
}

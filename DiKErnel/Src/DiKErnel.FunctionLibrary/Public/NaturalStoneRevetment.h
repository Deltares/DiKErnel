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
             * \param resistance
             *        The resistance.
             * \param incrementDegradation
             *        The increment of degradation.
             * \param waveAngleImpact
             *        The angle of the wave impact.
             * \return The increment of damage.
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
             * \param waveHeightHm0
             *        The wave height.
             * \param hydraulicLoadA
             *        The A coefficient.
             * \param hydraulicLoadB
             *        The B coefficient.
             * \param hydraulicLoadC
             *        The C coefficient.
             * \param hydraulicLoadN
             *        The N coefficient.
             * \return The hydraulic load.
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
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waterLevel
             *        The water level.
             * \param waveHeightHm0
             *        The wave height.
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             * \param upperLimitLoadingBul
             *        The Bul coefficient.
             * \param upperLimitLoadingCul
             *        The Cul coefficient.
             * \return The upper limit of loading.
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
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waterLevel
             *        The water level.
             * \param waveHeightHm0
             *        The wave height.
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             * \param lowerLimitLoadingBll
             *        The Bll coefficient.
             * \param lowerLimitLoadingCll
             *        The Cll coefficient.
             * \return The lower limit of loading.
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
              * \param normativeWidthWaveImpact
              *        The normative width of wave impact.
              * \param slopeAngle
              *        The slope angle.
              * \return The maximum wave load depth.
              */
            static double DepthMaximumWaveLoad(
                double distanceMaximumWaveElevation,
                double normativeWidthWaveImpact,
                double slopeAngle);

            /*!
             * \brief Calculates the maximum distance of wave elevation.
             * \param impactShallowWater
             *        The impact in shallow water.
             * \param waveSteepnessDeepWater
             *        The wave steepness in deep water
             * \param waveHeightHm0
             *        The wave height.
             * \param distanceMaximumWaveElevationAsmax
             *        The Asmax coefficient.
             * \param distanceMaximumWaveElevationBsmax
             *        The Bsmax coefficient.
             * \return The maximum distance of wave elevation.
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
             */
            static double ImpactShallowWater();

            /*!
             * \brief Calculates the normative width of wave impact.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waveHeightHm0
             *        The wave height.
             * \param normativeWidthWaveImpactAwi
             *        The Awi coefficient.
             * \param normativeWidthWaveImpactBwi
             *        The Bwi coefficient.
             * \return The normative width of wave impact.
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
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             * \return The angle of wave impact.
             */
            static double WaveAngleImpact(
                double waveAngle,
                double waveAngleImpactBetamax);

            /*!
             * \brief Calculates the resistance.
             * \param relativeDensity
             *        The relative density.
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             * \return The resistance.
             */
            static double Resistance(
                double relativeDensity,
                double thicknessTopLayer);

            /*!
             * \brief Calculates the increment of degradation.
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             * \param incrementTime
             *        The increment of time.
             * \param wavePeriodTm10
             *        The wave period.
             * \return The increment of degradation.
             */
            static double IncrementDegradation(
                double referenceTimeDegradation,
                double incrementTime,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the degradation.
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             * \param wavePeriodTm10
             *        The wave period.
             * \return The degradation.
             */
            static double Degradation(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference time of degradation.
             * \param referenceDegradation
             *        The reference of degradation.
             * \param wavePeriodTm10
             *        The wave period.
             * \return The reference time of degradation.
             */
            static double ReferenceTimeDegradation(
                double referenceDegradation,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of degradation.
             * \param resistance
             *        The resistance.
             * \param hydraulicLoad
             *        The hydraulic load.
             * \param waveAngleImpact
             *        The angle of wave impact.
             * \param initialDamage
             *        The initial damage.
             * \return The reference of degradation.
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
             * \param referenceTimeDegradation
             *        The reference time of degradation.
             * \return The duration in the time step of failure.
             */
            static double DurationInTimeStepFailure(
                double referenceTimeFailure,
                double referenceTimeDegradation);

            /*!
             * \brief Calculates the reference time of failure.
             * \param referenceFailure
             *        The reference of failure.
             * \param wavePeriodTm10
             *        The wave period.
             * \return The reference time of failure.
             */
            static double ReferenceTimeFailure(
                double referenceFailure,
                double wavePeriodTm10);

            /*!
             * \brief Calculates the reference of failure.
             * \param resistance
             *        The resistance.
             * \param hydraulicLoad
             *        The hydraulic load.
             * \param waveAngleImpact
             *        The angle of wave impact.
             * \param failureNumber
             *        The failure number.
             * \return The reference of failure.
             */
            static double ReferenceFailure(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double failureNumber);
    };
}

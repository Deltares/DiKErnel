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
             *        The wave angle of impact.
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
             *        The hydraulic load A.
             * \param hydraulicLoadB
             *        The hydraulic load B.
             * \param hydraulicLoadC
             *        The hydraulic load C.
             * \param hydraulicLoadN
             *        The hydraulic load N.
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
             * \brief Calculates the upper limit loading.
             * \param depthMaximumWaveLoad
             *        The maximum wave load depth.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waterLevel
             *        The water level.
             * \param waveHeightHm0
             *        The wave height.
             * \param upperLimitLoadingAul
             *        The upper limit loading Aul.
             * \param upperLimitLoadingBul
             *        The upper limit loading Bul.
             * \param upperLimitLoadingCul
             *        The upper limit loading Cul.
             * \return The upper limit loading.
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
              * \brief Calculates the lower limit loading.
              * \param depthMaximumWaveLoad
              *        The maximum wave load depth.
              * \param surfSimilarityParameter
              *        The surf similarity parameter.
              * \param waterLevel
              *        The water level.
              * \param waveHeightHm0
              *        The wave height.
              * \param lowerLimitLoadingAll
              *        The lower limit loading All.
              * \param lowerLimitLoadingBll
              *        The lower limit loading Bll.
              * \param lowerLimitLoadingCll
              *        The lower limit loading Cll.
              * \return The lower limit loading.
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
             * \brief Calculates the maximum distance wave elevation.
             * \param impactShallowWater
             *        The impact shallow water.
             * \param waveSteepnessDeepWater
             *        The wave steepness deep water
             * \param waveHeightHm0
             *        The wave height.
             * \param distanceMaximumWaveElevationAsmax
             *        The the maximum distance wave elevation Asmax.
             * \param distanceMaximumWaveElevationBsmax
             *        The the maximum distance wave elevation Bsmax.
             * \return The maximum distance wave elevation.
             */
            static double DistanceMaximumWaveElevation(
                double impactShallowWater,
                double waveSteepnessDeepWater,
                double waveHeightHm0,
                double distanceMaximumWaveElevationAsmax,
                double distanceMaximumWaveElevationBsmax);

            static double ImpactShallowWater();

            static double NormativeWidthWaveImpact(
                double surfSimilarityParameter,
                double waveHeightHm0,
                double normativeWidthWaveImpactAwi,
                double normativeWidthWaveImpactBwi);

            static double WaveAngleImpact(
                double waveAngle,
                double waveAngleImpactBetamax);

            static double Resistance(
                double relativeDensity,
                double thicknessTopLayer);

            static double IncrementDegradation(
                double referenceTimeDegradation,
                double incrementTime,
                double wavePeriodTm10);

            static double Degradation(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            static double ReferenceTimeDegradation(
                double referenceDegradation,
                double wavePeriodTm10);

            static double ReferenceDegradation(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double initialDamage);

            static double DurationInTimeStepFailure(
                double referenceTimeFailure,
                double referenceTimeDegradation);

            static double ReferenceTimeFailure(
                double referenceFailure,
                double wavePeriodTm10);

            static double ReferenceFailure(
                double resistance,
                double hydraulicLoad,
                double waveAngleImpact,
                double failureNumber);
    };
}

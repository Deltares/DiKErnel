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
            static double IncrementDamageOfNaturalStone(
                double hydraulicLoadOnNaturalStone,
                double resistanceOfNaturalStone,
                double incrementDegradationOfNaturalStone,
                double loadingOfRevetment,
                double waveAngleImpactOnNaturalStone);

            static double HydraulicLoadOnNaturalStone(
                double waveHeightHm0,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs,
                double surfSimilarityParameter);

            static double UpperLimitLoadingOfNaturalStone(
                double waterLevel,
                double waveHeightHm0,
                double upperLimitLoadingOfNaturalStoneAul,
                double upperLimitLoadingOfNaturalStoneBul,
                double upperLimitLoadingOfNaturalStoneCul,
                double depthMaximumWaveLoadNaturalStone,
                double surfSimilarityParameter);

            static double LowerLimitLoadingOfNaturalStone(
                double waterLevel,
                double waveHeightHm0,
                double lowerLimitLoadingOfNaturalStoneAll,
                double lowerLimitLoadingOfNaturalStoneBll,
                double lowerLimitLoadingOfNaturalStoneCll,
                double depthMaximumWaveLoadNaturalStone,
                double surfSimilarityParameter);

            static double DepthMaximumWaveLoadNaturalStone(
                double distanceMaximumWaveElevationNaturalStone,
                double normativeWidthOfWaveImpact,
                double slopeAngle);

            static double DistanceMaximumWaveElevationNaturalStone(
                double waveHeightHm0,
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax,
                double impactShallowWaterNaturalStone,
                double waveSteepnessDeepWater);

            static double ImpactShallowWaterNaturalStone();

            static double NormativeWidthOfWaveImpactNaturalStone(
                double waveHeightHm0,
                double normativeWidthOfWaveImpactNaturalStoneAwi,
                double normativeWidthOfWaveImpactNaturalStoneBwi,
                double surfSimilarityParameter);

            static double WaveAngleImpactOnNaturalStone(
                double waveAngle,
                double waveAngleImpactOnNaturalStoneBetamax);

            static double ResistanceOfNaturalStone(
                double relativeDensity,
                double thicknessTopLayer);

            static double IncrementDegradationOfNaturalStone(
                double wavePeriodTm10,
                double incrementOfTime,
                double referenceTimeDegradationOfNaturalStone);

            static double DegradationOfNaturalStone(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            static double ReferenceTimeDegradationOfNaturalStone(
                double wavePeriodTm10,
                double referenceDegradationOfNaturalStone);

            static double ReferenceDegradationOfNaturalStone(
                double initialDamage,
                double resistanceOfNaturalStone,
                double hydraulicLoadOnNaturalStone,
                double waveAngleImpactOnNaturalStone);

            static double DurationInTimeStepFailureNaturalStone(
                double referenceTimeFailureOfNaturalStone,
                double referenceTimeDegradationOfNaturalStone);

            static double ReferenceTimeFailureOfNaturalStone(
                double wavePeriodTm10,
                double referenceFailureOfNaturalStone);

            static double ReferenceFailureOfNaturalStone(
                double failureNumber,
                double resistanceOfNaturalStone,
                double hydraulicLoadOnNaturalStone,
                double waveAngleImpactOnNaturalStone);
    };
}

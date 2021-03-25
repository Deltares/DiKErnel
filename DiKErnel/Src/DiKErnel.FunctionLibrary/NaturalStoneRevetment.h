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
            static double CalculateDamageOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateIncrementDamageOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateHydraulicLoadOnNaturalStone(
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateUpperLimitLoadingOfNaturalStone(
                double waterLevel,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax,
                double normativeWidthOfWaveImpactNaturalStoneAwi,
                double normativeWidthOfWaveImpactNaturalStoneBwi,
                double upperLimitLoadingOfNaturalStoneAul,
                double upperLimitLoadingOfNaturalStoneBul,
                double upperLimitLoadingOfNaturalStoneCul);

            static double CalculateLowerLimitLoadingOfNaturalStone(
                double waterLevel,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax,
                double normativeWidthOfWaveImpactNaturalStoneAwi,
                double normativeWidthOfWaveImpactNaturalStoneBwi,
                double lowerLimitLoadingOfNaturalStoneAll,
                double lowerLimitLoadingOfNaturalStoneBll,
                double lowerLimitLoadingOfNaturalStoneCll);

            static double CalculateDepthMaximumWaveLoadNaturalStone(
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax,
                double normativeWidthOfWaveImpactNaturalStoneAwi,
                double normativeWidthOfWaveImpactNaturalStoneBwi);

            static double CalculateDistanceMaximumWaveElevationNaturalStone(
                double waveHeightHm0,
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax);

            static double CalculateImpactShallowWaterNaturalStone();

            static double CalculateNormativeWidthOfWaveImpactNaturalStone(
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double normativeWidthOfWaveImpactNaturalStoneAwi,
                double normativeWidthOfWaveImpactNaturalStoneBwi);

            static double CalculateResistanceOfNaturalStone(
                double relativeDensity,
                double thicknessTopLayer);

            static double CalculateIncrementDegradationOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateReferenceTimeDegradationOfNaturalStone(
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateDegradationOfNaturalStone(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            static double CalculateReferenceDegradationOfNaturalStone(
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateWaveAngleImpactOnNaturalStone(
                double waveAngle,
                double waveAngleImpactOnNaturalStoneBetamax);

            static double CalculateDurationInTimeStepFailureNaturalStone(
                double initialDamage,
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateReferenceTimeFailureOfNaturalStone(
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);

            static double CalculateReferenceFailureOfNaturalStone(
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                double tanA,
                double waveHeightHm0,
                double wavePeriodTm10,
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs);
    };
}

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
            static double IncrementDamage(
                double hydraulicLoad,
                double resistance,
                double incrementDegradation,
                double waveAngleImpact);

            static double HydraulicLoad(
                double surfSimilarityParameter,
                double waveHeightHm0,
                double hydraulicLoadA,
                double hydraulicLoadB,
                double hydraulicLoadC,
                double hydraulicLoadN);

            static double UpperLimitLoading(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0,
                double upperLimitLoadingAul,
                double upperLimitLoadingBul,
                double upperLimitLoadingCul);

            static double LowerLimitLoading(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0,
                double lowerLimitLoadingAll,
                double lowerLimitLoadingBll,
                double lowerLimitLoadingCll);

            static double DepthMaximumWaveLoad(
                double distanceMaximumWaveElevation,
                double normativeWidthWaveImpact,
                double slopeAngle);

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

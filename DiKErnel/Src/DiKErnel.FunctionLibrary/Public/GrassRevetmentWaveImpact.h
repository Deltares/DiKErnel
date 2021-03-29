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
     * \brief Class that holds all grass revetment wave impact specific calculation routines.
     */
    class GrassRevetmentWaveImpact
    {
        static double IncrementDamage(
            double incrementTime,
            double failureTime);

        static double TimeLine(
            double waveHeight,
            double failureTimeAgwi,
            double failureTimeBgwi,
            double failureTimeCgwi);

        static double WaveHeight(
            double minimumWaveHeight,
            double maximumWaveHeight,
            double waveAngleImpact,
            double waveHeightHm0);

        static double MinimumWaveHeight(
            double failureTimeAgwi,
            double failureTimeBgwi,
            double failureTimeCgwi,
            double minimumWaveHeightTemax);

        static double MaximumWaveHeight(
            double failureTimeAgwi,
            double failureTimeBgwi,
            double failureTimeCgwi,
            double minimumWaveHeightTemin);

        static double WaveAngleImpact(
            double waveAngle,
            double waveAngleImpactNwa,
            double waveAngleImpactQwa,
            double waveAngleImpactRwa);

        static double UpperLimitLoading(
            double waterLevel,
            double waveHeightHm0,
            double upperLimitLoadingAul);

        static double LowerLimitLoading(
            double waterLevel,
            double waveHeightHm0,
            double lowerLimitLoadingAll);

        static double FailureTime(
            double failureTime,
            double failureNumber,
            double initialDamage);
    };
}

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

#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a natural stone revetment location.
     */
    class NaturalStoneRevetmentTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param damage
             *        The damage.
             * \param timeOfFailure
             *        The time of failure.
             * \param loadingRevetment
             *        The loading revetment.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waveSteepnessDeepWater
             *        The wave steepness deep water.
             * \param upperLimitLoading
             *        The upper limit loading.
             * \param lowerLimitLoading
             *        The lower limit loading.
             * \param depthMaximumWaveLoad
             *        The depth maximum wave load.
             * \param distanceMaximumWaveElevation
             *        The distance maximum wave elevation.
             * \param normativeWidthOfWaveImpact
             *        The normative width of wave impact.
             * \param waveAngleImpact
             *        The wave angle impact.
             * \param hydraulicLoad
             *        The hydraulic load.
             * \param resistance
             *        The resistance.
             * \param referenceTimeDegradation
             *        The reference time degradation.
             * \param referenceDegradation
             *        The reference degradation.
             * \param incrementDamage
             *        The increment damage.
             */
            explicit NaturalStoneRevetmentTimeDependentOutput(
                double damage,
                std::unique_ptr<int> timeOfFailure,
                bool loadingRevetment,
                double surfSimilarityParameter,
                double waveSteepnessDeepWater,
                double upperLimitLoading,
                double lowerLimitLoading,
                double depthMaximumWaveLoad,
                double distanceMaximumWaveElevation,
                double normativeWidthOfWaveImpact,
                std::unique_ptr<double> hydraulicLoad,
                std::unique_ptr<double> waveAngleImpact,
                std::unique_ptr<double> resistance,
                std::unique_ptr<double> referenceTimeDegradation,
                std::unique_ptr<double> referenceDegradation,
                double incrementDamage);

        private:
            const bool _loadingRevetment;
            const double _surfSimilarityParameter;
            const double _waveSteepnessDeepWater;
            const double _upperLimitLoading;
            const double _lowerLimitLoading;
            const double _depthMaximumWaveLoad;
            const double _distanceMaximumWaveElevation;
            const double _normativeWidthOfWaveImpact;
            std::unique_ptr<double> _hydraulicLoad;
            std::unique_ptr<double> _waveAngleImpact;
            std::unique_ptr<double> _resistance;
            std::unique_ptr<double> _referenceTimeDegradation;
            std::unique_ptr<double> _referenceDegradation;
            const double _incrementDamage;
    };
}

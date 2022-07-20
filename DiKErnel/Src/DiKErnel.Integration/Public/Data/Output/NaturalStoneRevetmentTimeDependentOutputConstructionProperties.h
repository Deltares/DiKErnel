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

#include "TimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct natural stone revetment time dependent output.
     */
    class NaturalStoneRevetmentTimeDependentOutputConstructionProperties : public Core::TimeDependentOutputConstructionProperties
    {
        public:
            /*!
             * \brief The outer slope.
             */
            std::unique_ptr<double> _outerSlope = nullptr;

            /*!
             * \brief The slope upper level.
             */
            std::unique_ptr<double> _slopeUpperLevel = nullptr;

            /*!
             * \brief The slope upper position.
             */
            std::unique_ptr<double> _slopeUpperPosition = nullptr;

            /*!
             * \brief The slope lower level.
             */
            std::unique_ptr<double> _slopeLowerLevel = nullptr;

            /*!
             * \brief The slope lower position.
             */
            std::unique_ptr<double> _slopeLowerPosition = nullptr;

            /*!
             * \brief The loading revetment.
             */
            std::unique_ptr<bool> _loadingRevetment = nullptr;

            /*!
             * \brief The surf similarity parameter.
             */
            std::unique_ptr<double> _surfSimilarityParameter = nullptr;

            /*!
             * \brief The wave steepness deep water.
             */
            std::unique_ptr<double> _waveSteepnessDeepWater = nullptr;

            /*!
             * \brief The upper limit loading.
             */
            std::unique_ptr<double> _upperLimitLoading = nullptr;

            /*!
             * \brief The lower limit loading.
             */
            std::unique_ptr<double> _lowerLimitLoading = nullptr;

            /*!
             * \brief The depth maximum wave load.
             */
            std::unique_ptr<double> _depthMaximumWaveLoad = nullptr;

            /*!
             * \brief The distance maximum wave elevation.
             */
            std::unique_ptr<double> _distanceMaximumWaveElevation = nullptr;

            /*!
             * \brief The normative width of wave impact.
             */
            std::unique_ptr<double> _normativeWidthOfWaveImpact = nullptr;

            /*!
             * \brief The hydraulic load.
             */
            std::unique_ptr<double> _hydraulicLoad = nullptr;

            /*!
             * \brief The wave angle impact.
             */
            std::unique_ptr<double> _waveAngleImpact = nullptr;

            /*!
             * \brief The resistance.
             */
            std::unique_ptr<double> _resistance = nullptr;

            /*!
             * \brief The reference time degradation.
             */
            std::unique_ptr<double> _referenceTimeDegradation = nullptr;

            /*!
             * \brief The reference degradation.
             */
            std::unique_ptr<double> _referenceDegradation = nullptr;
    };
}

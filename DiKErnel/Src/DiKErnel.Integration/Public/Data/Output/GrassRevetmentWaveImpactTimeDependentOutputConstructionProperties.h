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
     * \brief Construction properties to construct grass revetment wave impact time dependent
     *        output.
     */
    class GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties : public Core::TimeDependentOutputConstructionProperties
    {
        public:
            /*!
             * \brief The loading revetment.
             */
            std::unique_ptr<bool> _loadingRevetment = nullptr;

            /*!
             * \brief The upper limit loading.
             */
            std::unique_ptr<double> _upperLimitLoading = nullptr;

            /*!
             * \brief The lower limit loading.
             */
            std::unique_ptr<double> _lowerLimitLoading = nullptr;

            /*!
             * \brief The minimum wave height.
             */
            std::unique_ptr<double> _minimumWaveHeight = nullptr;

            /*!
             * \brief The maximum wave height.
             */
            std::unique_ptr<double> _maximumWaveHeight = nullptr;

            /*!
             * \brief The wave angle impact.
             */
            std::unique_ptr<double> _waveAngleImpact = nullptr;

            /*!
             * \brief The wave height impact.
             */
            std::unique_ptr<double> _waveHeightImpact = nullptr;
    };
}

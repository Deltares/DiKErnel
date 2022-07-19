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
     * \brief Construction properties to construct asphalt revetment wave impact time dependent
     *        output.
     */
    class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties : public Core::TimeDependentOutputConstructionProperties
    {
        public:
            /*!
             * \brief The log failure tension.
             */
            std::unique_ptr<double> _logFailureTension = nullptr;

            /*!
             * \brief The maximum peak stress.
             */
            std::unique_ptr<double> _maximumPeakStress = nullptr;

            /*!
             * \brief The stiffness relation.
             */
            std::unique_ptr<double> _stiffnessRelation = nullptr;

            /*!
             * \brief The computational thickness.
             */
            std::unique_ptr<double> _computationalThickness = nullptr;

            /*!
             * \brief The equivalent elastic modulus.
             */
            std::unique_ptr<double> _equivalentElasticModulus = nullptr;
    };
}

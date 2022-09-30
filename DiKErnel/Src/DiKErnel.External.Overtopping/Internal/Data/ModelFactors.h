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

namespace DiKErnel::External::Overtopping
{
    /*!
     * \brief The model factors for the overtopping kernel.
     */
    struct ModelFactors
    {
        /*!
         * \brief Model factor for non-breaking waves.
         *        Unit = [-]
         */
        double _factorDeterminationQnFn{};

        /*!
         * \brief Model factor for breaking waves.
         *        Unit = [-]
         */
        double _factorDeterminationQbFb{};

        /*!
         * \brief Model factor describing the uncertainty of 2% run-up height.
         *        Unit = [-]
         */
        double _mz2{};

        /*!
         * \brief Model factor for shallow waves.
         *        Unit = [-]
         */
        double _fshallow{};

        /*!
         * \brief Model factor computed overtopping.
         *        Unit = [-]
         */
        double _computedOvertopping{};

        /*!
         * \brief Model factor critical overtopping.
         *        Unit = [-]
         */
        double _criticalOvertopping{};

        /*!
         * \brief Relaxation factor iteration procedure wave run-up.
         *        Unit = [-]
         */
        double _relaxationfactor{};

        /*!
         * \brief Reduction factor foreshore.
         *        Unit = [-]
         */
        double _reductionFactorForeshore{};
    };
}

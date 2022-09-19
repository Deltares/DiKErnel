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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for grass revetment cumulative overload
     *        calculations.
     */
    class GrassRevetmentCumulativeOverloadDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the increased load transition alpha M.
             * \return The default value of the increased load transition alpha M.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetIncreasedLoadTransitionAlphaM();

            /*!
             * \brief Gets the default value of the reduced strength transition alpha S.
             * \return The default value of the reduced strength transition alpha S.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetReducedStrengthTransitionAlphaS();

            /*!
             * \brief Gets the default value of the Ctm coefficient.
             * \return The default value of the Ctm coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetAverageNumberOfWavesCtm();
    };
}

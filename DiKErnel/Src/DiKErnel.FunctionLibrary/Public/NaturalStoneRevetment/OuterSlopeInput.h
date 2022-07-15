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

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Input object for an outer slope calculation.
     */
    struct OuterSlopeInput
    {
        /*!
         * \brief The outer toe height.
         *        Unit = [m]
         */
        double _outerToeHeight;

        /*!
         * \brief The outer crest height.
         *        Unit = [m]
         */
        double _outerCrestHeight;

        /*!
         * \brief The notch outer berm position.
         *        Unit = [m]
         */
        double _notchOuterBermPosition;

        /*!
         * \brief The notch outer berm height.
         *        Unit = [m]
         */
        double _notchOuterBermHeight;

        /*!
         * \brief The crest outer berm position.
         *        Unit = [m]
         */
        double _crestOuterBermPosition;

        /*!
         * \brief The crest outer berm height.
         *        Unit = [m]
         */
        double _crestOuterBermHeight;

        /*!
         * \brief The slope lower position.
         *        Unit = [m]
         */
        double _slopeLowerPosition;

        /*!
         * \brief The slope lower level.
         *        Unit = [m]
         */
        double _slopeLowerLevel;

        /*!
         * \brief The slope upper position.
         *        Unit = [m]
         */
        double _slopeUpperPosition;

        /*!
         * \brief The slope upper level.
         *        Unit = [m]
         */
        double _slopeUpperLevel;
    };
}

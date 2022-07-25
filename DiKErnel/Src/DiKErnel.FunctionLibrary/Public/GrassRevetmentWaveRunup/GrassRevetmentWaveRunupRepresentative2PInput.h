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
     * \brief Input for a grass revetment wave run-up representative 2P calculation.
     */
    struct GrassRevetmentWaveRunupRepresentative2PInput
    {
        /*!
         * \brief The surf similarity parameter.
         *        Unit = [-]
         */
        double _surfSimilarityParameter{};

        /*!
         * \brief The wave impact with respect to the wave angle.
         *        Unit = [-]
         */
        double _waveAngleImpact{};

        /*!
         * \brief The wave height.
         *        Unit = [m]
         */
        double _waveHeightHm0{};

        /*!
         * \brief The Gammab value.
         *        Unit = [-]
         */
        double _representativeWaveRunup2PGammab{};

        /*!
         * \brief The Gammaf value.
         *        Unit = [-]
         */
        double _representativeWaveRunup2PGammaf{};

        /*!
         * \brief The Aru coefficient.
         *        Unit = [-]
         */
        double _representativeWaveRunup2PAru{};

        /*!
         * \brief The Bru coefficient.
         *        Unit = [-]
         */
        double _representativeWaveRunup2PBru{};

        /*!
         * \brief The Cru coefficient.
         *        Unit = [-]
         */
        double _representativeWaveRunup2PCru{};
    };
}

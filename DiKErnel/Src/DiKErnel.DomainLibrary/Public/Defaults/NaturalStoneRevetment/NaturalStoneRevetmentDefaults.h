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
     * \brief Class that contains default values for all natural stone revetments.
     */
    class NaturalStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the Aus coefficient.
             * \return The default value of the Aus coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetSlopeUpperLevelAus();

            /*!
             * \brief Gets the default value of the Als coefficient.
             * \return The default value of the Als coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetSlopeLowerLevelAls();

            /*!
             * \brief Gets the default value of the Aul coefficient.
             * \return The default value of the Aul coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetUpperLimitLoadingAul();

            /*!
             * \brief Gets the default value of the Bul coefficient.
             * \return The default value of the Bul coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetUpperLimitLoadingBul();

            /*!
             * \brief Gets the default value of the Cul coefficient.
             * \return The default value of the Cul coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetUpperLimitLoadingCul();

            /*!
             * \brief Gets the default value of the All coefficient.
             * \return The default value of the All coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetLowerLimitLoadingAll();

            /*!
             * \brief Gets the default value of the Bll coefficient.
             * \return The default value of the Bll coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetLowerLimitLoadingBll();

            /*!
             * \brief Gets the default value of the Cll coefficient.
             * \return The default value of the Cll coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetLowerLimitLoadingCll();

            /*!
             * \brief Gets the default value of the Asmax coefficient.
             * \return The default value of the Asmax coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetDistanceMaximumWaveElevationAsmax();

            /*!
             * \brief Gets the default value of the Bsmax coefficient.
             * \return The default value of the Bsmax coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetDistanceMaximumWaveElevationBsmax();

            /*!
             * \brief Gets the default value of the Awi coefficient.
             * \return The default value of the Awi coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetNormativeWidthOfWaveImpactAwi();

            /*!
             * \brief Gets the default value of the Bwi coefficient.
             * \return The default value of the Bwi coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double GetNormativeWidthOfWaveImpactBwi();

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [deg]
             */
            [[nodiscard]]
            static double GetWaveAngleImpactBetamax();
    };
}

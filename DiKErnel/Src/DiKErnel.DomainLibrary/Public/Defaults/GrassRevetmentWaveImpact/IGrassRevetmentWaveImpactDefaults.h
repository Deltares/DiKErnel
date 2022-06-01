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
     * \brief Interface that contains default value definitions for grass revetment wave impact.
     */
    class IGrassRevetmentWaveImpactDefaults
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~IGrassRevetmentWaveImpactDefaults() = default;

            /*!
             * \brief Gets the default value of the Agwi coefficient.
             * \return The default value of the Agwi coefficient.
             *         Unit = [m]
             */
            [[nodiscard]]
            virtual double GetTimeLineAgwi() const = 0;

            /*!
             * \brief Gets the default value of the Bgwi coefficient.
             * \return The default value of the Bgwi coefficient.
             *         Unit = [s^-1]
             */
            [[nodiscard]]
            virtual double GetTimeLineBgwi() const = 0;

            /*!
             * \brief Gets the default value of the Cgwi coefficient.
             * \return The default value of the Cgwi coefficient.
             *         Unit = [m]
             */
            [[nodiscard]]
            virtual double GetTimeLineCgwi() const = 0;

            /*!
             * \brief Gets the default value of the Temax coefficient.
             * \return The default value of the Temax coefficient.
             *         Unit = [s]
             */
            [[nodiscard]]
            virtual double GetMinimumWaveHeightTemax() const = 0;

            /*!
             * \brief Gets the default value of the Temin coefficient.
             * \return The default value of the Temin coefficient.
             *         Unit = [s]
             */
            [[nodiscard]]
            virtual double GetMaximumWaveHeightTemin() const = 0;

            /*!
             * \brief Gets the default value of the Nwa coefficient.
             * \return The default value of the Nwa coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetWaveAngleImpactNwa() const = 0;

            /*!
             * \brief Gets the default value of the Qwa coefficient.
             * \return The default value of the Qwa coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetWaveAngleImpactQwa() const = 0;

            /*!
             * \brief Gets the default value of the Rwa coefficient.
             * \return The default value of the Rwa coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetWaveAngleImpactRwa() const = 0;

            /*!
             * \brief Gets the default value of the Aul coefficient.
             * \return The default value of the Aul coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetUpperLimitLoadingAul() const = 0;

            /*!
             * \brief Gets the default value of the All coefficient.
             * \return The default value of the All coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetLowerLimitLoadingAll() const = 0;
    };
}

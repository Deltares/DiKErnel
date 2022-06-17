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
     * \brief Interface that contains default value definitions for natural stone revetment top
     *        layers.
     */
    class INaturalStoneRevetmentTopLayerDefaults
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~INaturalStoneRevetmentTopLayerDefaults() = default;

            /*!
             * \brief Gets the default value of the Xib coefficient.
             * \return The default value of the Xib coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadXib() const = 0;

            /*!
             * \brief Gets the default value of the Ap coefficient.
             * \return The default value of the Ap coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadAp() const = 0;

            /*!
             * \brief Gets the default value of the Bp coefficient.
             * \return The default value of the Bp coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadBp() const = 0;

            /*!
             * \brief Gets the default value of the Cp coefficient.
             * \return The default value of the Cp coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadCp() const = 0;

            /*!
             * \brief Gets the default value of the Np coefficient.
             * \return The default value of the Np coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadNp() const = 0;

            /*!
             * \brief Gets the default value of the As coefficient.
             * \return The default value of the As coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadAs() const = 0;

            /*!
             * \brief Gets the default value of the Bs coefficient.
             * \return The default value of the Bs coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadBs() const = 0;

            /*!
             * \brief Gets the default value of the Cs coefficient.
             * \return The default value of the Cs coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadCs() const = 0;

            /*!
             * \brief Gets the default value of the Ns coefficient.
             * \return The default value of the Ns coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            virtual double GetHydraulicLoadNs() const = 0;
    };
}

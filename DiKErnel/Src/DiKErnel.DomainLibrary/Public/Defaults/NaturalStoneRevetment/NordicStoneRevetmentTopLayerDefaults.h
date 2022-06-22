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

#include "INaturalStoneRevetmentTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for natural stone revetments with a nordic stone
     *        top layer.
     */
    class NordicStoneRevetmentTopLayerDefaults : public INaturalStoneRevetmentTopLayerDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the Xib coefficient.
             * \return The default value of the Xib coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadXib() const override;

            /*!
             * \brief Gets the default value of the Ap coefficient.
             * \return The default value of the Ap coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadAp() const override;

            /*!
             * \brief Gets the default value of the Bp coefficient.
             * \return The default value of the Bp coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadBp() const override;

            /*!
             * \brief Gets the default value of the Cp coefficient.
             * \return The default value of the Cp coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadCp() const override;

            /*!
             * \brief Gets the default value of the Np coefficient.
             * \return The default value of the Np coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadNp() const override;

            /*!
             * \brief Gets the default value of the As coefficient.
             * \return The default value of the As coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadAs() const override;

            /*!
             * \brief Gets the default value of the Bs coefficient.
             * \return The default value of the Bs coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadBs() const override;

            /*!
             * \brief Gets the default value of the Cs coefficient.
             * \return The default value of the Cs coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadCs() const override;

            /*!
             * \brief Gets the default value of the Ns coefficient.
             * \return The default value of the Ns coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetHydraulicLoadNs() const override;
    };
}

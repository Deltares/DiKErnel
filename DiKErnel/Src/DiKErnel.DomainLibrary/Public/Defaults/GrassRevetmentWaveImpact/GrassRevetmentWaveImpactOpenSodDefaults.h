// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "IGrassRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for grass revetment wave impact with open sod.
     */
    class GrassRevetmentWaveImpactOpenSodDefaults : public IGrassRevetmentWaveImpactDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the Agwi coefficient.
             * \return The default value of the Agwi coefficient.
             *         Unit = [m]
             */
            double GetTimeLineAgwi() const override;

            /*!
             * \brief Gets the default value of the Bgwi coefficient.
             * \return The default value of the Bgwi coefficient.
             *         Unit = [s^-1]
             */
            double GetTimeLineBgwi() const override;

            /*!
             * \brief Gets the default value of the Cgwi coefficient.
             * \return The default value of the Cgwi coefficient.
             *         Unit = [m]
             */
            double GetTimeLineCgwi() const override;

            /*!
             * \brief Gets the default value of the Temax coefficient.
             * \return The default value of the Temax coefficient.
             *         Unit = [s]
             */
            double GetMinimumWaveHeightTemax() const override;

            /*!
             * \brief Gets the default value of the Temin coefficient.
             * \return The default value of the Temin coefficient.
             *         Unit = [s]
             */
            double GetMaximumWaveHeightTemin() const override;

            /*!
             * \brief Gets the default value of the Nwa coefficient.
             * \return The default value of the Nwa coefficient.
             *         Unit = [-]
             */
            double GetWaveAngleImpactNwa() const override;

            /*!
             * \brief Gets the default value of the Qwa coefficient.
             * \return The default value of the Qwa coefficient.
             *         Unit = [-]
             */
            double GetWaveAngleImpactQwa() const override;

            /*!
             * \brief Gets the default value of the Rwa coefficient.
             * \return The default value of the Rwa coefficient.
             *         Unit = [-]
             */
            double GetWaveAngleImpactRwa() const override;

            /*!
             * \brief Gets the default value of the Aul coefficient.
             * \return The default value of the Aul coefficient.
             *         Unit = [-]
             */
            double GetUpperLimitLoadingAul() const override;

            /*!
             * \brief Gets the default value of the All coefficient.
             * \return The default value of the All coefficient.
             *         Unit = [-]
             */
            double GetLowerLimitLoadingAll() const override;
    };
}

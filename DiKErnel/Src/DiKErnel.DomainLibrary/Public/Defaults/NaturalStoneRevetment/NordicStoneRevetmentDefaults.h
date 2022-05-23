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

#include "INaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for nordic stone revetments.
     */
    class NordicStoneRevetmentDefaults : public INaturalStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the Xib coefficient.
             * \return The default value of the Xib coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadXib() const override;

            /*!
             * \brief Gets the default value of the Ap coefficient.
             * \return The default value of the Ap coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadAp() const override;

            /*!
             * \brief Gets the default value of the Bp coefficient.
             * \return The default value of the Bp coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadBp() const override;

            /*!
             * \brief Gets the default value of the Cp coefficient.
             * \return The default value of the Cp coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadCp() const override;

            /*!
             * \brief Gets the default value of the Np coefficient.
             * \return The default value of the Np coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadNp() const override;

            /*!
             * \brief Gets the default value of the As coefficient.
             * \return The default value of the As coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadAs() const override;

            /*!
             * \brief Gets the default value of the Bs coefficient.
             * \return The default value of the Bs coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadBs() const override;

            /*!
             * \brief Gets the default value of the Cs coefficient.
             * \return The default value of the Cs coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadCs() const override;

            /*!
             * \brief Gets the default value of the Ns coefficient.
             * \return The default value of the Ns coefficient.
             *         Unit = [-]
             */
            double GetHydraulicLoadNs() const override;

            /*!
             * \brief Gets the default value of the Aus coefficient.
             * \return The default value of the Aus coefficient.
             *         Unit = [-]
             */
            double GetSlopeUpperLevelAus() const override;

            /*!
             * \brief Gets the default value of the Als coefficient.
             * \return The default value of the Als coefficient.
             *         Unit = [-]
             */
            double GetSlopeLowerLevelAls() const override;

            /*!
             * \brief Gets the default value of the Aul coefficient.
             * \return The default value of the Aul coefficient.
             *         Unit = [-]
             */
            double GetUpperLimitLoadingAul() const override;

            /*!
             * \brief Gets the default value of the Bul coefficient.
             * \return The default value of the Bul coefficient.
             *         Unit = [-]
             */
            double GetUpperLimitLoadingBul() const override;

            /*!
             * \brief Gets the default value of the Cul coefficient.
             * \return The default value of the Cul coefficient.
             *         Unit = [-]
             */
            double GetUpperLimitLoadingCul() const override;

            /*!
             * \brief Gets the default value of the All coefficient.
             * \return The default value of the All coefficient.
             *         Unit = [-]
             */
            double GetLowerLimitLoadingAll() const override;

            /*!
             * \brief Gets the default value of the Bll coefficient.
             * \return The default value of the Bll coefficient.
             *         Unit = [-]
             */
            double GetLowerLimitLoadingBll() const override;

            /*!
             * \brief Gets the default value of the Cll coefficient.
             * \return The default value of the Cll coefficient.
             *         Unit = [-]
             */
            double GetLowerLimitLoadingCll() const override;

            /*!
             * \brief Gets the default value of the Asmax coefficient.
             * \return The default value of the Asmax coefficient.
             *         Unit = [-]
             */
            double GetDistanceMaximumWaveElevationAsmax() const override;

            /*!
             * \brief Gets the default value of the Bsmax coefficient.
             * \return The default value of the Bsmax coefficient.
             *         Unit = [-]
             */
            double GetDistanceMaximumWaveElevationBsmax() const override;

            /*!
             * \brief Gets the default value of the Awi coefficient.
             * \return The default value of the Awi coefficient.
             *         Unit = [-]
             */
            double GetNormativeWidthOfWaveImpactAwi() const override;

            /*!
             * \brief Gets the default value of the Bwi coefficient.
             * \return The default value of the Bwi coefficient.
             *         Unit = [-]
             */
            double GetNormativeWidthOfWaveImpactBwi() const override;

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [deg]
             */
            double GetWaveAngleImpactBetamax() const override;
    };
}

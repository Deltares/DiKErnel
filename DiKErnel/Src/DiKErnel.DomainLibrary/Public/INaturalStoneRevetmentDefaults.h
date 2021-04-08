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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Interface that defines default values for natural stone revetments.
     */
    class INaturalStoneRevetmentDefaults
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~INaturalStoneRevetmentDefaults() = default;

            /*!
             * \brief Gets the default value of the Xib coefficient.
             * \return The default value of the Xib coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadXib() const = 0;

            /*!
             * \brief Gets the default value of the Ap coefficient.
             * \return The default value of the Ap coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadAp() const = 0;

            /*!
             * \brief Gets the default value of the Bp coefficient.
             * \return The default value of the Bp coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadBp() const = 0;

            /*!
             * \brief Gets the default value of the Cp coefficient.
             * \return The default value of the Cp coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadCp() const = 0;

            /*!
             * \brief Gets the default value of the Np coefficient.
             * \return The default value of the Np coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadNp() const = 0;

            /*!
             * \brief Gets the default value of the As coefficient.
             * \return The default value of the As coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadAs() const = 0;

            /*!
             * \brief Gets the default value of the Bs coefficient.
             * \return The default value of the Bs coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadBs() const = 0;

            /*!
             * \brief Gets the default value of the Cs coefficient.
             * \return The default value of the Cs coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadCs() const = 0;

            /*!
             * \brief Gets the default value of the Ns coefficient.
             * \return The default value of the Ns coefficient.
             *         Unit = [-]
             */
            virtual double GetHydraulicLoadNs() const = 0;

            /*!
             * \brief Gets the default value of the Aul coefficient.
             * \return The default value of the Aul coefficient.
             *         Unit = [-]
             */
            virtual double GetUpperLimitLoadingAul() const = 0;

            /*!
             * \brief Gets the default value of the Bul coefficient.
             * \return The default value of the Bul coefficient.
             *         Unit = [-]
             */
            virtual double GetUpperLimitLoadingBul() const = 0;

            /*!
             * \brief Gets the default value of the Cul coefficient.
             * \return The default value of the Cul coefficient.
             *         Unit = [-]
             */
            virtual double GetUpperLimitLoadingCul() const = 0;

            /*!
             * \brief Gets the default value of the All coefficient.
             * \return The default value of the All coefficient.
             *         Unit = [-]
             */
            virtual double GetLowerLimitLoadingAll() const = 0;

            /*!
             * \brief Gets the default value of the Bll coefficient.
             * \return The default value of the Bll coefficient.
             *         Unit = [-]
             */
            virtual double GetLowerLimitLoadingBll() const = 0;

            /*!
             * \brief Gets the default value of the Cll coefficient.
             * \return The default value of the Cll coefficient.
             *         Unit = [-]
             */
            virtual double GetLowerLimitLoadingCll() const = 0;

            /*!
             * \brief Gets the default value of the Asmax coefficient.
             * \return The default value of the Asmax coefficient.
             *         Unit = [-]
             */
            virtual double GetDistanceMaximumWaveElevationAsmax() const = 0;

            /*!
             * \brief Gets the default value of the Bsmax coefficient.
             * \return The default value of the Bsmax coefficient.
             *         Unit = [-]
             */
            virtual double GetDistanceMaximumWaveElevationBsmax() const = 0;

            /*!
             * \brief Gets the default value of the Awi coefficient.
             * \return The default value of the Awi coefficient.
             *         Unit = [-]
             */
            virtual double GetNormativeWidthOfWaveImpactAwi() const = 0;

            /*!
             * \brief Gets the default value of the Bwi coefficient.
             * \return The default value of the Bwi coefficient.
             *         Unit = [-]
             */
            virtual double GetNormativeWidthOfWaveImpactBwi() const = 0;

            /*!
             * \brief Gets the default value of the Betamax coefficient.
             * \return The default value of the Betamax coefficient.
             *         Unit = [deg]
             */
            virtual double GetWaveAngleImpactBetamax() const = 0;
    };
}

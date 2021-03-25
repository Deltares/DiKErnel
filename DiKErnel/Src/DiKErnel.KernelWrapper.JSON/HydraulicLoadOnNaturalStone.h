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

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for hydraulic load on natural stone.
     */
    class HydraulicLoadOnNaturalStone
    {
        public:
            /*! 
             * \brief Creates a new instance.
             * \param hydraulicLoadOnNaturalStoneXib
             *        The hydraulic load on natural stone Xib.
             * \param hydraulicLoadOnNaturalStoneAp
             *        The hydraulic load on natural stone Ap.
             * \param hydraulicLoadOnNaturalStoneBp
             *        The hydraulic load on natural stone Bp.
             * \param hydraulicLoadOnNaturalStoneCp
             *        The hydraulic load on natural stone Cp.
             * \param hydraulicLoadOnNaturalStoneNp
             *        The hydraulic load on natural stone Np.
             * \param hydraulicLoadOnNaturalStoneAs
             *        The hydraulic load on natural stone As.
             * \param hydraulicLoadOnNaturalStoneBs
             *        The hydraulic load on natural stone Bs.
             * \param hydraulicLoadOnNaturalStoneCs
             *        The hydraulic load on natural stone Cs.
             * \param hydraulicLoadOnNaturalStoneNs
             *        The hydraulic load on natural stone Ns.
             */
            explicit HydraulicLoadOnNaturalStone(
                double hydraulicLoadOnNaturalStoneXib,
                double hydraulicLoadOnNaturalStoneAp,
                double hydraulicLoadOnNaturalStoneBp,
                double hydraulicLoadOnNaturalStoneCp,
                double hydraulicLoadOnNaturalStoneNp,
                double hydraulicLoadOnNaturalStoneAs,
                double hydraulicLoadOnNaturalStoneBs,
                double hydraulicLoadOnNaturalStoneCs,
                double hydraulicLoadOnNaturalStoneNs
            );

            /*!
             * \brief Gets the hydraulic load on natural stone XIb.
             * \return The hydraulic load on natural stone XIb.
             */
            double GetHydraulicLoadOnNaturalStoneXib() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Ap.
             * \return The hydraulic load on natural stone Ap.
             */
            double GetHydraulicLoadOnNaturalStoneAp() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Bp.
             * \return The hydraulic load on natural stone Bp.
             */
            double GetHydraulicLoadOnNaturalStoneBp() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Cp.
             * \return The hydraulic load on natural stone Cp.
             */
            double GetHydraulicLoadOnNaturalStoneCp() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Np.
             * \return The hydraulic load on natural stone Np.
             */
            double GetHydraulicLoadOnNaturalStoneNp() const;

            /*!
             * \brief Gets the hydraulic load on natural stone As.
             * \return The hydraulic load on natural stone As.
             */
            double GetHydraulicLoadOnNaturalStoneAs() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Bs.
             * \return The hydraulic load on natural stone Bs.
             */
            double GetHydraulicLoadOnNaturalStoneBs() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Cs.
             * \return The hydraulic load on natural stone Cs.
             */
            double GetHydraulicLoadOnNaturalStoneCs() const;

            /*!
             * \brief Gets the hydraulic load on natural stone Ns.
             * \return The hydraulic load on natural stone Ns.
             */
            double GetHydraulicLoadOnNaturalStoneNs() const;

        private:
            double _hydraulicLoadOnNaturalStoneXib;
            double _hydraulicLoadOnNaturalStoneAp;
            double _hydraulicLoadOnNaturalStoneBp;
            double _hydraulicLoadOnNaturalStoneCp;
            double _hydraulicLoadOnNaturalStoneNp;
            double _hydraulicLoadOnNaturalStoneAs;
            double _hydraulicLoadOnNaturalStoneBs;
            double _hydraulicLoadOnNaturalStoneCs;
            double _hydraulicLoadOnNaturalStoneNs;
    };
}

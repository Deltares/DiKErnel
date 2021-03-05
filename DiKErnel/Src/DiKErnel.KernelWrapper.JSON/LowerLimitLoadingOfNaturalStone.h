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
     * \brief Container for lower limit loading of natural stone data.
     */
    class LowerLimitLoadingOfNaturalStone
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param lowerLimitLoadingOfNaturalStoneAll
             *        The lower limit loading of natural stone all.
             * \param lowerLimitLoadingOfNaturalStoneBll
             *        The lower limit loading of natural stone bll.
             * \param lowerLimitLoadingOfNaturalStoneCll
             *        The lower limit loading of natural stone cll.
             */
            explicit LowerLimitLoadingOfNaturalStone(
                double lowerLimitLoadingOfNaturalStoneAll,
                double lowerLimitLoadingOfNaturalStoneBll,
                double lowerLimitLoadingOfNaturalStoneCll);

            /*!
             * \brief Gets the lower limit loading of natural stone all.
             * \return The lower limit loading of natural stone all.
             */
            double GetLowerLimitLoadingOfNaturalStoneAll() const;

            /*!
             * \brief Gets the lower limit loading of natural stone bll.
             * \return The lower limit loading of natural stone bll.
             */
            double GetLowerLimitLoadingOfNaturalStoneBll() const;

            /*!
             * \brief Gets the lower limit loading of natural stone cll.
             * \return The lower limit loading of natural stone cll.
             */
            double GetLowerLimitLoadingOfNaturalStoneCll() const;

        private:
            double _lowerLimitLoadingOfNaturalStoneAll;
            double _lowerLimitLoadingOfNaturalStoneBll;
            double _lowerLimitLoadingOfNaturalStoneCll;
    };
}

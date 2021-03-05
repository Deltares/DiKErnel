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
     * \brief Container for calculation method data.
     */
    class DistanceMaximumWaveElevationNaturalStone
    {
        public:
            /*! 
             * \brief Creates a new instance.
             * \param distanceMaximumWaveElevationNaturalStoneAsmax
             *        The distance maximum wave elevation natural stone as max.
             * \param distanceMaximumWaveElevationNaturalStoneBsmax
             *        The distance maximum wave elevation natural stone bs max.
             */
            explicit DistanceMaximumWaveElevationNaturalStone(
                double distanceMaximumWaveElevationNaturalStoneAsmax,
                double distanceMaximumWaveElevationNaturalStoneBsmax
            );

            /*!
             * \brief Gets the distance maximum wave elevation natural stone as max.
             * \return The distance maximum wave elevation natural stone as max.
             */
            double GetDistanceMaximumWaveElevationNaturalStoneAsmax() const;

            /*!
             * \brief Gets the distance maximum wave elevation natural stone bs max.
             * \return The distance maximum wave elevation natural stone bs max.
             */
            double GetDistanceMaximumWaveElevationNaturalStoneBsmax() const;

        private:
            double _distanceMaximumWaveElevationNaturalStoneAsmax;
            double _distanceMaximumWaveElevationNaturalStoneBsmax;
    };
}

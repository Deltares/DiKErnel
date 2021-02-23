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

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing all time step that is needed to perform a calculation.
     */
    class TimeDependentData
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param beginTime
             *        The begin time.
             * \param endTime
             *        The end time.
             * \param waveHeightHm0
             *        The wave height.
             * \param wavePeriodTm10
             *        The wave period.
             * \param waveAngle
             *        The wave angle.
             * \exception InvalidCalculationDataException
             *            Thrown when endTime is equal to or larger than beginTime.
             */
            explicit TimeDependentData(
                int beginTime,
                int endTime,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle);

            /*!
             * \brief Gets the begin time.
             * \return The begin time.
            */
            int GetBeginTime() const;

            /*!
             * \brief Gets the end time.
             * \return The end time.
             */
            int GetEndTime() const;

            /*!
             * \brief Gets the wave height.
             * \return The wave height.
             */
            double GetWaveHeightHm0() const;

            /*!
             * \brief Gets the wave period.
             * \return The wave period.
             */
            double GetWavePeriodTm10() const;

            /*!
             * \brief Gets the wave angle.
             * \return The wave angle.
             */
            double GetWaveAngle() const;

        private:
            int beginTime;
            int endTime;
            double waveHeightHm0;
            double wavePeriodTm10;
            double waveAngle;
    };
}

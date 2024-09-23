// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.FunctionLibrary
{
    /// <summary>
    /// Class that holds generic revetment calculation routines.
    /// </summary>
    public static class RevetmentFunctions
    {
        /// <summary>
        /// Calculates the increment of time.
        /// </summary>
        /// <param name="beginTime">The begin time [s].</param>
        /// <param name="endTime">The end time [s].</param>
        /// <returns>The increment of time [s].</returns>
        public static double IncrementTime(double beginTime, double endTime)
        {
            return endTime - beginTime;
        }

        /// <summary>
        /// Calculates the average number of waves.
        /// </summary>
        /// <param name="incrementTime">The increment of time [s].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <param name="averageNumberOfWavesCtm">The Ctm coefficient [-].</param>
        /// <returns>The average number of waves [-].</returns>
        public static double AverageNumberOfWaves(double incrementTime, double wavePeriodTm10, double averageNumberOfWavesCtm)
        {
            return incrementTime / (averageNumberOfWavesCtm * wavePeriodTm10);
        }

        /// <summary>
        /// Calculates the damage.
        /// </summary>
        /// <param name="incrementDamage">The increment of damage [-].</param>
        /// <param name="initialDamage">The initial damage [-].</param>
        /// <returns>The damage [-].</returns>
        public static double Damage(double incrementDamage, double initialDamage)
        {
            return initialDamage + incrementDamage;
        }
    }
}
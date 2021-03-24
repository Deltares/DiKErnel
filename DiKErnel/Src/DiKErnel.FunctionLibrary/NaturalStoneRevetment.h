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

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all natural stone revetment specific calculation routines.
     */
    class NaturalStoneRevetment
    {
        public:
            static double CalculateDamageOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double wavePeriodTm10);

            static double CalculateIncrementDamageOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double wavePeriodTm10);

            static double CalculateHydraulicLoadOnNaturalStone();

            static double CalculateResistanceOfNaturalStone(
                double relativeDensity,
                double thicknessTopLayer);

            static double CalculateIncrementDegradationOfNaturalStone(
                double startTime,
                double endTime,
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double wavePeriodTm10);

            static double CalculateReferenceTimeDegradationOfNaturalStone(
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer,
                double wavePeriodTm10);

            static double CalculateDegradationOfNaturalStone(
                double referenceTimeDegradation,
                double wavePeriodTm10);

            static double CalculateReferenceDegradationOfNaturalStone(
                double initialDamage,
                double relativeDensity,
                double thicknessTopLayer);

            static double CalculateWaveAngleImpactOnNaturalStone();
    };
}

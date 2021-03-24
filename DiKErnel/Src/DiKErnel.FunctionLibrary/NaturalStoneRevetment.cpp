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

#include "NaturalStoneRevetment.h"

#include "Revetment.h"

namespace DiKErnel::FunctionLibrary
{
    double NaturalStoneRevetment::CalculateDamageOfNaturalStone(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        const auto initialDamage = 0.0;

        return initialDamage + CalculateIncrementDamageOfNaturalStone(relativeDensity, thicknessTopLayer);
    }

    double NaturalStoneRevetment::CalculateIncrementDamageOfNaturalStone(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        const auto hydraulicLoadOnNaturalStone = CalculateHydraulicLoadOnNaturalStone();
        const auto resistanceOfNaturalStone = CalculateResistanceOfNaturalStone(relativeDensity, thicknessTopLayer);
        const auto incrementDegradationOfNaturalStone = CalculateIncrementDegradationOfNaturalStone();
        const auto loadingOfRevetment = Revetment::CalculateLoadingOfRevetment();
        const auto waveAngleImpactOnNaturalStone = CalculateWaveAngleImpactOnNaturalStone();

        return hydraulicLoadOnNaturalStone / resistanceOfNaturalStone * incrementDegradationOfNaturalStone * loadingOfRevetment
                * waveAngleImpactOnNaturalStone;
    }

    double NaturalStoneRevetment::CalculateHydraulicLoadOnNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::CalculateResistanceOfNaturalStone(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::CalculateIncrementDegradationOfNaturalStone()
    {
        return 1.0;
    }

    double NaturalStoneRevetment::CalculateWaveAngleImpactOnNaturalStone()
    {
        return 1.0;
    }
}

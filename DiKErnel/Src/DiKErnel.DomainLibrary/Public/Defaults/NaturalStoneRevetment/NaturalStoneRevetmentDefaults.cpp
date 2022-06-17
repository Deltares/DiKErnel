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

#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus()
    {
        return 0.05;
    }

    double NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls()
    {
        return 1.5;
    }

    double NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul()
    {
        return 0.1;
    }

    double NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul()
    {
        return 0.6;
    }

    double NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul()
    {
        return 4;
    }

    double NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll()
    {
        return 0.1;
    }

    double NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll()
    {
        return 0.2;
    }

    double NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll()
    {
        return 4;
    }

    double NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax()
    {
        return 0.42;
    }

    double NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax()
    {
        return 0.9;
    }

    double NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi()
    {
        return 0.96;
    }

    double NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi()
    {
        return 0.11;
    }

    double NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax()
    {
        return 78;
    }
}

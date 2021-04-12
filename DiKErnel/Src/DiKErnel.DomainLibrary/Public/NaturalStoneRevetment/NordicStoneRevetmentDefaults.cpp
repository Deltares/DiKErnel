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

#include "NordicStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double NordicStoneRevetmentDefaults::GetHydraulicLoadXib() const
    {
        return 2.9;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadAp() const
    {
        return 4;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadBp() const
    {
        return 0;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadCp() const
    {
        return 0;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadNp() const
    {
        return -0.9;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadAs() const
    {
        return 0.8;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadBs() const
    {
        return 0;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadCs() const
    {
        return 0;
    }

    double NordicStoneRevetmentDefaults::GetHydraulicLoadNs() const
    {
        return 0.6;
    }

    double NordicStoneRevetmentDefaults::GetUpperLimitLoadingAul() const
    {
        return 0.1;
    }

    double NordicStoneRevetmentDefaults::GetUpperLimitLoadingBul() const
    {
        return 0.6;
    }

    double NordicStoneRevetmentDefaults::GetUpperLimitLoadingCul() const
    {
        return 4;
    }

    double NordicStoneRevetmentDefaults::GetLowerLimitLoadingAll() const
    {
        return 0.1;
    }

    double NordicStoneRevetmentDefaults::GetLowerLimitLoadingBll() const
    {
        return 0.2;
    }

    double NordicStoneRevetmentDefaults::GetLowerLimitLoadingCll() const
    {
        return 4;
    }

    double NordicStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax() const
    {
        return 0.42;
    }

    double NordicStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax() const
    {
        return 0.9;
    }

    double NordicStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi() const
    {
        return 0.96;
    }

    double NordicStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi() const
    {
        return 0.11;
    }

    double NordicStoneRevetmentDefaults::GetWaveAngleImpactBetamax() const
    {
        return 78;
    }
}

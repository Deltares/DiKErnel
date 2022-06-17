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

#include "NordicStoneRevetmentTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadXib() const
    {
        return 2.9;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadAp() const
    {
        return 4;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadBp() const
    {
        return 0;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadCp() const
    {
        return 0;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadNp() const
    {
        return -0.9;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadAs() const
    {
        return 0.8;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadBs() const
    {
        return 0;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadCs() const
    {
        return 0;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetHydraulicLoadNs() const
    {
        return 0.6;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetSlopeUpperLevelAus() const
    {
        return 0.05;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetSlopeLowerLevelAls() const
    {
        return 1.5;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetUpperLimitLoadingAul() const
    {
        return 0.1;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetUpperLimitLoadingBul() const
    {
        return 0.6;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetUpperLimitLoadingCul() const
    {
        return 4;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetLowerLimitLoadingAll() const
    {
        return 0.1;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetLowerLimitLoadingBll() const
    {
        return 0.2;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetLowerLimitLoadingCll() const
    {
        return 4;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetDistanceMaximumWaveElevationAsmax() const
    {
        return 0.42;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetDistanceMaximumWaveElevationBsmax() const
    {
        return 0.9;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetNormativeWidthOfWaveImpactAwi() const
    {
        return 0.96;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetNormativeWidthOfWaveImpactBwi() const
    {
        return 0.11;
    }

    double NordicStoneRevetmentTopLayerDefaults::GetWaveAngleImpactBetamax() const
    {
        return 78;
    }
}

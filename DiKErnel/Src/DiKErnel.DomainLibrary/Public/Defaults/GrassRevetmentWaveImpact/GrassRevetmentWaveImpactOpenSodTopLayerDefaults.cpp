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

#include "GrassRevetmentWaveImpactOpenSodTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetTimeLineAgwi() const
    {
        return 0.8;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetTimeLineBgwi() const
    {
        return -0.00001944;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetTimeLineCgwi() const
    {
        return 0.25;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetMinimumWaveHeightTemax() const
    {
        return 3600000;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetMaximumWaveHeightTemin() const
    {
        return 3.6;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetWaveAngleImpactNwa() const
    {
        return 2.0 / 3.0;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetWaveAngleImpactQwa() const
    {
        return 0.35;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetWaveAngleImpactRwa() const
    {
        return 10;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetUpperLimitLoadingAul() const
    {
        return 0;
    }

    double GrassRevetmentWaveImpactOpenSodTopLayerDefaults::GetLowerLimitLoadingAll() const
    {
        return 0.5;
    }
}

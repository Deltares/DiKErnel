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

#include "GrassRevetmentWaveImpactClosedSodDefaults.h"

namespace DiKErnel::DomainLibrary
{
    double GrassRevetmentWaveImpactClosedSodDefaults::GetTimeLineAgwi() const
    {
        return 1;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetTimeLineBgwi() const
    {
        return -0.000009722;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetTimeLineCgwi() const
    {
        return 0.25;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetMinimumWaveHeightTemax() const
    {
        return 3600000;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetMaximumWaveHeightTemin() const
    {
        return 3.6;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetWaveAngleImpactNwa() const
    {
        return 2.0 / 3.0;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetWaveAngleImpactQwa() const
    {
        return 0.35;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetWaveAngleImpactRwa() const
    {
        return 10;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetUpperLimitLoadingAul() const
    {
        return 0;
    }

    double GrassRevetmentWaveImpactClosedSodDefaults::GetLowerLimitLoadingAll() const
    {
        return 0.5;
    }
}

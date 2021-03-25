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

#include "HydraulicLoadOnNaturalStone.h"

namespace DiKErnel::KernelWrapper::Json
{
    HydraulicLoadOnNaturalStone::HydraulicLoadOnNaturalStone(
        const double hydraulicLoadOnNaturalStoneXib,
        const double hydraulicLoadOnNaturalStoneAp,
        const double hydraulicLoadOnNaturalStoneBp,
        const double hydraulicLoadOnNaturalStoneCp,
        const double hydraulicLoadOnNaturalStoneNp,
        const double hydraulicLoadOnNaturalStoneAs,
        const double hydraulicLoadOnNaturalStoneBs,
        const double hydraulicLoadOnNaturalStoneCs,
        const double hydraulicLoadOnNaturalStoneNs)
        : _hydraulicLoadOnNaturalStoneXib(hydraulicLoadOnNaturalStoneXib),
          _hydraulicLoadOnNaturalStoneAp(hydraulicLoadOnNaturalStoneAp),
          _hydraulicLoadOnNaturalStoneBp(hydraulicLoadOnNaturalStoneBp),
          _hydraulicLoadOnNaturalStoneCp(hydraulicLoadOnNaturalStoneCp),
          _hydraulicLoadOnNaturalStoneNp(hydraulicLoadOnNaturalStoneNp),
          _hydraulicLoadOnNaturalStoneAs(hydraulicLoadOnNaturalStoneAs),
          _hydraulicLoadOnNaturalStoneBs(hydraulicLoadOnNaturalStoneBs),
          _hydraulicLoadOnNaturalStoneCs(hydraulicLoadOnNaturalStoneCs),
          _hydraulicLoadOnNaturalStoneNs(hydraulicLoadOnNaturalStoneNs) { }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneXib() const
    {
        return _hydraulicLoadOnNaturalStoneXib;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneAp() const
    {
        return _hydraulicLoadOnNaturalStoneAp;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneBp() const
    {
        return _hydraulicLoadOnNaturalStoneBp;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneCp() const
    {
        return _hydraulicLoadOnNaturalStoneCp;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneNp() const
    {
        return _hydraulicLoadOnNaturalStoneNp;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneAs() const
    {
        return _hydraulicLoadOnNaturalStoneAs;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneBs() const
    {
        return _hydraulicLoadOnNaturalStoneBs;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneCs() const
    {
        return _hydraulicLoadOnNaturalStoneCs;
    }

    double HydraulicLoadOnNaturalStone::GetHydraulicLoadOnNaturalStoneNs() const
    {
        return _hydraulicLoadOnNaturalStoneNs;
    }
}

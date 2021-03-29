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

#include "NaturalStoneRevetmentHydraulicLoads.h"

namespace DiKErnel::Integration
{
    NaturalStoneRevetmentHydraulicLoads::NaturalStoneRevetmentHydraulicLoads(
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double hydraulicLoadXib)
        : _hydraulicLoadAp(hydraulicLoadAp),
          _hydraulicLoadBp(hydraulicLoadBp),
          _hydraulicLoadCp(hydraulicLoadCp),
          _hydraulicLoadNp(hydraulicLoadNp),
          _hydraulicLoadAs(hydraulicLoadAs),
          _hydraulicLoadBs(hydraulicLoadBs),
          _hydraulicLoadCs(hydraulicLoadCs),
          _hydraulicLoadNs(hydraulicLoadNs),
          _hydraulicLoadXib(hydraulicLoadXib) {}

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs;
    }

    double NaturalStoneRevetmentHydraulicLoads::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib;
    }
}

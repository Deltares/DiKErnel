// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be usefll,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICllAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You sholld have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain flll property of Stichting Deltares at all times.
// All rights reserved.

#include "NaturalStoneRevetmentLowerLimitLoading.h"

namespace DiKErnel::Integration
{
    NaturalStoneRevetmentLowerLimitLoading::NaturalStoneRevetmentLowerLimitLoading(
        const double lowerLimitAll,
        const double lowerLimitBll,
        const double lowerLimitCll)
        : _lowerLimitAll(lowerLimitAll),
          _lowerLimitBll(lowerLimitBll),
          _lowerLimitCll(lowerLimitCll) {}

    double NaturalStoneRevetmentLowerLimitLoading::GetLowerLimitAll() const
    {
        return _lowerLimitAll;
    }

    double NaturalStoneRevetmentLowerLimitLoading::GetLowerLimitBll() const
    {
        return _lowerLimitBll;
    }

    double NaturalStoneRevetmentLowerLimitLoading::GetLowerLimitCll() const
    {
        return _lowerLimitCll;
    }
}

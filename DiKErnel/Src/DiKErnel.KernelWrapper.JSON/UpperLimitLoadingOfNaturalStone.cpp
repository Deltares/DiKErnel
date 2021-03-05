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

#include "UpperLimitLoadingOfNaturalStone.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    UpperLimitLoadingOfNaturalStone::UpperLimitLoadingOfNaturalStone(
        const double upperLimitLoadingOfNaturalStoneAul,
        const double upperLimitLoadingOfNaturalStoneBul,
        const double upperLimitLoadingOfNaturalStoneCul)
        : _upperLimitLoadingOfNaturalStoneAul(upperLimitLoadingOfNaturalStoneAul),
          _upperLimitLoadingOfNaturalStoneBul(upperLimitLoadingOfNaturalStoneBul),
          _upperLimitLoadingOfNaturalStoneCul(upperLimitLoadingOfNaturalStoneCul) { }

    double UpperLimitLoadingOfNaturalStone::GetUpperLimitLoadingOfNaturalStoneAul() const
    {
        return _upperLimitLoadingOfNaturalStoneAul;
    }

    double UpperLimitLoadingOfNaturalStone::GetUpperLimitLoadingOfNaturalStoneBul() const
    {
        return _upperLimitLoadingOfNaturalStoneBul;
    }

    double UpperLimitLoadingOfNaturalStone::GetUpperLimitLoadingOfNaturalStoneCul() const
    {
        return _upperLimitLoadingOfNaturalStoneCul;
    }
}

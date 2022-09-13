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

#include "GrassRevetmentOvertoppingTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace std;

    GrassRevetmentOvertoppingTimeDependentOutput::GrassRevetmentOvertoppingTimeDependentOutput(
        GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties& constructionProperties)
        : TimeDependentOutput(constructionProperties),
          _verticalDistanceWaterLevelElevation(move(constructionProperties._verticalDistanceWaterLevelElevation)),
          _representativeWaveRunup2P(move(constructionProperties._representativeWaveRunup2P)),
          _cumulativeOverload(move(constructionProperties._cumulativeOverload))
    {
        ThrowExceptionWhenPropertyIsNullPtr(_verticalDistanceWaterLevelElevation.get(), "verticalDistanceWaterLevelElevation");
    }

    double GrassRevetmentOvertoppingTimeDependentOutput::GetVerticalDistanceWaterLevelElevation() const
    {
        return *_verticalDistanceWaterLevelElevation;
    }

    const double* GrassRevetmentOvertoppingTimeDependentOutput::GetRepresentativeWaveRunup2P() const
    {
        return _representativeWaveRunup2P.get();
    }

    const double* GrassRevetmentOvertoppingTimeDependentOutput::GetCumulativeOverload() const
    {
        return _cumulativeOverload.get();
    }
}

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

#include "Revetment.h"

#include <cmath>

#include "Constants.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace DomainLibrary;

    double Revetment::CalculateLoadingOfRevetment()
    {
        return 1.0;
    }

    double Revetment::CalculateIncrementOfTime(
        const double startTime,
        const double endTime)
    {
        return endTime - startTime;
    }

    double Revetment::CalculateSurfSimilarityParameter(
        const double tanA,
        const double waveHeightHm0,
        const double wavePeriodTm10)
    {
        return tanA / sqrt(2 * Constants::PI * waveHeightHm0 / (Constants::GRAVITATIONAL_ACCELERATION * pow(wavePeriodTm10, 2.0)));
    }
}

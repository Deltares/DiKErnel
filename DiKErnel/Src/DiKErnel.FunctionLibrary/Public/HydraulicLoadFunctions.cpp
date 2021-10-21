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

#include "HydraulicLoadFunctions.h"

#include <cmath>

#include "GenericFunctions.h"

namespace DiKErnel::FunctionLibrary
{
    double HydraulicLoadFunctions::SlopeAngle(
        const double outerSlope)
    {
        return GenericFunctions::Degrees(atan(outerSlope));
    }

    bool HydraulicLoadFunctions::LoadingRevetment(
        const double lowerLimitLoadingRevetment,
        const double upperLimitLoadingRevetment,
        const double z)
    {
        return z >= lowerLimitLoadingRevetment && z <= upperLimitLoadingRevetment;
    }

    double HydraulicLoadFunctions::SurfSimilarityParameter(
        const double outerSlope,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double gravitationalAcceleration)
    {
        return outerSlope / sqrt(2.0 * GenericFunctions::Pi() * waveHeightHm0 / (gravitationalAcceleration * pow(wavePeriodTm10, 2.0)));
    }

    double HydraulicLoadFunctions::WaveSteepnessDeepWater(
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double gravitationalAcceleration)
    {
        return waveHeightHm0 / (gravitationalAcceleration / (2.0 * GenericFunctions::Pi()) * pow(wavePeriodTm10, 2.0));
    }

    double HydraulicLoadFunctions::VerticalDistanceWaterLevelElevation(
        const double z,
        const double waterLevel)
    {
        return z - waterLevel;
    }
}

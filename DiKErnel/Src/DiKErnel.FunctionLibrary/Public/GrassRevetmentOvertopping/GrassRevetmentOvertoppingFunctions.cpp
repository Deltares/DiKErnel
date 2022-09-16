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

#include "GrassRevetmentOvertoppingFunctions.h"

#include <algorithm>
#include <cmath>
#include <functional>

#include "Geometry.h"
#include "GrassRevetmentFunctions.h"
#include "Input.h"
#include "Load.h"
#include "OvertoppingAdapter.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;
    using namespace External::Overtopping;

    double GrassRevetmentOvertoppingFunctions::RepresentativeWaveRunup2P(
        const GrassRevetmentOvertoppingRepresentative2PInput& input)
    {
        Load load
        {
            ._waterLevel = input._waterLevel,
            ._height = input._waveHeightHm0,
            ._period = input._wavePeriodTm10,
            ._direction = input._waveDirection
        };

        Geometry geometry
        {
            ._normal = 0.0,
            ._nPoints = static_cast<int>(input._xValuesProfile.size()),
            ._xCoords = input._xValuesProfile.data(),
            ._yCoords = input._zValuesProfile.data(),
            ._roughness = input._roughnessCoefficients.data()
        };

        Input overtoppingInput{
            ._factorDeterminationQnFn = 1.0,
            ._factorDeterminationQbFb = 1.0,
            ._mz2 = 1.0,
            ._fshallow = 1.0,
            ._computedOvertopping = 1.0,
            ._criticalOvertopping = 1.0,
            ._relaxationfactor = 1.0,
            ._reductionFactorForeshore = 0.5
        };

        Result result{};

        bool success = false;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(255);

        OvertoppingAdapter::CalculateQo(load, geometry, overtoppingInput, &result, messageBuffer.get(), &success, input._dikeHeight);

        return result._z2;
    }

    double GrassRevetmentOvertoppingFunctions::CumulativeOverload(
        const GrassRevetmentOvertoppingCumulativeOverloadInput& input)
    {
        const function getFrontVelocity = [&input](
            const double waveRunup)
        {
            return FrontVelocity(waveRunup, input._verticalDistanceWaterLevelElevation, input._accelerationAlphaA, input._frontVelocityCwo,
                                 input._gravitationalAcceleration);
        };

        return GrassRevetmentFunctions::CumulativeOverload(input, getFrontVelocity);
    }

    double GrassRevetmentOvertoppingFunctions::FrontVelocity(
        const double waveRunup,
        const double verticalDistanceWaterLevelElevation,
        const double accelerationAlphaA,
        const double frontVelocityCwo,
        const double gravitationalAcceleration)
    {
        return frontVelocityCwo * accelerationAlphaA * sqrt(gravitationalAcceleration * max(0.0, waveRunup - verticalDistanceWaterLevelElevation));
    }
}

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

#include "GrassRevetmentOvertoppingLocationDependentInputFactory.h"

#include "GrassRevetmentCumulativeOverloadDefaults.h"
#include "GrassRevetmentCumulativeOverloadDefaultsFactory.h"
#include "GrassRevetmentOvertoppingDefaults.h"
#include "InputHelper.h"
#include "RevetmentDefaults.h"
#include "UniquePtrHelper.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;
    using namespace Util;

    unique_ptr<GrassRevetmentOvertoppingLocationDependentInput>
    GrassRevetmentOvertoppingLocationDependentInputFactory::CreateLocationDependentInput(
        const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties)
    {
        const auto topLayerDefaults = GrassRevetmentCumulativeOverloadDefaultsFactory::CreateTopLayerDefaults(
            constructionProperties.GetTopLayerType());

        auto locationDependentAccelerationAlphaA = make_unique<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA>(
            InputHelper::GetValue(constructionProperties.GetAccelerationAlphaAForCrest(),
                                  GrassRevetmentOvertoppingDefaults::GetAccelerationAlphaAForCrest()),
            InputHelper::GetValue(constructionProperties.GetAccelerationAlphaAForInnerSlope(),
                                  GrassRevetmentOvertoppingDefaults::GetAccelerationAlphaAForInnerSlope()));

        return make_unique<GrassRevetmentOvertoppingLocationDependentInput>(
            constructionProperties.GetX(),
            InputHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            InputHelper::GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
            InputHelper::GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
            InputHelper::GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetIncreasedLoadTransitionAlphaM()),
            InputHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetReducedStrengthTransitionAlphaS()),
            InputHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetAverageNumberOfWavesCtm()),
            InputHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetFixedNumberOfWaves()),
            InputHelper::GetValue(constructionProperties.GetFrontVelocityCwo(), GrassRevetmentOvertoppingDefaults::GetFrontVelocityCwo()),
            move(locationDependentAccelerationAlphaA),
            UniquePtrHelper::CreatePtrOfValue(constructionProperties.GetDikeHeight()));
    }
}

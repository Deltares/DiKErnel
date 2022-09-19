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

#include "DefaultsFactoryException.h"
#include "GrassRevetmentCumulativeOverloadDefaults.h"
#include "GrassRevetmentCumulativeOverloadDefaultsFactory.h"
#include "IGrassRevetmentCumulativeOverloadTopLayerDefaults.h"
#include "InputFactoryException.h"
#include "InputFactoryHelper.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<GrassRevetmentOvertoppingLocationDependentInput> GrassRevetmentOvertoppingLocationDependentInputFactory::
    CreateLocationDependentInput(
        const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentCumulativeOverloadTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentCumulativeOverloadDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException& e)
        {
            throw_with_nested(InputFactoryException(e.what()));
        }

        auto locationDependentAccelerationAlphaA = make_unique<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA>(
            InputFactoryHelper::GetValue(constructionProperties.GetAccelerationAlphaAForCrest(), 1.1),
            InputFactoryHelper::GetValue(constructionProperties.GetAccelerationAlphaAForInnerSlope(), 1.1));

        return make_unique<GrassRevetmentOvertoppingLocationDependentInput>(
            constructionProperties.GetX(),
            InputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            InputFactoryHelper::GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
            InputFactoryHelper::GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
            InputFactoryHelper::GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetIncreasedLoadTransitionAlphaM()),
            InputFactoryHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetReducedStrengthTransitionAlphaS()),
            InputFactoryHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetAverageNumberOfWavesCtm()),
            InputFactoryHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetFixedNumberOfWaves()),
            InputFactoryHelper::GetValue(constructionProperties.GetFrontVelocityCwo(), 1.1),
            move(locationDependentAccelerationAlphaA),
            constructionProperties.GetDikeHeight()
        );
    }
}

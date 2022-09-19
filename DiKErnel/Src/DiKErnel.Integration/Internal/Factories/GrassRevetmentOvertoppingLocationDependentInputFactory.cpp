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
#include "GrassRevetmentWaveRunupDefaults.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighDefaults.h"
#include "IGrassRevetmentWaveRunupTopLayerDefaults.h"
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
        unique_ptr<IGrassRevetmentWaveRunupTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentWaveRunupDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
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
                                         GrassRevetmentWaveRunupDefaults::GetIncreasedLoadTransitionAlphaM()),
            InputFactoryHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                         GrassRevetmentWaveRunupDefaults::GetReducedStrengthTransitionAlphaS()),
            InputFactoryHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                         GrassRevetmentWaveRunupDefaults::GetAverageNumberOfWavesCtm()),
            InputFactoryHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                         GrassRevetmentWaveRunupRayleighDefaults::GetFixedNumberOfWaves()),
            InputFactoryHelper::GetValue(constructionProperties.GetFrontVelocityCwo(), 1.1),
            move(locationDependentAccelerationAlphaA),
            constructionProperties.GetDikeHeight()
        );
    }
}

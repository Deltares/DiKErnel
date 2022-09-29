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

#include "GrassRevetmentWaveRunupRayleighLocationDependentInputFactory.h"

#include "GrassRevetmentCumulativeOverloadDefaults.h"
#include "GrassRevetmentCumulativeOverloadDefaultsFactory.h"
#include "GrassRevetmentWaveRunupDefaults.h"
#include "GrassRevetmentWaveRunupRayleighDefaults.h"
#include "InputFactoryHelper.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationDependentInput> GrassRevetmentWaveRunupRayleighLocationDependentInputFactory::
    CreateLocationDependentInput(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        const auto topLayerDefaults = GrassRevetmentCumulativeOverloadDefaultsFactory::CreateTopLayerDefaults(
            constructionProperties.GetTopLayerType());

        auto representative2P = make_unique<GrassRevetmentWaveRunupRepresentative2P>(
            InputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(),
                                         GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru()),
            InputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(),
                                         GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru()),
            InputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(),
                                         GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru()),
            InputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(),
                                         GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab()),
            InputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(),
                                         GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactAbeta(),
                                         GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta()),
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactBetamax(),
                                         GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax()));

        return make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
            constructionProperties.GetX(),
            InputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetOuterSlope(),
            InputFactoryHelper::GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
            InputFactoryHelper::GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
            InputFactoryHelper::GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetIncreasedLoadTransitionAlphaM()),
            InputFactoryHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetReducedStrengthTransitionAlphaS()),
            InputFactoryHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetAverageNumberOfWavesCtm()),
            move(representative2P),
            move(waveAngleImpact),
            InputFactoryHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                         GrassRevetmentCumulativeOverloadDefaults::GetFixedNumberOfWaves()),
            InputFactoryHelper::GetValue(constructionProperties.GetFrontVelocityCu(),
                                         GrassRevetmentWaveRunupRayleighDefaults::GetFrontVelocityCu()));
    }
}

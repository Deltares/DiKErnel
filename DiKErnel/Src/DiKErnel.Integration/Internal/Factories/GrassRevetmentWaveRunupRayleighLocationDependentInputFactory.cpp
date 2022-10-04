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
#include "InputHelper.h"
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
            InputHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(),
                                  GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru()),
            InputHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(),
                                  GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru()),
            InputHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(),
                                  GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru()),
            InputHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(),
                                  GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab()),
            InputHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(),
                                  GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactAbeta(), GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta()),
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactBetamax(),
                                  GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax()));

        return make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
            constructionProperties.GetX(),
            InputHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetOuterSlope(),
            InputHelper::GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
            InputHelper::GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
            InputHelper::GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetIncreasedLoadTransitionAlphaM()),
            InputHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetReducedStrengthTransitionAlphaS()),
            InputHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetAverageNumberOfWavesCtm()),
            move(representative2P),
            move(waveAngleImpact),
            InputHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                  GrassRevetmentCumulativeOverloadDefaults::GetFixedNumberOfWaves()),
            InputHelper::GetValue(constructionProperties.GetFrontVelocityCu(), GrassRevetmentWaveRunupRayleighDefaults::GetFrontVelocityCu()));
    }
}

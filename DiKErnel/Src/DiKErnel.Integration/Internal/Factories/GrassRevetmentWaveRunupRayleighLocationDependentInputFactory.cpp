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

#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveRunupDefaults.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighDefaults.h"
#include "IGrassRevetmentWaveRunupTopLayerDefaults.h"
#include "LocationDependentInputFactoryException.h"
#include "LocationDependentInputFactoryHelper.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationDependentInput> GrassRevetmentWaveRunupRayleighLocationDependentInputFactory::
    CreateLocationDependentInput(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentWaveRunupTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentWaveRunupDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException& e)
        {
            throw_with_nested(LocationDependentInputFactoryException(e.what()));
        }

        auto representative2P = make_unique<GrassRevetmentWaveRunupRepresentative2P>(
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(),
                                                          GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(),
                                                          GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(),
                                                          GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(),
                                                          GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(),
                                                          GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactAbeta(),
                                                          GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactBetamax(),
                                                          GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax()));

        return make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
            constructionProperties.GetX(),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetOuterSlope(),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetCriticalCumulativeOverload(),
                                                          topLayerDefaults->GetCriticalCumulativeOverload()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetCriticalFrontVelocity(),
                                                          topLayerDefaults->GetCriticalFrontVelocity()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                                                          GrassRevetmentWaveRunupDefaults::GetIncreasedLoadTransitionAlphaM()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                                                          GrassRevetmentWaveRunupDefaults::GetReducedStrengthTransitionAlphaS()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetAverageNumberOfWavesCtm(),
                                                          GrassRevetmentWaveRunupDefaults::GetAverageNumberOfWavesCtm()),
            move(representative2P),
            move(waveAngleImpact),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFixedNumberOfWaves(),
                                                          GrassRevetmentWaveRunupRayleighDefaults::GetFixedNumberOfWaves()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFrontVelocityCu(),
                                                          GrassRevetmentWaveRunupRayleighDefaults::GetFrontVelocityCu()));
    }
}

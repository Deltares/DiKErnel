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

#include "GrassRevetmentWaveImpactLocationDependentInputFactory.h"

#include "GrassRevetmentWaveImpactDefaults.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "InputFactoryHelper.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<GrassRevetmentWaveImpactLocationDependentInput> GrassRevetmentWaveImpactLocationDependentInputFactory::
    CreateLocationDependentInput(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        const auto topLayerDefaults = GrassRevetmentWaveImpactDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());

        auto waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactNwa()),
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactQwa()),
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactRwa(),
                                         GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactRwa()));

        auto timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
            InputFactoryHelper::GetValue(constructionProperties.GetTimeLineAgwi(), topLayerDefaults->GetTimeLineAgwi()),
            InputFactoryHelper::GetValue(constructionProperties.GetTimeLineBgwi(), topLayerDefaults->GetTimeLineBgwi()),
            InputFactoryHelper::GetValue(constructionProperties.GetTimeLineCgwi(), topLayerDefaults->GetTimeLineCgwi()));

        return make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
            constructionProperties.GetX(),
            InputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            move(waveAngleImpact),
            InputFactoryHelper::GetValue(constructionProperties.GetMinimumWaveHeightTemax(),
                                         GrassRevetmentWaveImpactDefaults::GetMinimumWaveHeightTemax()),
            InputFactoryHelper::GetValue(constructionProperties.GetMaximumWaveHeightTemin(),
                                         GrassRevetmentWaveImpactDefaults::GetMaximumWaveHeightTemin()),
            move(timeLine),
            InputFactoryHelper::GetValue(constructionProperties.GetUpperLimitLoadingAul(),
                                         GrassRevetmentWaveImpactDefaults::GetUpperLimitLoadingAul()),
            InputFactoryHelper::GetValue(constructionProperties.GetLowerLimitLoadingAll(),
                                         GrassRevetmentWaveImpactDefaults::GetLowerLimitLoadingAll()));
    }
}

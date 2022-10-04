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
#include "InputHelper.h"
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
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactNwa()),
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactQwa()),
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactRwa()));

        auto timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
            InputHelper::GetValue(constructionProperties.GetTimeLineAgwi(), topLayerDefaults->GetTimeLineAgwi()),
            InputHelper::GetValue(constructionProperties.GetTimeLineBgwi(), topLayerDefaults->GetTimeLineBgwi()),
            InputHelper::GetValue(constructionProperties.GetTimeLineCgwi(), topLayerDefaults->GetTimeLineCgwi()));

        return make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
            constructionProperties.GetX(),
            InputHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            move(waveAngleImpact),
            InputHelper::GetValue(constructionProperties.GetMinimumWaveHeightTemax(),
                                  GrassRevetmentWaveImpactDefaults::GetMinimumWaveHeightTemax()),
            InputHelper::GetValue(constructionProperties.GetMaximumWaveHeightTemin(),
                                  GrassRevetmentWaveImpactDefaults::GetMaximumWaveHeightTemin()),
            move(timeLine),
            InputHelper::GetValue(constructionProperties.GetUpperLimitLoadingAul(), GrassRevetmentWaveImpactDefaults::GetUpperLimitLoadingAul()),
            InputHelper::GetValue(constructionProperties.GetLowerLimitLoadingAll(), GrassRevetmentWaveImpactDefaults::GetLowerLimitLoadingAll()));
    }
}

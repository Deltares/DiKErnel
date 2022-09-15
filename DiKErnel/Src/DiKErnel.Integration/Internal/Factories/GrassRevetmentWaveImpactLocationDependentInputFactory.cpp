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

#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactDefaults.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "IGrassRevetmentWaveImpactTopLayerDefaults.h"
#include "LocationDependentInputFactoryException.h"
#include "LocationDependentInputFactoryHelper.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<GrassRevetmentWaveImpactLocationDependentInput> GrassRevetmentWaveImpactLocationDependentInputFactory::
    CreateLocationDependentInput(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentWaveImpactTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentWaveImpactDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException& e)
        {
            throw_with_nested(LocationDependentInputFactoryException(e.what()));
        }

        auto waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactNwa(),
                                                          GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactNwa()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactQwa(),
                                                          GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactQwa()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactRwa(),
                                                          GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactRwa()));

        auto timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetTimeLineAgwi(), topLayerDefaults->GetTimeLineAgwi()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetTimeLineBgwi(), topLayerDefaults->GetTimeLineBgwi()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetTimeLineCgwi(), topLayerDefaults->GetTimeLineCgwi()));

        return make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
            constructionProperties.GetX(),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            move(waveAngleImpact),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetMinimumWaveHeightTemax(),
                                                          GrassRevetmentWaveImpactDefaults::GetMinimumWaveHeightTemax()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetMaximumWaveHeightTemin(),
                                                          GrassRevetmentWaveImpactDefaults::GetMaximumWaveHeightTemin()),
            move(timeLine),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetUpperLimitLoadingAul(),
                                                          GrassRevetmentWaveImpactDefaults::GetUpperLimitLoadingAul()),
            LocationDependentInputFactoryHelper::GetValue(constructionProperties.GetLowerLimitLoadingAll(),
                                                          GrassRevetmentWaveImpactDefaults::GetLowerLimitLoadingAll()));
    }
}

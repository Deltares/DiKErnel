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

#include "NaturalStoneRevetmentLocationDependentInputFactory.h"

#include "InputFactoryHelper.h"
#include "NaturalStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentDefaultsFactory.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace std;
    using namespace DomainLibrary;

    unique_ptr<NaturalStoneRevetmentLocationDependentInput> NaturalStoneRevetmentLocationDependentInputFactory::CreateLocationDependentInput(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        const auto& topLayerDefaults = NaturalStoneRevetmentDefaultsFactory::CreateTopLayerDefaults();

        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadAp(), topLayerDefaults->GetHydraulicLoadAp()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadBp(), topLayerDefaults->GetHydraulicLoadBp()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadCp(), topLayerDefaults->GetHydraulicLoadCp()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadNp(), topLayerDefaults->GetHydraulicLoadNp()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadAs(), topLayerDefaults->GetHydraulicLoadAs()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadBs(), topLayerDefaults->GetHydraulicLoadBs()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadCs(), topLayerDefaults->GetHydraulicLoadCs()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadNs(), topLayerDefaults->GetHydraulicLoadNs()),
            InputFactoryHelper::GetValue(constructionProperties.GetHydraulicLoadXib(), topLayerDefaults->GetHydraulicLoadXib()));

        auto slope = make_unique<NaturalStoneRevetmentSlope>(
            InputFactoryHelper::GetValue(constructionProperties.GetSlopeUpperLevelAus(), NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus()),
            InputFactoryHelper::GetValue(constructionProperties.GetSlopeLowerLevelAls(), NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls()));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            InputFactoryHelper::GetValue(constructionProperties.GetUpperLimitLoadingAul(),
                                         NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul()),
            InputFactoryHelper::GetValue(constructionProperties.GetUpperLimitLoadingBul(),
                                         NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul()),
            InputFactoryHelper::GetValue(constructionProperties.GetUpperLimitLoadingCul(),
                                         NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul()));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            InputFactoryHelper::GetValue(constructionProperties.GetLowerLimitLoadingAll(),
                                         NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll()),
            InputFactoryHelper::GetValue(constructionProperties.GetLowerLimitLoadingBll(),
                                         NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll()),
            InputFactoryHelper::GetValue(constructionProperties.GetLowerLimitLoadingCll(),
                                         NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll()));

        auto distanceMaximumWaveElevation = make_unique<
            NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            InputFactoryHelper::GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                                         NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax()),
            InputFactoryHelper::GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                                         NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax()));

        auto normativeWidthOfWaveImpact = make_unique<
            NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            InputFactoryHelper::GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(),
                                         NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi()),
            InputFactoryHelper::GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(),
                                         NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi()));

        auto waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
            InputFactoryHelper::GetValue(constructionProperties.GetWaveAngleImpactBetamax(),
                                         NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax()));

        return make_unique<NaturalStoneRevetmentLocationDependentInput>(
            constructionProperties.GetX(),
            InputFactoryHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputFactoryHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
            constructionProperties.GetRelativeDensity(),
            constructionProperties.GetThicknessTopLayer(),
            move(hydraulicLoads),
            move(slope),
            move(upperLimitLoading),
            move(lowerLimitLoading),
            move(distanceMaximumWaveElevation),
            move(normativeWidthOfWaveImpact),
            move(waveAngleImpact));
    }
}

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

#include "InputHelper.h"
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
        const auto topLayerDefaults = NaturalStoneRevetmentDefaultsFactory::CreateTopLayerDefaults();

        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadAp(), topLayerDefaults->GetHydraulicLoadAp()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadBp(), topLayerDefaults->GetHydraulicLoadBp()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadCp(), topLayerDefaults->GetHydraulicLoadCp()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadNp(), topLayerDefaults->GetHydraulicLoadNp()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadAs(), topLayerDefaults->GetHydraulicLoadAs()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadBs(), topLayerDefaults->GetHydraulicLoadBs()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadCs(), topLayerDefaults->GetHydraulicLoadCs()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadNs(), topLayerDefaults->GetHydraulicLoadNs()),
            InputHelper::GetValue(constructionProperties.GetHydraulicLoadXib(), topLayerDefaults->GetHydraulicLoadXib()));

        auto slope = make_unique<NaturalStoneRevetmentSlope>(
            InputHelper::GetValue(constructionProperties.GetSlopeUpperLevelAus(), NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus()),
            InputHelper::GetValue(constructionProperties.GetSlopeLowerLevelAls(), NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls()));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            InputHelper::GetValue(constructionProperties.GetUpperLimitLoadingAul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul()),
            InputHelper::GetValue(constructionProperties.GetUpperLimitLoadingBul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul()),
            InputHelper::GetValue(constructionProperties.GetUpperLimitLoadingCul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul()));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            InputHelper::GetValue(constructionProperties.GetLowerLimitLoadingAll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll()),
            InputHelper::GetValue(constructionProperties.GetLowerLimitLoadingBll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll()),
            InputHelper::GetValue(constructionProperties.GetLowerLimitLoadingCll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll()));

        auto distanceMaximumWaveElevation = make_unique<
            NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            InputHelper::GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                                  NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax()),
            InputHelper::GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                                  NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax()));

        auto normativeWidthOfWaveImpact = make_unique<
            NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            InputHelper::GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(),
                                  NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi()),
            InputHelper::GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(),
                                  NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi()));

        auto waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
            InputHelper::GetValue(constructionProperties.GetWaveAngleImpactBetamax(), NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax()));
        return make_unique<NaturalStoneRevetmentLocationDependentInput>(
            constructionProperties.GetX(),
            InputHelper::GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            InputHelper::GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
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

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

#include "DefaultsFactoryException.h"
#include "INaturalStoneRevetmentTopLayerDefaults.h"
#include "LocationDependentInputFactoryException.h"
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
        unique_ptr<INaturalStoneRevetmentTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = NaturalStoneRevetmentDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            throw_with_nested(LocationDependentInputFactoryException("Could not create instance."));
        }

        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            GetValue(constructionProperties.GetHydraulicLoadAp(), topLayerDefaults->GetHydraulicLoadAp()),
            GetValue(constructionProperties.GetHydraulicLoadBp(), topLayerDefaults->GetHydraulicLoadBp()),
            GetValue(constructionProperties.GetHydraulicLoadCp(), topLayerDefaults->GetHydraulicLoadCp()),
            GetValue(constructionProperties.GetHydraulicLoadNp(), topLayerDefaults->GetHydraulicLoadNp()),
            GetValue(constructionProperties.GetHydraulicLoadAs(), topLayerDefaults->GetHydraulicLoadAs()),
            GetValue(constructionProperties.GetHydraulicLoadBs(), topLayerDefaults->GetHydraulicLoadBs()),
            GetValue(constructionProperties.GetHydraulicLoadCs(), topLayerDefaults->GetHydraulicLoadCs()),
            GetValue(constructionProperties.GetHydraulicLoadNs(), topLayerDefaults->GetHydraulicLoadNs()),
            GetValue(constructionProperties.GetHydraulicLoadXib(), topLayerDefaults->GetHydraulicLoadXib()));

        auto slope = make_unique<NaturalStoneRevetmentSlope>(
            GetValue(constructionProperties.GetSlopeUpperLevelAus(), NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus()),
            GetValue(constructionProperties.GetSlopeLowerLevelAls(), NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls()));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            GetValue(constructionProperties.GetUpperLimitLoadingAul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul()),
            GetValue(constructionProperties.GetUpperLimitLoadingBul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul()),
            GetValue(constructionProperties.GetUpperLimitLoadingCul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul()));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            GetValue(constructionProperties.GetLowerLimitLoadingAll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll()),
            GetValue(constructionProperties.GetLowerLimitLoadingBll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll()),
            GetValue(constructionProperties.GetLowerLimitLoadingCll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll()));

        auto distanceMaximumWaveElevation = make_unique<
            NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                     NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax()),
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                     NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax()));

        auto normativeWidthOfWaveImpact = make_unique<
            NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(), NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi()),
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(), NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi()));

        auto waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax()));

        return make_unique<NaturalStoneRevetmentLocationDependentInput>(
            constructionProperties.GetX(),
            GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
            GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
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

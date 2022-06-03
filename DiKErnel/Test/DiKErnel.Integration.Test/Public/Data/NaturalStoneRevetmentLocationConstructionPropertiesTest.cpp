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

#include <gtest/gtest.h>

#include "AssertHelper.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        constexpr auto x = 0.1;
        constexpr auto thicknessTopLayer = 0.2;
        constexpr auto relativeDensity = 0.3;

        // Call
        const NaturalStoneRevetmentLocationConstructionProperties constructionProperties(x, topLayerType, thicknessTopLayer, relativeDensity);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(relativeDensity, constructionProperties.GetRelativeDensity());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadXib());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadAp());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadBp());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadCp());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadNp());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadAs());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadBs());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadCs());
        ASSERT_EQ(nullptr, constructionProperties.GetHydraulicLoadNs());
        ASSERT_EQ(nullptr, constructionProperties.GetSlopeUpperLevelAus());
        ASSERT_EQ(nullptr, constructionProperties.GetSlopeLowerLevelAls());
        ASSERT_EQ(nullptr, constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_EQ(nullptr, constructionProperties.GetUpperLimitLoadingBul());
        ASSERT_EQ(nullptr, constructionProperties.GetUpperLimitLoadingCul());
        ASSERT_EQ(nullptr, constructionProperties.GetLowerLimitLoadingAll());
        ASSERT_EQ(nullptr, constructionProperties.GetLowerLimitLoadingBll());
        ASSERT_EQ(nullptr, constructionProperties.GetLowerLimitLoadingCll());
        ASSERT_EQ(nullptr, constructionProperties.GetDistanceMaximumWaveElevationAsmax());
        ASSERT_EQ(nullptr, constructionProperties.GetDistanceMaximumWaveElevationBsmax());
        ASSERT_EQ(nullptr, constructionProperties.GetNormativeWidthOfWaveImpactAwi());
        ASSERT_EQ(nullptr, constructionProperties.GetNormativeWidthOfWaveImpactBwi());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactBetamax());
    }

    TEST(NaturalStoneRevetmentLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        constexpr auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        constexpr auto x = 0.1;
        constexpr auto thicknessTopLayer = 0.2;
        constexpr auto relativeDensity = 0.3;
        constexpr auto initialDamage = 0.4;
        constexpr auto failureNumber = 0.5;
        constexpr auto hydraulicLoadXib = 0.6;
        constexpr auto hydraulicLoadAp = 0.7;
        constexpr auto hydraulicLoadBp = 0.8;
        constexpr auto hydraulicLoadCp = 0.9;
        constexpr auto hydraulicLoadNp = 1.0;
        constexpr auto hydraulicLoadAs = 1.1;
        constexpr auto hydraulicLoadBs = 1.2;
        constexpr auto hydraulicLoadCs = 1.3;
        constexpr auto hydraulicLoadNs = 1.4;
        constexpr auto slopeUpperLevelAus = 1.5;
        constexpr auto slopeLowerLevelAls = 1.6;
        constexpr auto upperLimitLoadingAul = 1.7;
        constexpr auto upperLimitLoadingBul = 1.8;
        constexpr auto upperLimitLoadingCul = 1.9;
        constexpr auto lowerLimitLoadingAll = 2.0;
        constexpr auto lowerLimitLoadingBll = 2.1;
        constexpr auto lowerLimitLoadingCll = 2.2;
        constexpr auto distanceMaximumWaveElevationAsmax = 2.3;
        constexpr auto distanceMaximumWaveElevationBsmax = 2.4;
        constexpr auto normativeWidthOfWaveImpactAwi = 2.5;
        constexpr auto normativeWidthOfWaveImpactBwi = 2.6;
        constexpr auto waveAngleImpactBetamax = 2.7;

        NaturalStoneRevetmentLocationConstructionProperties constructionProperties(x, topLayerType, thicknessTopLayer, relativeDensity);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetHydraulicLoadXib(make_unique<double>(hydraulicLoadXib));
        constructionProperties.SetHydraulicLoadAp(make_unique<double>(hydraulicLoadAp));
        constructionProperties.SetHydraulicLoadBp(make_unique<double>(hydraulicLoadBp));
        constructionProperties.SetHydraulicLoadCp(make_unique<double>(hydraulicLoadCp));
        constructionProperties.SetHydraulicLoadNp(make_unique<double>(hydraulicLoadNp));
        constructionProperties.SetHydraulicLoadAs(make_unique<double>(hydraulicLoadAs));
        constructionProperties.SetHydraulicLoadBs(make_unique<double>(hydraulicLoadBs));
        constructionProperties.SetHydraulicLoadCs(make_unique<double>(hydraulicLoadCs));
        constructionProperties.SetHydraulicLoadNs(make_unique<double>(hydraulicLoadNs));
        constructionProperties.SetSlopeUpperLevelAus(make_unique<double>(slopeUpperLevelAus));
        constructionProperties.SetSlopeLowerLevelAls(make_unique<double>(slopeLowerLevelAls));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties.SetUpperLimitLoadingBul(make_unique<double>(upperLimitLoadingBul));
        constructionProperties.SetUpperLimitLoadingCul(make_unique<double>(upperLimitLoadingCul));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));
        constructionProperties.SetLowerLimitLoadingBll(make_unique<double>(lowerLimitLoadingBll));
        constructionProperties.SetLowerLimitLoadingCll(make_unique<double>(lowerLimitLoadingCll));
        constructionProperties.SetDistanceMaximumWaveElevationAsmax(make_unique<double>(distanceMaximumWaveElevationAsmax));
        constructionProperties.SetDistanceMaximumWaveElevationBsmax(make_unique<double>(distanceMaximumWaveElevationBsmax));
        constructionProperties.SetNormativeWidthOfWaveImpactAwi(make_unique<double>(normativeWidthOfWaveImpactAwi));
        constructionProperties.SetNormativeWidthOfWaveImpactBwi(make_unique<double>(normativeWidthOfWaveImpactBwi));
        constructionProperties.SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(relativeDensity, constructionProperties.GetRelativeDensity());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(hydraulicLoadXib, *constructionProperties.GetHydraulicLoadXib());
        ASSERT_DOUBLE_EQ(hydraulicLoadAp, *constructionProperties.GetHydraulicLoadAp());
        ASSERT_DOUBLE_EQ(hydraulicLoadBp, *constructionProperties.GetHydraulicLoadBp());
        ASSERT_DOUBLE_EQ(hydraulicLoadCp, *constructionProperties.GetHydraulicLoadCp());
        ASSERT_DOUBLE_EQ(hydraulicLoadNp, *constructionProperties.GetHydraulicLoadNp());
        ASSERT_DOUBLE_EQ(hydraulicLoadAs, *constructionProperties.GetHydraulicLoadAs());
        ASSERT_DOUBLE_EQ(hydraulicLoadBs, *constructionProperties.GetHydraulicLoadBs());
        ASSERT_DOUBLE_EQ(hydraulicLoadCs, *constructionProperties.GetHydraulicLoadCs());
        ASSERT_DOUBLE_EQ(hydraulicLoadNs, *constructionProperties.GetHydraulicLoadNs());
        ASSERT_DOUBLE_EQ(slopeUpperLevelAus, *constructionProperties.GetSlopeUpperLevelAus());
        ASSERT_DOUBLE_EQ(slopeLowerLevelAls, *constructionProperties.GetSlopeLowerLevelAls());
        ASSERT_DOUBLE_EQ(upperLimitLoadingAul, *constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_DOUBLE_EQ(upperLimitLoadingBul, *constructionProperties.GetUpperLimitLoadingBul());
        ASSERT_DOUBLE_EQ(upperLimitLoadingCul, *constructionProperties.GetUpperLimitLoadingCul());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, *constructionProperties.GetLowerLimitLoadingAll());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingBll, *constructionProperties.GetLowerLimitLoadingBll());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingCll, *constructionProperties.GetLowerLimitLoadingCll());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationAsmax, *constructionProperties.GetDistanceMaximumWaveElevationAsmax());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationBsmax, *constructionProperties.GetDistanceMaximumWaveElevationBsmax());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactAwi, *constructionProperties.GetNormativeWidthOfWaveImpactAwi());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactBwi, *constructionProperties.GetNormativeWidthOfWaveImpactBwi());
        ASSERT_DOUBLE_EQ(waveAngleImpactBetamax, *constructionProperties.GetWaveAngleImpactBetamax());
    }
}

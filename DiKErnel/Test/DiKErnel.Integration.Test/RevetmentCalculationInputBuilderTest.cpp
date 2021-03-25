// Copyright (C) Stichting Deltares 2020. All rights reserved.
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
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentCalculationInputBuilderException.h"
#include "TimeDependentInputAssertHelper.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace DiKErnel::TestUtil;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct RevetmentCalculationInputBuilderTest : Test
    {
        static void CreateBuilderAndAddInvalidTimeStep()
        {
            RevetmentCalculationInputBuilder builder;
            builder.AddTimeStep(10, 5, 0, 0, 0, 0);
        }

        static void CreateBuilderAndAddNonSuccessiveTimeSteps()
        {
            RevetmentCalculationInputBuilder builder;
            builder.AddTimeStep(0, 5, 0, 0, 0, 0);
            builder.AddTimeStep(10, 20, 0, 0, 0, 0);
            builder.Build();
        }
    };

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        RevetmentCalculationInputBuilder builder;

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());
        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        const auto waterLevel = 0.1;
        const auto waveHeightHm0 = 0.2;
        const auto wavePeriodTm10 = 0.3;
        const auto waveAngle = 0.4;

        RevetmentCalculationInputBuilder builder;
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);

        // When
        const auto calculationInput = builder.Build();

        // Then
        const auto& actualTimeDependentInputItems = calculationInput->GetTimeDependentInputItems();
        ASSERT_EQ(1, actualTimeDependentInputItems.size());
        const auto& timeDependentInput = actualTimeDependentInputItems[0].get();

        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle,
                                                                     timeDependentInput);

        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenAddTimeStepWithInvalidEndTime_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddInvalidTimeStep;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentInput.", "'beginTime' should be smaller than 'endTime'.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = NaturalStoneRevetmentLocationConstructionProperties::TopLayerType::NordicStone;
        const string name = "Test";
        const auto slopeAngle = 0.1;
        const auto thicknessTopLayer = 0.2;
        const auto relativeDensity = 0.3;
        const auto initialDamage = 0.4;
        const auto failureNumber = 0.5;
        const auto hydraulicLoadXib = 0.6;
        const auto hydraulicLoadAp = 0.7;
        const auto hydraulicLoadBp = 0.8;
        const auto hydraulicLoadCp = 0.9;
        const auto hydraulicLoadNp = 1.0;
        const auto hydraulicLoadAs = 1.1;
        const auto hydraulicLoadBs = 1.2;
        const auto hydraulicLoadCs = 1.3;
        const auto hydraulicLoadNs = 1.4;
        const auto upperLimitLoadingAul = 1.5;
        const auto upperLimitLoadingBul = 1.6;
        const auto upperLimitLoadingCul = 1.7;
        const auto lowerLimitLoadingAll = 1.8;
        const auto lowerLimitLoadingBll = 1.9;
        const auto lowerLimitLoadingCll = 2.0;
        const auto distanceMaximumWaveElevationAsmax = 2.1;
        const auto distanceMaximumWaveElevationBsmax = 2.2;
        const auto normativeWidthOfWaveImpactAwi = 2.3;
        const auto normativeWidthOfWaveImpactBwi = 2.4;
        const auto waveAngleImpactBetamax = 2.5;

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            topLayerType, name, slopeAngle, thicknessTopLayer, relativeDensity);
        naturalStoneConstructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        naturalStoneConstructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        naturalStoneConstructionProperties.SetHydraulicLoadXib(make_unique<double>(hydraulicLoadXib));
        naturalStoneConstructionProperties.SetHydraulicLoadAp(make_unique<double>(hydraulicLoadAp));
        naturalStoneConstructionProperties.SetHydraulicLoadBp(make_unique<double>(hydraulicLoadBp));
        naturalStoneConstructionProperties.SetHydraulicLoadCp(make_unique<double>(hydraulicLoadCp));
        naturalStoneConstructionProperties.SetHydraulicLoadNp(make_unique<double>(hydraulicLoadNp));
        naturalStoneConstructionProperties.SetHydraulicLoadAs(make_unique<double>(hydraulicLoadAs));
        naturalStoneConstructionProperties.SetHydraulicLoadBs(make_unique<double>(hydraulicLoadBs));
        naturalStoneConstructionProperties.SetHydraulicLoadCs(make_unique<double>(hydraulicLoadCs));
        naturalStoneConstructionProperties.SetHydraulicLoadNs(make_unique<double>(hydraulicLoadNs));
        naturalStoneConstructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        naturalStoneConstructionProperties.SetUpperLimitLoadingBul(make_unique<double>(upperLimitLoadingBul));
        naturalStoneConstructionProperties.SetUpperLimitLoadingCul(make_unique<double>(upperLimitLoadingCul));
        naturalStoneConstructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));
        naturalStoneConstructionProperties.SetLowerLimitLoadingBll(make_unique<double>(lowerLimitLoadingBll));
        naturalStoneConstructionProperties.SetLowerLimitLoadingCll(make_unique<double>(lowerLimitLoadingCll));
        naturalStoneConstructionProperties.SetDistanceMaximumWaveElevationAsmax(make_unique<double>(distanceMaximumWaveElevationAsmax));
        naturalStoneConstructionProperties.SetDistanceMaximumWaveElevationBsmax(make_unique<double>(distanceMaximumWaveElevationBsmax));
        naturalStoneConstructionProperties.SetNormativeWidthOfWaveImpactAwi(make_unique<double>(normativeWidthOfWaveImpactAwi));
        naturalStoneConstructionProperties.SetNormativeWidthOfWaveImpactBwi(make_unique<double>(normativeWidthOfWaveImpactBwi));
        naturalStoneConstructionProperties.SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));

        RevetmentCalculationInputBuilder builder;
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties(
            name, initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            hydraulicLoadAp, hydraulicLoadBp, hydraulicLoadCp, hydraulicLoadNp, hydraulicLoadAs, hydraulicLoadBs,
            hydraulicLoadCs, hydraulicLoadNs, hydraulicLoadXib, locationDependentInput->GetHydraulicLoads());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            upperLimitLoadingAul, upperLimitLoadingBul, upperLimitLoadingCul, locationDependentInput->GetUpperLimitLoading());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            lowerLimitLoadingAll, lowerLimitLoadingBll, lowerLimitLoadingCll, locationDependentInput->GetLowerLimitLoading());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax,
            locationDependentInput->GetDistanceMaximumWaveElevation());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi,
            locationDependentInput->GetNormativeWidthOfWaveImpact());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactBetamax, locationDependentInput->GetWaveAngleImpact());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = NaturalStoneRevetmentLocationConstructionProperties::TopLayerType::NordicStone;
        const string name = "Test";
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;
        const auto relativeDensity = 0.4;

        const NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            topLayerType, name, slopeAngle, thicknessTopLayer, relativeDensity);

        RevetmentCalculationInputBuilder builder;
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties(
            name, initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInput->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.1, 0.6, 4, locationDependentInput->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.1, 0.2, 4, locationDependentInput->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.42, 0.9, locationDependentInput->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            0.96, 0.11, locationDependentInput->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            78, locationDependentInput->GetWaveAngleImpact());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithInvalidTimeSteps_WhenBuild_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddNonSuccessiveTimeSteps;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentInput.",
            "The begin time of a successive element must equal the end time of the previous element.");
    }
}

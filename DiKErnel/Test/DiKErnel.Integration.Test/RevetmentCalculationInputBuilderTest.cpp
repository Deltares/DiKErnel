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
#include "Defaults.h"
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentCalculationInputBuilderException.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct RevetmentCalculationInputBuilderTest : Test
    {
        static void CreateBuilderAndAddInvalidTimeStep()
        {
            RevetmentCalculationInputBuilder builder(0);
            builder.AddTimeStep(10, 5, 0, 0, 0, 0);
        }

        static void CreateBuilderAndAddNotConnectingTimeStep()
        {
            RevetmentCalculationInputBuilder builder(0);
            builder.AddTimeStep(0, 5, 0, 0, 0, 0);
            builder.AddTimeStep(10, 20, 0, 0, 0, 0);
            builder.Build();
        }

        void AssertTimeDependentInputItems(
            const int expectedBeginTime,
            const int expectedEndTime,
            const double expectedWaterLevel,
            const double expectedWaveHeightHm0,
            const double expectedWavePeriodTm10,
            const double expectedWaveAngle,
            const vector<reference_wrapper<TimeDependentInput>>& actualTimeDependentInputItems) const
        {
            ASSERT_EQ(1, actualTimeDependentInputItems.size());
            const auto& timeDependentInput = actualTimeDependentInputItems[0].get();
            ASSERT_DOUBLE_EQ(expectedBeginTime, timeDependentInput.GetBeginTime());
            ASSERT_DOUBLE_EQ(expectedEndTime, timeDependentInput.GetEndTime());
            ASSERT_DOUBLE_EQ(expectedWaterLevel, timeDependentInput.GetWaterLevel());
            ASSERT_DOUBLE_EQ(expectedWaveHeightHm0, timeDependentInput.GetWaveHeightHm0());
            ASSERT_DOUBLE_EQ(expectedWavePeriodTm10, timeDependentInput.GetWavePeriodTm10());
            ASSERT_DOUBLE_EQ(expectedWaveAngle, timeDependentInput.GetWaveAngle());
        }

        void AssertHydraulicLoads(
            const double plungingCoefficientA,
            const double plungingCoefficientB,
            const double plungingCoefficientC,
            const double plungingCoefficientN,
            const double surgingCoefficientA,
            const double surgingCoefficientB,
            const double surgingCoefficientC,
            const double surgingCoefficientN,
            const double similarityParameterThreshold,
            const NaturalStoneRevetmentHydraulicLoads& hydraulicLoads) const
        {
            ASSERT_DOUBLE_EQ(plungingCoefficientA, hydraulicLoads.GetHydraulicLoadAp());
            ASSERT_DOUBLE_EQ(plungingCoefficientB, hydraulicLoads.GetHydraulicLoadBp());
            ASSERT_DOUBLE_EQ(plungingCoefficientC, hydraulicLoads.GetHydraulicLoadCp());
            ASSERT_DOUBLE_EQ(plungingCoefficientN, hydraulicLoads.GetHydraulicLoadNp());
            ASSERT_DOUBLE_EQ(surgingCoefficientA, hydraulicLoads.GetHydraulicLoadAs());
            ASSERT_DOUBLE_EQ(surgingCoefficientB, hydraulicLoads.GetHydraulicLoadBs());
            ASSERT_DOUBLE_EQ(surgingCoefficientC, hydraulicLoads.GetHydraulicLoadCs());
            ASSERT_DOUBLE_EQ(surgingCoefficientN, hydraulicLoads.GetHydraulicLoadNs());
            ASSERT_DOUBLE_EQ(similarityParameterThreshold, hydraulicLoads.GetHydraulicLoadXib());
        }

        void AssertUpperLimitLoading(
            const double upperLimitLoadingAul,
            const double upperLimitLoadingBul,
            const double upperLimitLoadingCul,
            const NaturalStoneRevetmentUpperLimitLoading& upperLimitLoading) const
        {
            ASSERT_DOUBLE_EQ(upperLimitLoadingAul, upperLimitLoading.GetUpperLimitAul());
            ASSERT_DOUBLE_EQ(upperLimitLoadingBul, upperLimitLoading.GetUpperLimitBul());
            ASSERT_DOUBLE_EQ(upperLimitLoadingCul, upperLimitLoading.GetUpperLimitCul());
        }

        void AssertLowerLimitLoading(
            const double lowerLimitLoadingAll,
            const double lowerLimitLoadingBll,
            const double lowerLimitLoadingCll,
            const NaturalStoneRevetmentLowerLimitLoading& lowerLimitLoading) const
        {
            ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, lowerLimitLoading.GetLowerLimitAll());
            ASSERT_DOUBLE_EQ(lowerLimitLoadingBll, lowerLimitLoading.GetLowerLimitBll());
            ASSERT_DOUBLE_EQ(lowerLimitLoadingCll, lowerLimitLoading.GetLowerLimitCll());
        }

        void AssertDistanceMaximumWaveElevation(
            const double distanceMaximumWaveElevationAsmax,
            const double distanceMaximumWaveElevationBsmax,
            const NaturalStoneRevetmentDistanceMaximumWaveElevation& distanceMaximumWaveElevation) const
        {
            ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevation.GetDistanceMaximumWaveElevationAsmax());
            ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationBsmax, distanceMaximumWaveElevation.GetDistanceMaximumWaveElevationBsmax());
        }

        void AssertNormativeWidthOfWaveImpact(
            const double normativeWidthOfWaveImpactAwi,
            const double normativeWidthOfWaveImpactBwi,
            const NaturalStoneRevetmentNormativeWidthOfWaveImpact& normativeWidthOfWaveImpact) const
        {
            ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactAwi());
            ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactBwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactBwi());
        }
    };

    TEST_F(RevetmentCalculationInputBuilderTest, GiveBuilder_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());
        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        const auto waterLevel = 0.1;
        const auto waveHeightHm0 = 0.2;
        const auto wavePeriodTm10 = 0.3;
        const auto waveAngle = 0.4;

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());

        const auto& actualTimeDependentInputItems = calculationInput->GetTimeDependentInputItems();
        ASSERT_EQ(1, actualTimeDependentInputItems.size());
        const auto& timeDependentInput = actualTimeDependentInputItems[0].get();
        ASSERT_DOUBLE_EQ(beginTime, timeDependentInput.GetBeginTime());
        ASSERT_DOUBLE_EQ(endTime, timeDependentInput.GetEndTime());
        ASSERT_DOUBLE_EQ(waterLevel, timeDependentInput.GetWaterLevel());
        ASSERT_DOUBLE_EQ(waveHeightHm0, timeDependentInput.GetWaveHeightHm0());
        ASSERT_DOUBLE_EQ(wavePeriodTm10, timeDependentInput.GetWavePeriodTm10());
        ASSERT_DOUBLE_EQ(waveAngle, timeDependentInput.GetWaveAngle());

        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenAddTimeStepWithInvalidEndTime_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Call
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddInvalidTimeStep;

        // Assert
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentInput.", "'beginTime' should be smaller than 'endTime'.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;
        const auto relativeDensity = 0.4;
        const auto similarityParameterThreshold = 0.5;
        const auto plungingCoefficientA = 0.6;
        const auto plungingCoefficientB = 0.7;
        const auto plungingCoefficientC = 0.8;
        const auto plungingCoefficientN = 0.9;
        const auto surgingCoefficientA = 1.0;
        const auto surgingCoefficientB = 1.1;
        const auto surgingCoefficientC = 1.2;
        const auto surgingCoefficientN = 1.3;
        const auto upperLimitLoadingAul = 1.4;
        const auto upperLimitLoadingBul = 1.5;
        const auto upperLimitLoadingCul = 1.6;
        const auto lowerLimitLoadingAll = 1.7;
        const auto lowerLimitLoadingBll = 1.8;
        const auto lowerLimitLoadingCll = 1.9;
        const auto distanceMaximumWaveElevationAsmax = 2.0;
        const auto distanceMaximumWaveElevationBsmax = 2.1;
        const auto normativeWidthOfWaveImpactAwi = 2.2;
        const auto normativeWidthOfWaveImpactBwi = 2.3;

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            initialDamage, slopeAngle, thicknessTopLayer, relativeDensity);
        naturalStoneConstructionProperties.SetSimilarityParameterThreshold(make_unique<double>(similarityParameterThreshold));
        naturalStoneConstructionProperties.SetPlungingCoefficientA(make_unique<double>(plungingCoefficientA));
        naturalStoneConstructionProperties.SetPlungingCoefficientB(make_unique<double>(plungingCoefficientB));
        naturalStoneConstructionProperties.SetPlungingCoefficientC(make_unique<double>(plungingCoefficientC));
        naturalStoneConstructionProperties.SetPlungingCoefficientN(make_unique<double>(plungingCoefficientN));
        naturalStoneConstructionProperties.SetSurgingCoefficientA(make_unique<double>(surgingCoefficientA));
        naturalStoneConstructionProperties.SetSurgingCoefficientB(make_unique<double>(surgingCoefficientB));
        naturalStoneConstructionProperties.SetSurgingCoefficientC(make_unique<double>(surgingCoefficientC));
        naturalStoneConstructionProperties.SetSurgingCoefficientN(make_unique<double>(surgingCoefficientN));
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

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput =
                dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(&actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        ASSERT_DOUBLE_EQ(initialDamage, locationDependentInput->GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, locationDependentInput->GetSlopeAngle());
        ASSERT_DOUBLE_EQ(relativeDensity, locationDependentInput->GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentInput->GetThicknessTopLayer());

        AssertHydraulicLoads(plungingCoefficientA, plungingCoefficientB, plungingCoefficientC, plungingCoefficientN, surgingCoefficientA,
                             surgingCoefficientB, surgingCoefficientC, surgingCoefficientN, similarityParameterThreshold,
                             locationDependentInput->GetHydraulicLoads());

        AssertUpperLimitLoading(upperLimitLoadingAul, upperLimitLoadingBul, upperLimitLoadingCul, locationDependentInput->GetUpperLimitLoading());

        AssertLowerLimitLoading(lowerLimitLoadingAll, lowerLimitLoadingBll, lowerLimitLoadingCll, locationDependentInput->GetLowerLimitLoading());

        AssertDistanceMaximumWaveElevation(distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax,
                                           locationDependentInput->GetDistanceMaximumWaveElevation());

        AssertNormativeWidthOfWaveImpact(normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi,
                                         locationDependentInput->GetNormativeWidthOfWaveImpact());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;
        const auto relativeDensity = 0.4;

        const NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            initialDamage, slopeAngle, thicknessTopLayer, relativeDensity);

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(&actualLocationDependentInputItems[0].get()
        );
        ASSERT_TRUE(locationDependentInput != nullptr);

        ASSERT_DOUBLE_EQ(initialDamage, locationDependentInput->GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, locationDependentInput->GetSlopeAngle());
        ASSERT_DOUBLE_EQ(relativeDensity, locationDependentInput->GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentInput->GetThicknessTopLayer());

        AssertHydraulicLoads(NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B,
                             NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N,
                             NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B,
                             NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N,
                             NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD, locationDependentInput->GetHydraulicLoads());

        AssertUpperLimitLoading(Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL, Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL,
                                Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL, locationDependentInput->GetUpperLimitLoading());

        AssertLowerLimitLoading(Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL, Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL,
                                Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL, locationDependentInput->GetLowerLimitLoading());

        AssertDistanceMaximumWaveElevation(Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX,
                                           Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX,
                                           locationDependentInput->GetDistanceMaximumWaveElevation());

        AssertNormativeWidthOfWaveImpact(Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI, Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI,
                                         locationDependentInput->GetNormativeWidthOfWaveImpact());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithInvalidTimeSteps_WhenBuild_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Call
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddNotConnectingTimeStep;

        // Assert
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentInput.", "The begin time of an element must connect to the end time of the previous element.");
    }
}

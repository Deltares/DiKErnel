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

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "AssertHelper.h"
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h"
#include "InvalidCalculationDataException.h"
#include "LocationDependentInputAssertHelper.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"
#include "ProfileDataAssertHelper.h"
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

        static void CreateBuilderAndAddAsphaltRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            const auto topLayerType = static_cast<AsphaltRevetmentTopLayerType>(99);
            const AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
                "Test", 0.1, 0.2, 0.3, topLayerType, 0.4, 0.5, 0.6, 0.7, 0.8);

            RevetmentCalculationInputBuilder builder;
            builder.AddAsphaltWaveImpactLocation(constructionProperties);
        }

        static void CreateBuilderAndAddGrassRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties("Test", 0.1, 0.2, topLayerType);

            RevetmentCalculationInputBuilder builder;
            builder.AddGrassWaveImpactLocation(constructionProperties);
        }

        static void CreateBuilderAndAddGrassRevetmentWaveRunupRayleighLocationWithInvalidTopLayerType()
        {
            const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties("Test", 0.1, 0.2, 0.3, topLayerType);

            RevetmentCalculationInputBuilder builder;
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);
        }

        static void CreateBuilderAndAddNaturalStoneRevetmentLocationWithInvalidTopLayerType()
        {
            const auto topLayerType = static_cast<NaturalStoneRevetmentTopLayerType>(99);
            const NaturalStoneRevetmentLocationConstructionProperties constructionProperties("Test", 0.1, 0.2, 0.3, topLayerType, 0.4, 0.5);

            RevetmentCalculationInputBuilder builder;
            builder.AddNaturalStoneLocation(constructionProperties);
        }
    };

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        RevetmentCalculationInputBuilder builder;

        // When
        const auto calculationInput = builder.Build();

        // Then
        const auto& profileData = calculationInput->GetProfileData();
        ASSERT_EQ(0, profileData.GetProfilePoints().size());
        ASSERT_EQ(0, profileData.GetCharacteristicPoints().size());
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());
        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    #pragma region Profile Point

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithDikeProfilePointWithoutCharacteristicPointTypeAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto x = 10;
        const auto z = 20;

        RevetmentCalculationInputBuilder builder;
        builder.AddDikeProfilePoint(x, z, nullptr);

        // When
        const auto calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfilePoints = actualProfileData.GetProfilePoints();
        ASSERT_EQ(1, actualProfilePoints.size());
        ASSERT_EQ(0, actualProfileData.GetCharacteristicPoints().size());

        ProfileDataAssertHelper::AssertProfilePoint(x, z, actualProfilePoints[0]);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithDikeProfilePointWithCharacteristicPointTypeAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto x = 10;
        const auto z = 20;
        const auto characteristicPointType = make_unique<CharacteristicPointType>(CharacteristicPointType::NotchOuterBerm);

        RevetmentCalculationInputBuilder builder;
        builder.AddDikeProfilePoint(x, z, characteristicPointType.get());

        // When
        const auto calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfilePoints = actualProfileData.GetProfilePoints();
        const auto& actualCharacteristicPoints = actualProfileData.GetCharacteristicPoints();
        ASSERT_EQ(1, actualProfilePoints.size());
        ASSERT_EQ(1, actualCharacteristicPoints.size());

        ProfileDataAssertHelper::AssertProfilePoint(x, z, actualProfilePoints[0]);
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualProfilePoints[0], *characteristicPointType, actualCharacteristicPoints[0]);
    }

    #pragma endregion

    #pragma region Time step

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

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilder_WhenAddTimeStepWithInvalidEndTime_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddInvalidTimeStep;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create instance.", "'beginTime' should be smaller than 'endTime'.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithInvalidTimeSteps_WhenBuild_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddNonSuccessiveTimeSteps;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create instance.", "The begin time of a successive element must equal the end time of the previous element.");
    }

    #pragma endregion

    #pragma region Asphalt wave impact

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilder_WhenAddingAsphaltWaveImpactLocationWithInvalidTopLayerType_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action =
                &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddAsphaltRevetmentWaveImpactLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, DefaultsFactoryException>(
            action, "Could not create instance.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        const auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;
        const auto failureTension = 0.4;
        const auto densityOfWater = 0.5;
        const auto soilElasticity = 0.6;
        const auto thicknessUpperLayer = 0.7;
        const auto elasticModulusUpperLayer = 0.8;
        const auto initialDamage = 0.9;
        const auto failureNumber = 1.0;
        const auto thicknessSubLayer = 1.1;
        const auto elasticModulusSubLayer = 1.2;
        const auto averageNumberOfWavesCtm = 1.3;
        const auto fatigueAlpha = 1.4;
        const auto fatigueBeta = 1.5;
        const auto impactNumberC = 1.6;
        const auto stiffnessRelationNu = 1.7;
        const auto widthFactors = vector
        {
            tuple(1.8, 1.9)
        };
        const auto depthFactors = vector
        {
            tuple(2.0, 2.1)
        };
        const auto impactFactors = vector
        {
            tuple(2.2, 2.3)
        };

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, x, tanA, positionZ, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(make_unique<double>(fatigueAlpha));
        constructionProperties.SetFatigueBeta(make_unique<double>(fatigueBeta));
        constructionProperties.SetImpactNumberC(make_unique<double>(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<tuple<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<tuple<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<tuple<double, double>>>(impactFactors));

        RevetmentCalculationInputBuilder builder;
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, failureTension, densityOfWater, soilElasticity, averageNumberOfWavesCtm, impactNumberC, stiffnessRelationNu,
            *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessSubLayer, elasticModulusSubLayer,
                                                                                  locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(fatigueAlpha, fatigueBeta,
                                                                                    locationDependentInput->GetFatigue());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(widthFactors, depthFactors, impactFactors,
                                                                                    *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        const auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;
        const auto failureTension = 0.4;
        const auto densityOfWater = 0.5;
        const auto soilElasticity = 0.6;
        const auto thicknessUpperLayer = 0.7;
        const auto elasticModulusUpperLayer = 0.8;

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, x, tanA, positionZ, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        RevetmentCalculationInputBuilder builder;
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, failureTension, densityOfWater, soilElasticity, 1, 1, 0.35,
            *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(0, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(0.42, 4.76,
                                                                                    locationDependentInput->GetFatigue());

        const auto expectedWidthFactors = vector
        {
            tuple(0.1, 0.0392),
            tuple(0.2, 0.0738),
            tuple(0.3, 0.1002),
            tuple(0.4, 0.1162),
            tuple(0.5, 0.1213),
            tuple(0.6, 0.1168),
            tuple(0.7, 0.1051),
            tuple(0.8, 0.0890),
            tuple(0.9, 0.0712),
            tuple(1.0, 0.0541),
            tuple(1.1, 0.0391),
            tuple(1.2, 0.0269),
            tuple(1.3, 0.0216),
            tuple(1.4, 0.0150),
            tuple(1.5, 0.0105)
        };

        const auto expectedDepthFactors = vector
        {
            tuple(-1.0, 0.0244),
            tuple(-0.875, 0.0544),
            tuple(-0.750, 0.0938),
            tuple(-0.625, 0.1407),
            tuple(-0.500, 0.1801),
            tuple(-0.375, 0.1632),
            tuple(-0.250, 0.1426),
            tuple(-0.125, 0.0994),
            tuple(0.0, 0.06),
            tuple(0.125, 0.0244),
            tuple(0.250, 0.0169)
        };

        const auto expectedImpactFactors = vector
        {
            tuple(2.0, 0.039),
            tuple(2.4, 0.1),
            tuple(2.8, 0.18),
            tuple(3.2, 0.235),
            tuple(3.6, 0.2),
            tuple(4.0, 0.13),
            tuple(4.4, 0.08),
            tuple(4.8, 0.02),
            tuple(5.2, 0.01),
            tuple(5.6, 0.005),
            tuple(6.0, 0.001)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(expectedWidthFactors, expectedDepthFactors,
                                                                                    expectedImpactFactors, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Grass wave impact

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilder_WhenAddingGrassWaveImpactLocationWithInvalidTopLayerType_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddGrassRevetmentWaveImpactLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, DefaultsFactoryException>(
            action, "Could not create instance.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithFullyConfiguredGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        const string name = "Test";
        const auto x = 0.1;
        const auto positionZ = 0.2;
        const auto initialDamage = 0.3;
        const auto failureNumber = 0.4;
        const auto timeLineAgwi = 0.5;
        const auto timeLineBgwi = 0.6;
        const auto timeLineCgwi = 0.7;
        const auto minimumWaveHeightTemax = 0.8;
        const auto maximumWaveHeightTemin = 0.9;
        const auto waveAngleImpactNwa = 1.0;
        const auto waveAngleImpactQwa = 1.1;
        const auto waveAngleImpactRwa = 1.2;
        const auto upperLimitLoadingAul = 1.3;
        const auto lowerLimitLoadingAll = 1.4;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(name, x, positionZ, topLayerType);
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetTimeLineAgwi(make_unique<double>(timeLineAgwi));
        constructionProperties.SetTimeLineBgwi(make_unique<double>(timeLineBgwi));
        constructionProperties.SetTimeLineCgwi(make_unique<double>(timeLineCgwi));
        constructionProperties.SetMinimumWaveHeightTemax(make_unique<double>(minimumWaveHeightTemax));
        constructionProperties.SetMaximumWaveHeightTemin(make_unique<double>(maximumWaveHeightTemin));
        constructionProperties.SetWaveAngleImpactNwa(make_unique<double>(waveAngleImpactNwa));
        constructionProperties.SetWaveAngleImpactQwa(make_unique<double>(waveAngleImpactQwa));
        constructionProperties.SetWaveAngleImpactRwa(make_unique<double>(waveAngleImpactRwa));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveImpactLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, positionZ, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            minimumWaveHeightTemax, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            maximumWaveHeightTemin, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactNwa, waveAngleImpactQwa, waveAngleImpactRwa, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            timeLineAgwi, timeLineBgwi, timeLineCgwi, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            upperLimitLoadingAul, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            lowerLimitLoadingAll, *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        const string name = "Test";
        const auto x = 0.1;
        const auto positionZ = 0.2;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(name, x, positionZ, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveImpactLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, positionZ, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            1, -0.000009722, 0.25, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        const string name = "Test";
        const auto x = 0.1;
        const auto positionZ = 0.2;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(name, x, positionZ, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveImpactLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, positionZ, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.8, -0.00001944, 0.25, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Grass wave run-up Rayleigh

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilder_WhenAddingGrassWaveRunupRayleighLocationWithInvalidTopLayerType_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action =
                &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddGrassRevetmentWaveRunupRayleighLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, DefaultsFactoryException>(
            action, "Could not create instance.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithFullyConfiguredGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;
        const auto initialDamage = 0.4;
        const auto failureNumber = 0.5;
        const auto criticalCumulativeOverload = 0.6;
        const auto criticalFrontVelocity = 0.7;
        const auto increasedLoadTransitionAlphaM = 0.8;
        const auto reducedStrengthTransitionAlphaS = 0.9;
        const auto averageNumberOfWavesCtm = 1.0;
        const auto representativeWaveRunup2PAru = 1.1;
        const auto representativeWaveRunup2PBru = 1.2;
        const auto representativeWaveRunup2PCru = 1.3;
        const auto representativeWaveRunup2PGammab = 1.4;
        const auto representativeWaveRunup2PGammaf = 1.5;
        const auto waveAngleImpactAbeta = 1.6;
        const auto waveAngleImpactBetamax = 1.7;
        const auto fixedNumberOfWaves = 18;
        const auto frontVelocityCu = 1.9;

        GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(name, x, tanA, positionZ, topLayerType);
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetRepresentativeWaveRunup2PAru(make_unique<double>(representativeWaveRunup2PAru));
        constructionProperties.SetRepresentativeWaveRunup2PBru(make_unique<double>(representativeWaveRunup2PBru));
        constructionProperties.SetRepresentativeWaveRunup2PCru(make_unique<double>(representativeWaveRunup2PCru));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(make_unique<double>(representativeWaveRunup2PGammab));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(make_unique<double>(representativeWaveRunup2PGammaf));
        constructionProperties.SetWaveAngleImpactAbeta(make_unique<double>(waveAngleImpactAbeta));
        constructionProperties.SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));
        constructionProperties.SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCu(make_unique<double>(frontVelocityCu));

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            representativeWaveRunup2PAru, representativeWaveRunup2PBru, representativeWaveRunup2PCru,
            representativeWaveRunup2PGammab, representativeWaveRunup2PGammaf, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactAbeta, waveAngleImpactBetamax, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            averageNumberOfWavesCtm, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            criticalCumulativeOverload, fixedNumberOfWaves, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            criticalFrontVelocity, frontVelocityCu, *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;

        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(name, x, tanA, positionZ, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            6.6, 1.1, *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;

        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(name, x, tanA, positionZ, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        // When
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.1, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Natural stone

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilder_WhenAddingNaturalStoneLocationWithInvalidTopLayerType_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddNaturalStoneRevetmentLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, DefaultsFactoryException>(
            action, "Could not create instance.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;
        const auto thicknessTopLayer = 0.4;
        const auto relativeDensity = 0.5;
        const auto initialDamage = 0.6;
        const auto failureNumber = 0.7;
        const auto hydraulicLoadXib = 0.8;
        const auto hydraulicLoadAp = 0.9;
        const auto hydraulicLoadBp = 1.0;
        const auto hydraulicLoadCp = 1.1;
        const auto hydraulicLoadNp = 1.2;
        const auto hydraulicLoadAs = 1.3;
        const auto hydraulicLoadBs = 1.4;
        const auto hydraulicLoadCs = 1.5;
        const auto hydraulicLoadNs = 1.6;
        const auto slopeUpperLevelAus = 1.7;
        const auto slopeLowerLevelAls = 1.8;
        const auto upperLimitLoadingAul = 1.9;
        const auto upperLimitLoadingBul = 2.0;
        const auto upperLimitLoadingCul = 2.1;
        const auto lowerLimitLoadingAll = 2.2;
        const auto lowerLimitLoadingBll = 2.3;
        const auto lowerLimitLoadingCll = 2.4;
        const auto distanceMaximumWaveElevationAsmax = 2.5;
        const auto distanceMaximumWaveElevationBsmax = 2.6;
        const auto normativeWidthOfWaveImpactAwi = 2.7;
        const auto normativeWidthOfWaveImpactBwi = 2.8;
        const auto waveAngleImpactBetamax = 2.9;

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            name, x, tanA, positionZ, topLayerType, thicknessTopLayer, relativeDensity);
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
        naturalStoneConstructionProperties.SetSlopeUpperLevelAus(make_unique<double>(slopeUpperLevelAus));
        naturalStoneConstructionProperties.SetSlopeLowerLevelAus(make_unique<double>(slopeLowerLevelAls));
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

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, relativeDensity, thicknessTopLayer, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            hydraulicLoadAp, hydraulicLoadBp, hydraulicLoadCp, hydraulicLoadNp, hydraulicLoadAs, hydraulicLoadBs,
            hydraulicLoadCs, hydraulicLoadNs, hydraulicLoadXib, locationDependentInput->GetHydraulicLoads());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            slopeUpperLevelAus, slopeLowerLevelAls, locationDependentInput->GetSlope());

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
        const auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        const string name = "Test";
        const auto x = 0.1;
        const auto tanA = 0.2;
        const auto positionZ = 0.3;
        const auto thicknessTopLayer = 0.4;
        const auto relativeDensity = 0.5;

        const NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            name, x, tanA, positionZ, topLayerType, thicknessTopLayer, relativeDensity);

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

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            name, x, tanA, positionZ, relativeDensity, thicknessTopLayer, *locationDependentInput);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInput->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.05, 1.5, locationDependentInput->GetSlope());
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

    #pragma endregion
}

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

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "AssertHelper.h"
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h"
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
        static void CreateBuilderAndAddAsphaltRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<AsphaltRevetmentTopLayerType>(99);
            const AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
                0.1, 0.2, topLayerType, 0.3, 0.4, 0.5, 0.6, 0.7);

            RevetmentCalculationInputBuilder builder;
            builder.AddAsphaltWaveImpactLocation(constructionProperties);
        }

        static void CreateBuilderAndAddGrassRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(0.1, topLayerType);

            RevetmentCalculationInputBuilder builder;
            builder.AddGrassWaveImpactLocation(constructionProperties);
        }

        static void CreateBuilderAndAddGrassRevetmentWaveRunupRayleighLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(0.1, 0.2, topLayerType);

            RevetmentCalculationInputBuilder builder;
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);
        }

        static void CreateBuilderAndAddNaturalStoneRevetmentLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<NaturalStoneRevetmentTopLayerType>(99);
            const NaturalStoneRevetmentLocationConstructionProperties constructionProperties(0.1, topLayerType, 0.2, 0.3);

            RevetmentCalculationInputBuilder builder;
            builder.AddNaturalStoneLocation(constructionProperties);
        }
    };

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        RevetmentCalculationInputBuilder builder;

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& profileData = calculationInput->GetProfileData();
        ASSERT_EQ(0, profileData.GetProfilePoints().size());
        ASSERT_EQ(0, profileData.GetCharacteristicPoints().size());
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());
        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
    }

    #pragma region Profile point

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithDikeProfilePointWithoutCharacteristicPointTypeAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto x = 10;
        constexpr auto z = 20;

        RevetmentCalculationInputBuilder builder;
        builder.AddDikeProfilePoint(x, z, nullptr);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfilePoints = actualProfileData.GetProfilePoints();
        ASSERT_EQ(1, actualProfilePoints.size());
        ASSERT_EQ(0, actualProfileData.GetCharacteristicPoints().size());

        ProfileDataAssertHelper::AssertProfilePoint(x, z, actualProfilePoints.at(0));
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithDikeProfilePointWithCharacteristicPointTypeAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto x = 10;
        constexpr auto z = 20;
        constexpr auto characteristicPointType = CharacteristicPointType::NotchOuterBerm;

        RevetmentCalculationInputBuilder builder;
        builder.AddDikeProfilePoint(x, z, &characteristicPointType);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfilePoints = actualProfileData.GetProfilePoints();
        const auto& actualCharacteristicPoints = actualProfileData.GetCharacteristicPoints();
        ASSERT_EQ(1, actualProfilePoints.size());
        ASSERT_EQ(1, actualCharacteristicPoints.size());

        ProfileDataAssertHelper::AssertProfilePoint(x, z, actualProfilePoints.at(0));
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualProfilePoints.at(0), characteristicPointType, actualCharacteristicPoints.at(0));
    }

    #pragma endregion

    #pragma region Time step

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        constexpr auto waterLevel = 0.1;
        constexpr auto waveHeightHm0 = 0.2;
        constexpr auto wavePeriodTm10 = 0.3;
        constexpr auto waveAngle = 0.4;

        RevetmentCalculationInputBuilder builder;
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualTimeDependentInputItems = calculationInput->GetTimeDependentInputItems();
        ASSERT_EQ(1, actualTimeDependentInputItems.size());
        const auto& timeDependentInput = actualTimeDependentInputItems.at(0).get();

        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle,
                                                                     timeDependentInput);

        ASSERT_EQ(0, calculationInput->GetLocationDependentInputItems().size());
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
        constexpr auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;
        constexpr auto failureTension = 0.3;
        constexpr auto densityOfWater = 0.4;
        constexpr auto soilElasticity = 0.5;
        constexpr auto thicknessUpperLayer = 0.6;
        constexpr auto elasticModulusUpperLayer = 0.7;
        constexpr auto initialDamage = 0.8;
        constexpr auto failureNumber = 0.9;
        constexpr auto thicknessSubLayer = 1.0;
        constexpr auto elasticModulusSubLayer = 1.1;
        constexpr auto averageNumberOfWavesCtm = 1.2;
        constexpr auto fatigueAlpha = 1.3;
        constexpr auto fatigueBeta = 1.4;
        constexpr auto impactNumberC = 1.5;
        constexpr auto stiffnessRelationNu = 1.6;
        const auto widthFactors = vector
        {
            pair(1.7, 1.8)
        };
        const auto depthFactors = vector
        {
            pair(1.9, 2.0)
        };
        const auto impactFactors = vector
        {
            pair(2.1, 2.2)
        };

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            x, outerSlope, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer,
            elasticModulusUpperLayer);

        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(make_unique<double>(fatigueAlpha));
        constructionProperties.SetFatigueBeta(make_unique<double>(fatigueBeta));
        constructionProperties.SetImpactNumberC(make_unique<double>(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<pair<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<pair<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<pair<double, double>>>(impactFactors));

        RevetmentCalculationInputBuilder builder;
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(x, outerSlope, failureTension, densityOfWater,
                                                                                              soilElasticity, averageNumberOfWavesCtm,
                                                                                              impactNumberC, stiffnessRelationNu,
                                                                                              *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessSubLayer, elasticModulusSubLayer,
                                                                                  *locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(fatigueAlpha, fatigueBeta,
                                                                                    locationDependentInput->GetFatigue());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(widthFactors, depthFactors, impactFactors,
                                                                                    *locationDependentInput);
    }

    TEST_F(RevetmentCalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        constexpr auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;
        constexpr auto failureTension = 0.3;
        constexpr auto densityOfWater = 0.4;
        constexpr auto soilElasticity = 0.5;
        constexpr auto thicknessUpperLayer = 0.6;
        constexpr auto elasticModulusUpperLayer = 0.7;

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            x, outerSlope, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer,
            elasticModulusUpperLayer);

        RevetmentCalculationInputBuilder builder;
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(x, outerSlope, failureTension, densityOfWater,
                                                                                              soilElasticity, 1, 1, 0.35, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        ASSERT_EQ(nullptr, locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(0.42, 4.76,
                                                                                    locationDependentInput->GetFatigue());

        const auto expectedWidthFactors = vector
        {
            pair(0.1, 0.0392),
            pair(0.2, 0.0738),
            pair(0.3, 0.1002),
            pair(0.4, 0.1162),
            pair(0.5, 0.1213),
            pair(0.6, 0.1168),
            pair(0.7, 0.1051),
            pair(0.8, 0.0890),
            pair(0.9, 0.0712),
            pair(1.0, 0.0541),
            pair(1.1, 0.0391),
            pair(1.2, 0.0269),
            pair(1.3, 0.0216),
            pair(1.4, 0.0150),
            pair(1.5, 0.0105)
        };

        const auto expectedDepthFactors = vector
        {
            pair(-1.0, 0.0244),
            pair(-0.875, 0.0544),
            pair(-0.750, 0.0938),
            pair(-0.625, 0.1407),
            pair(-0.500, 0.1801),
            pair(-0.375, 0.1632),
            pair(-0.250, 0.1426),
            pair(-0.125, 0.0994),
            pair(0.0, 0.06),
            pair(0.125, 0.0244),
            pair(0.250, 0.0169)
        };

        const auto expectedImpactFactors = vector
        {
            pair(2.0, 0.039),
            pair(2.4, 0.1),
            pair(2.8, 0.18),
            pair(3.2, 0.235),
            pair(3.6, 0.2),
            pair(4.0, 0.13),
            pair(4.4, 0.08),
            pair(4.8, 0.02),
            pair(5.2, 0.01),
            pair(5.6, 0.005),
            pair(6.0, 0.001)
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
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;
        constexpr auto timeLineAgwi = 0.4;
        constexpr auto timeLineBgwi = 0.5;
        constexpr auto timeLineCgwi = 0.6;
        constexpr auto minimumWaveHeightTemax = 0.7;
        constexpr auto maximumWaveHeightTemin = 0.8;
        constexpr auto waveAngleImpactNwa = 0.9;
        constexpr auto waveAngleImpactQwa = 1.0;
        constexpr auto waveAngleImpactRwa = 1.1;
        constexpr auto upperLimitLoadingAul = 1.2;
        constexpr auto lowerLimitLoadingAll = 1.3;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);
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
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

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
        constexpr auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        constexpr auto x = 0.1;

        const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveImpactLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

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
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;

        const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveImpactLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

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
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;
        constexpr auto initialDamage = 0.3;
        constexpr auto failureNumber = 0.4;
        constexpr auto criticalCumulativeOverload = 0.5;
        constexpr auto criticalFrontVelocity = 0.6;
        constexpr auto increasedLoadTransitionAlphaM = 0.7;
        constexpr auto reducedStrengthTransitionAlphaS = 0.8;
        constexpr auto averageNumberOfWavesCtm = 0.9;
        constexpr auto representativeWaveRunup2PAru = 1.0;
        constexpr auto representativeWaveRunup2PBru = 1.1;
        constexpr auto representativeWaveRunup2PCru = 1.2;
        constexpr auto representativeWaveRunup2PGammab = 1.3;
        constexpr auto representativeWaveRunup2PGammaf = 1.4;
        constexpr auto waveAngleImpactAbeta = 1.5;
        constexpr auto waveAngleImpactBetamax = 1.6;
        constexpr auto fixedNumberOfWaves = 17;
        constexpr auto frontVelocityCu = 1.8;

        GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(x, outerSlope, topLayerType);
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
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

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
        constexpr auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;

        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(x, outerSlope, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

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
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;

        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(x, outerSlope, topLayerType);

        RevetmentCalculationInputBuilder builder;
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

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

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            x, topLayerType, thicknessTopLayer, relativeDensity);
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
        naturalStoneConstructionProperties.SetSlopeLowerLevelAls(make_unique<double>(slopeLowerLevelAls));
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
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, relativeDensity, thicknessTopLayer, *locationDependentInput);

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
        constexpr auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        constexpr auto x = 0.1;
        constexpr auto thicknessTopLayer = 0.2;
        constexpr auto relativeDensity = 0.3;

        const NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(
            x, topLayerType, thicknessTopLayer, relativeDensity);

        RevetmentCalculationInputBuilder builder;
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);

        // When
        const auto& calculationInput = builder.Build();

        // Then
        ASSERT_EQ(0, calculationInput->GetTimeDependentInputItems().size());

        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, relativeDensity, thicknessTopLayer, *locationDependentInput);

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

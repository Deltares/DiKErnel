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
#include "CalculationInputBuilder.h"
#include "Calculator.h"
#include "Validator.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct NaturalStoneRevetmentCalculationTest : Test
    {
        #pragma region Schematization 1

        static void ConfigureBuilderForSchematization1(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
        }

        #pragma endregion

        #pragma region Schematization 2

        static void ConfigureBuilderForSchematization2(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 6.4, 1.6);
            builder.AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
            builder.AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(6.4, CharacteristicPointType::CrestOuterBerm);
            builder.AddDikeProfilePointData(12.4, CharacteristicPointType::NotchOuterBerm);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
        }

        #pragma endregion

        #pragma region Schematization 3

        static void ConfigureBuilderForSchematization3(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 6.4, 1.6);
            builder.AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
            builder.AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
        }

        #pragma endregion

        #pragma region Schematization 4

        static void ConfigureBuilderForSchematization4(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 900, 1.27, 1.5, 6, 0);
            builder.AddTimeStep(900, 1800, 1.271, 1.5, 6, 0);
            builder.AddTimeStep(1800, 2700, 1.272, 1.5, 6, 0);
            builder.AddTimeStep(2700, 3600, 1.273, 1.5, 6, 0);
            builder.AddTimeStep(3600, 4500, 2.531, 1.5, 6, 0);
            builder.AddTimeStep(4500, 5400, 2.532, 1.5, 6, 0);
            builder.AddTimeStep(5400, 6300, 2.533, 1.5, 6, 0);
            builder.AddTimeStep(6300, 7200, 2.534, 1.5, 6, 0);
            builder.AddTimeStep(7200, 8100, 2.535, 1.5, 6, 0);
            builder.AddTimeStep(8100, 9000, 2.536, 1.5, 6, 0);
            builder.AddTimeStep(9000, 9900, 2.537, 1.5, 6, 0);
            builder.AddTimeStep(9900, 10800, 2.538, 1.5, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
        }

        #pragma endregion

        static void AssertOutput(
            const Calculator& calculator,
            const double expectedDamage,
            const int* expectedTimeOfFailure = nullptr)
        {
            ASSERT_EQ(CalculationState::FinishedSuccessfully, calculator.GetCalculationState());

            const auto calculatorResult = calculator.GetResult();
            ASSERT_TRUE(calculatorResult->GetSuccessful());
            ASSERT_EQ(0, calculatorResult->GetEvents().size());

            const CalculationOutput* calculationOutput = calculatorResult->GetData();
            const auto& locationDependentOutput = calculationOutput->GetLocationDependentOutputItems().at(0).get();

            const auto actualDamage = locationDependentOutput.GetDamages().back();
            AssertHelper::AssertAreEqualWithAcceptablePrecision(expectedDamage, actualDamage);

            const auto actualTimeOfFailure = locationDependentOutput.GetTimeOfFailure();

            if (expectedTimeOfFailure == nullptr)
            {
                ASSERT_EQ(nullptr, actualTimeOfFailure);
            }
            else
            {
                ASSERT_NE(nullptr, actualTimeOfFailure);
                ASSERT_EQ(*expectedTimeOfFailure, *actualTimeOfFailure);
            }
        }
    };

    #pragma region Schematization 1

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65);

        ConfigureBuilderForSchematization1(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 7283;

        AssertOutput(calculator, 1.2304354560754505, &expectedTimeOfFailure);
    }

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.35, 1.6);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.6));

        ConfigureBuilderForSchematization1(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 6424;

        AssertOutput(calculator, 1.4501773914577867, &expectedTimeOfFailure);
    }

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.25, 1.65);

        locationConstructionProperties->SetHydraulicLoadXib(make_unique<double>(2.1));
        locationConstructionProperties->SetHydraulicLoadAp(make_unique<double>(6.68));
        locationConstructionProperties->SetHydraulicLoadBp(make_unique<double>(0));
        locationConstructionProperties->SetHydraulicLoadCp(make_unique<double>(0));
        locationConstructionProperties->SetHydraulicLoadNp(make_unique<double>(-0.723));
        locationConstructionProperties->SetHydraulicLoadAs(make_unique<double>(12));
        locationConstructionProperties->SetHydraulicLoadBs(make_unique<double>(1.5));
        locationConstructionProperties->SetHydraulicLoadCs(make_unique<double>(-3.12));
        locationConstructionProperties->SetHydraulicLoadNs(make_unique<double>(-1.5));

        ConfigureBuilderForSchematization1(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 7815;

        AssertOutput(calculator, 1.071392516159668, &expectedTimeOfFailure);
    }

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65);

        locationConstructionProperties->SetWaveAngleImpactBetamax(make_unique<double>(30));

        ConfigureBuilderForSchematization1(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 7272;

        AssertOutput(calculator, 1.2313943804174021, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 2

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

        ConfigureBuilderForSchematization2(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 5606;

        AssertOutput(calculator, 1.6908069656687659, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 3

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

        ConfigureBuilderForSchematization3(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 7942;

        AssertOutput(calculator, 1.1900709659898594, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 4

    TEST_F(NaturalStoneRevetmentCalculationTest,
           GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            6, NaturalStoneRevetmentTopLayerType::NordicStone, 0.3, 1.65);

        locationConstructionProperties->SetUpperLimitLoadingAul(make_unique<double>(0.08));
        locationConstructionProperties->SetUpperLimitLoadingBul(make_unique<double>(0.7));
        locationConstructionProperties->SetUpperLimitLoadingCul(make_unique<double>(3.5));
        locationConstructionProperties->SetLowerLimitLoadingAll(make_unique<double>(0.08));
        locationConstructionProperties->SetLowerLimitLoadingBll(make_unique<double>(0.15));
        locationConstructionProperties->SetLowerLimitLoadingCll(make_unique<double>(5.5));
        locationConstructionProperties->SetDistanceMaximumWaveElevationAsmax(make_unique<double>(0.5));
        locationConstructionProperties->SetDistanceMaximumWaveElevationBsmax(make_unique<double>(0.8));
        locationConstructionProperties->SetNormativeWidthOfWaveImpactAwi(make_unique<double>(1.1));
        locationConstructionProperties->SetNormativeWidthOfWaveImpactBwi(make_unique<double>(0.15));

        ConfigureBuilderForSchematization4(builder);

        builder.AddNaturalStoneLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 3894;

        AssertOutput(calculator, 1.0994145971228768, &expectedTimeOfFailure);
    }

    #pragma endregion
}

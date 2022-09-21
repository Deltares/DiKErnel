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

    struct GrassRevetmentOvertoppingCalculationTest : Test
    {
        const vector<double> _roughnessCoefficientsForSchematization1
        {
            1,
            1,
            0.75,
            0.5,
            0.8,
            0.8,
            0.8,
            0.8,
            0.8,
            0.8
        };

        void ConfigureBuilderForSchematization1(
            CalculationInputBuilder& builder) const
        {
            builder.AddTimeStep(0, 3600, 5.5, 1.9, 4.7, -10);
            builder.AddTimeStep(3600, 7200, 5.6, 1.95, 4.73, -8);
            builder.AddTimeStep(7200, 10800, 5.7, 2, 4.76, -6);
            builder.AddTimeStep(10800, 14400, 5.8, 2.05, 4.79, -4);
            builder.AddTimeStep(14400, 18000, 5.9, 2.1, 4.82, -2);
            builder.AddTimeStep(18000, 21600, 6, 2.15, 4.85, 0);
            builder.AddTimeStep(21600, 25200, 6.1, 2.2, 4.88, 2);
            builder.AddTimeStep(25200, 28800, 6.2, 2.25, 4.91, 4);
            builder.AddTimeStep(28800, 32400, 6.2, 2.3, 4.94, 6);
            builder.AddTimeStep(32400, 36000, 6.1, 2.35, 4.97, 8);
            builder.AddTimeStep(36000, 39600, 6, 2.4, 5, 10);
            builder.AddTimeStep(39600, 43200, 5.9, 2.45, 5.03, 12);
            builder.AddTimeStep(43200, 46800, 5.8, 2.5, 5.06, 14);
            builder.AddTimeStep(46800, 50400, 5.7, 2.55, 5.09, 16);
            builder.AddTimeStep(50400, 54000, 5.6, 2.6, 5.12, 18);
            builder.AddTimeStep(54000, 57600, 5.5, 2.65, 5.15, 20);

            builder.AddDikeProfileSegment(0, -0.1, 5, 0, &_roughnessCoefficientsForSchematization1.at(0));
            builder.AddDikeProfileSegment(5, 0, 15, 3, &_roughnessCoefficientsForSchematization1.at(1));
            builder.AddDikeProfileSegment(15, 3, 22, 3.2, &_roughnessCoefficientsForSchematization1.at(2));
            builder.AddDikeProfileSegment(22, 3.2, 30, 7.5, &_roughnessCoefficientsForSchematization1.at(3));
            builder.AddDikeProfileSegment(30, 7.5, 31, 7.6, &_roughnessCoefficientsForSchematization1.at(4));
            builder.AddDikeProfileSegment(31, 7.6, 34, 7.7, &_roughnessCoefficientsForSchematization1.at(5));
            builder.AddDikeProfileSegment(34, 7.7, 35, 7.4, &_roughnessCoefficientsForSchematization1.at(6));
            builder.AddDikeProfileSegment(35, 7.4, 45, 5, &_roughnessCoefficientsForSchematization1.at(7));
            builder.AddDikeProfileSegment(45, 5, 60, 0.5, &_roughnessCoefficientsForSchematization1.at(8));
            builder.AddDikeProfileSegment(60, 0.5, 70, 0.5, &_roughnessCoefficientsForSchematization1.at(9));

            builder.AddDikeProfilePointData(5, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(15, CharacteristicPointType::CrestOuterBerm);
            builder.AddDikeProfilePointData(22, CharacteristicPointType::NotchOuterBerm);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
            builder.AddDikeProfilePointData(35, CharacteristicPointType::InnerCrest);
            builder.AddDikeProfilePointData(60, CharacteristicPointType::InnerToe);
        }

        [[nodiscard]]
        unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> CreateLocationConstructionPropertiesForSchematization1(
            double x) const
        {
            auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
                x, GrassRevetmentTopLayerType::ClosedSod);

            locationConstructionProperties->SetInitialDamage(make_unique<double>(0.02));
            locationConstructionProperties->SetFailureNumber(make_unique<double>(1));
            locationConstructionProperties->SetCriticalCumulativeOverload(make_unique<double>(7000));
            locationConstructionProperties->SetCriticalFrontVelocity(make_unique<double>(6.6));
            locationConstructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(1));
            locationConstructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(1));
            locationConstructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0.92));
            locationConstructionProperties->SetFixedNumberOfWaves(make_unique<int>(10000));
            locationConstructionProperties->SetFrontVelocityCwo(make_unique<double>(1.45));
            locationConstructionProperties->SetAccelerationAlphaAForCrest(make_unique<double>(1));
            locationConstructionProperties->SetAccelerationAlphaAForInnerSlope(make_unique<double>(1.4));

            return locationConstructionProperties;
        }

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

            const auto actualDamage = locationDependentOutput.GetTimeDependentOutputItems().back().get().GetDamage();
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

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1TestCase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = CreateLocationConstructionPropertiesForSchematization1(50);

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 33913;

        AssertOutput(calculator, 1.48214256643614, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1TestCase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = CreateLocationConstructionPropertiesForSchematization1(33);

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        AssertOutput(calculator, 0.0751492271841895);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1TestCase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = CreateLocationConstructionPropertiesForSchematization1(33);

        locationConstructionProperties->SetDikeHeight(make_unique<double>(8));

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        AssertOutput(calculator, 0.0403132797601268);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1TestCase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = CreateLocationConstructionPropertiesForSchematization1(33);

        locationConstructionProperties->SetDikeHeight(make_unique<double>(5.65));

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        AssertOutput(calculator, 0.360805793202144);
    }
}

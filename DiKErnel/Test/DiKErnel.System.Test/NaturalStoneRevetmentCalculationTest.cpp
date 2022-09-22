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
            builder.AddTimeStep(0, 900, 1.4, 1.0, 5.5, 30.00);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6.0, 60.00);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90.00);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7.0, 75.00);
            builder.AddTimeStep(3600, 4500, 2.0, 1.4, 7.0, 60.00);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45.00);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8.0, 30.00);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8.0, 15.00);
            builder.AddTimeStep(7200, 8100, 2.0, 2.4, 8.5, 0.0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8.0, 0.0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7.0, 0.0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6.0, 0.0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
        }

        #pragma endregion

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
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 7283;

        AssertOutput(calculator, 1.2304354560754505, &expectedTimeOfFailure);
    }

    #pragma endregion
}

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

    struct GrassRevetmentWaveRunupRayleighCalculationTest : Test
    {
        #pragma region Schematization 1

        static void ConfigureBuilderForSchematization1(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 3600, 0, 0.5, 3, 500);
            builder.AddTimeStep(3600, 7200, 0.1, 0.7, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 0.2, 1, 4, 40);
            builder.AddTimeStep(10800, 14400, 0.3, 1.3, 4.3, 35);
            builder.AddTimeStep(14400, 18000, 0.4, 1.5, 4.5, 30);
            builder.AddTimeStep(18000, 21600, 0.5, 1.8, 4.8, 25);
            builder.AddTimeStep(21600, 25200, 0.6, 2.1, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 0.7, 2.5, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 0.7, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 0.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 0.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 0.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 0.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 0.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 0.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 0, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(25, CharacteristicPointType::OuterCrest);
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

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 40451;

        AssertOutput(calculator, 1.1742487455486512, &expectedTimeOfFailure);
    }

    #pragma endregion
}

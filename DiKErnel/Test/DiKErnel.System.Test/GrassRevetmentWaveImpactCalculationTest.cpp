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

    struct GrassRevetmentWaveImpactCalculationTest : Test
    {
        #pragma region Schematization 1

        static void ConfigureBuilderForSchematization1(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 900, 0.5, 0.5, 3, 0);
            builder.AddTimeStep(900, 1800, 0.55, 0.6, 3, 15);
            builder.AddTimeStep(1800, 2700, 0.6, 0.65, 3, 30);
            builder.AddTimeStep(2700, 3600, 0.65, 0.7, 3, 45);
            builder.AddTimeStep(3600, 4500, 0.7, 0.75, 3, 60);
            builder.AddTimeStep(4500, 5400, 0.75, 0.8, 3, 70);
            builder.AddTimeStep(5400, 6300, 0.8, 0.85, 3, 75);
            builder.AddTimeStep(6300, 7200, 0.85, 0.9, 3, 70);
            builder.AddTimeStep(7200, 8100, 0.9, 0.95, 3, 60);
            builder.AddTimeStep(8100, 9000, 0.95, 1, 3, 45);
            builder.AddTimeStep(9000, 9900, 1, 1.1, 3, 30);
            builder.AddTimeStep(9900, 10800, 1.03, 1.1, 3, 15);
            builder.AddTimeStep(10800, 11700, 1.03, 1.15, 3, 0);
            builder.AddTimeStep(11700, 12600, 1, 1.2, 3, 0);
            builder.AddTimeStep(12600, 13500, 0.95, 1.23, 3, 0);
            builder.AddTimeStep(13500, 14400, 0.9, 1.2, 3, 0);
            builder.AddTimeStep(14400, 15300, 0.85, 1.15, 3, 0);
            builder.AddTimeStep(15300, 16200, 0.8, 1.1, 3, 0);
            builder.AddTimeStep(16200, 17100, 0.75, 1, 3, 0);
            builder.AddTimeStep(17100, 18000, 0.7, 1, 3, 0);
            builder.AddTimeStep(18000, 18900, 0.65, 0.95, 3, 0);
            builder.AddTimeStep(18900, 19800, 0.6, 0.95, 3, 0);
            builder.AddTimeStep(19800, 20700, 0.55, 0.9, 3, 0);
            builder.AddTimeStep(20700, 21600, 0.5, 0.9, 3, 0);

            builder.AddDikeProfileSegment(5, -1.0, 55, 11.5);

            builder.AddDikeProfilePointData(5, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(55, CharacteristicPointType::OuterCrest);
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

    TEST_F(GrassRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            11, GrassRevetmentTopLayerType::ClosedSod);

        ConfigureBuilderForSchematization1(builder);

        builder.AddGrassWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput->GetData());
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 14375;

        AssertOutput(calculator, 1.2922807852067086, &expectedTimeOfFailure);
    }

    #pragma endregion
}

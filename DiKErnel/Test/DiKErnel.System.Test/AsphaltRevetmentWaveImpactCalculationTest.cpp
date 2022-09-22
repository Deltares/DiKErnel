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

    struct AsphaltRevetmentWaveImpactCalculationTest : Test
    {
        #pragma region Schematization 1

        static void ConfigureBuilderForSchematization1(
            CalculationInputBuilder& builder)
        {
            builder.AddTimeStep(0, 3600, 2, 1, 4, 0);
            builder.AddTimeStep(3600, 7200, 2.2, 1.5, 5, 0);
            builder.AddTimeStep(7200, 10800, 2.4, 2, 5.5, 0);
            builder.AddTimeStep(10800, 14400, 2.6, 2.4, 6, 0);
            builder.AddTimeStep(14400, 18000, 2.8, 2.5, 6.2, 0);
            builder.AddTimeStep(18000, 21600, 3, 2.6, 6.3, 0);
            builder.AddTimeStep(21600, 25200, 2.8, 2.7, 6.5, 0);
            builder.AddTimeStep(25200, 28800, 2.6, 2.6, 6.6, 0);
            builder.AddTimeStep(28800, 32400, 2.4, 2.5, 6.3, 0);
            builder.AddTimeStep(32400, 36000, 2, 2.4, 6.2, 0);

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

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        CalculationInputBuilder builder;

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10.0, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

        ConfigureBuilderForSchematization1(builder);

        builder.AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        // Then
        constexpr int expectedTimeOfFailure = 25720;

        AssertOutput(calculator, 1.129939525442647, &expectedTimeOfFailure);
    }

    #pragma endregion
}

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

#include "AssertHelper.h"
#include "CalculationInputBuilder.h"
#include "CalculationTestBase.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct GrassRevetmentOvertoppingCalculationTest : CalculationTestBase
    {
        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization1()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 5.5, 1.9, 4.7, -10);
            builder->AddTimeStep(3600, 7200, 5.6, 1.95, 4.73, -8);
            builder->AddTimeStep(7200, 10800, 5.7, 2, 4.76, -6);
            builder->AddTimeStep(10800, 14400, 5.8, 2.05, 4.79, -4);
            builder->AddTimeStep(14400, 18000, 5.9, 2.1, 4.82, -2);
            builder->AddTimeStep(18000, 21600, 6, 2.15, 4.85, 0);
            builder->AddTimeStep(21600, 25200, 6.1, 2.2, 4.88, 2);
            builder->AddTimeStep(25200, 28800, 6.2, 2.25, 4.91, 4);
            builder->AddTimeStep(28800, 32400, 6.2, 2.3, 4.94, 6);
            builder->AddTimeStep(32400, 36000, 6.1, 2.35, 4.97, 8);
            builder->AddTimeStep(36000, 39600, 6, 2.4, 5, 10);
            builder->AddTimeStep(39600, 43200, 5.9, 2.45, 5.03, 12);
            builder->AddTimeStep(43200, 46800, 5.8, 2.5, 5.06, 14);
            builder->AddTimeStep(46800, 50400, 5.7, 2.55, 5.09, 16);
            builder->AddTimeStep(50400, 54000, 5.6, 2.6, 5.12, 18);
            builder->AddTimeStep(54000, 57600, 5.5, 2.65, 5.15, 20);

            builder->AddDikeProfileSegment(0, -0.1, 5, 0, 1);
            builder->AddDikeProfileSegment(5, 0, 15, 3, 1);
            builder->AddDikeProfileSegment(15, 3, 22, 3.2, 0.75);
            builder->AddDikeProfileSegment(22, 3.2, 30, 7.5, 0.5);
            builder->AddDikeProfileSegment(30, 7.5, 31, 7.6, 0.8);
            builder->AddDikeProfileSegment(31, 7.6, 34, 7.7, 0.8);
            builder->AddDikeProfileSegment(34, 7.7, 35, 7.4, 0.8);
            builder->AddDikeProfileSegment(35, 7.4, 45, 5, 0.8);
            builder->AddDikeProfileSegment(45, 5, 60, 0.5, 0.8);
            builder->AddDikeProfileSegment(60, 0.5, 70, 0.5, 0.8);

            builder->AddDikeProfilePointData(5, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(15, CharacteristicPointType::CrestOuterBerm);
            builder->AddDikeProfilePointData(22, CharacteristicPointType::NotchOuterBerm);
            builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
            builder->AddDikeProfilePointData(35, CharacteristicPointType::InnerCrest);
            builder->AddDikeProfilePointData(60, CharacteristicPointType::InnerToe);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization2()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 5, 2.35, 5.2, -10);
            builder->AddTimeStep(3600, 7200, 5.1, 2.4, 5.23, -8);
            builder->AddTimeStep(7200, 10800, 5.2, 2.45, 5.26, -6);
            builder->AddTimeStep(10800, 14400, 5.3, 2.5, 5.29, -4);
            builder->AddTimeStep(14400, 18000, 5.4, 2.55, 5.32, -2);
            builder->AddTimeStep(18000, 21600, 5.5, 2.6, 5.35, 0);
            builder->AddTimeStep(21600, 25200, 5.6, 2.65, 5.38, 2);
            builder->AddTimeStep(25200, 28800, 5.7, 2.7, 5.41, 4);
            builder->AddTimeStep(28800, 32400, 5.7, 2.75, 5.44, 6);
            builder->AddTimeStep(32400, 36000, 5.6, 2.8, 5.47, 8);
            builder->AddTimeStep(36000, 39600, 5.5, 2.85, 5.5, 10);
            builder->AddTimeStep(39600, 43200, 5.4, 2.9, 5.53, 12);
            builder->AddTimeStep(43200, 46800, 5.3, 2.95, 5.56, 14);
            builder->AddTimeStep(46800, 50400, 5.2, 3, 5.59, 16);
            builder->AddTimeStep(50400, 54000, 5.1, 3.05, 5.62, 18);
            builder->AddTimeStep(54000, 57600, 5, 3.1, 5.65, 20);

            builder->AddDikeProfileSegment(0, -0.1, 5, 0, 1);
            builder->AddDikeProfileSegment(5, 0, 30, 7.5, 1);
            builder->AddDikeProfileSegment(30, 7.5, 31, 7.6, 0.8);
            builder->AddDikeProfileSegment(31, 7.6, 34, 7.7, 0.8);
            builder->AddDikeProfileSegment(34, 7.7, 35, 7.4, 0.8);
            builder->AddDikeProfileSegment(35, 7.4, 45, 5, 0.8);
            builder->AddDikeProfileSegment(45, 5, 60, 0.5, 0.8);
            builder->AddDikeProfileSegment(60, 0.5, 70, 0.5, 0.8);

            builder->AddDikeProfilePointData(5, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);
            builder->AddDikeProfilePointData(35, CharacteristicPointType::InnerCrest);
            builder->AddDikeProfilePointData(60, CharacteristicPointType::InnerToe);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization3()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 5.7, 2.05, 5.2, -10);
            builder->AddTimeStep(3600, 7200, 6.2, 2.1, 5.23, -8);
            builder->AddTimeStep(7200, 10800, 6.8, 2.15, 5.26, -6);
            builder->AddTimeStep(10800, 14400, 6.8, 2.2, 5.29, -4);
            builder->AddTimeStep(14400, 21600, 6.8, 2.25, 5.32, -2);
            builder->AddTimeStep(21600, 32400, 6.7, 2.3, 5.35, 0);
            builder->AddTimeStep(32400, 46800, 6.6, 2.35, 5.38, 2);
            builder->AddTimeStep(46800, 50400, 6.4, 2.4, 5.41, 4);
            builder->AddTimeStep(50400, 54000, 6.2, 2.45, 5.44, 6);
            builder->AddTimeStep(54000, 57600, 6.1, 2.5, 5.47, 8);
            builder->AddTimeStep(57600, 75600, 6, 2.55, 5.5, 10);
            builder->AddTimeStep(75600, 79200, 5.7, 2.6, 5.53, 12);

            builder->AddDikeProfileSegment(-5, -4, -1.73, -2.89, 1);
            builder->AddDikeProfileSegment(-1.73, -2.89, 33.82, 6.03, 1);
            builder->AddDikeProfileSegment(33.82, 6.03, 38.16, 6.31, 0.9);
            builder->AddDikeProfileSegment(38.16, 6.31, 47.34, 8.64, 0.8);
            builder->AddDikeProfileSegment(47.34, 8.64, 52, 8.7, 1);
            builder->AddDikeProfileSegment(52, 8.7, 70, 5, 1);
            builder->AddDikeProfileSegment(70, 5, 85, 1, 1);
            builder->AddDikeProfileSegment(85, 1, 95, 0, 1);

            builder->AddDikeProfilePointData(-1.73, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(33.82, CharacteristicPointType::CrestOuterBerm);
            builder->AddDikeProfilePointData(38.16, CharacteristicPointType::NotchOuterBerm);
            builder->AddDikeProfilePointData(47.34, CharacteristicPointType::OuterCrest);
            builder->AddDikeProfilePointData(52, CharacteristicPointType::InnerCrest);
            builder->AddDikeProfilePointData(85, CharacteristicPointType::InnerToe);

            return builder;
        }
    };

    #pragma region Schematization 1

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            50, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.02));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 33913;

        AssertOutput(*calculator, 1.48214256643614, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            33, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.02));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.0751490475083924);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            33, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.02));
        locationConstructionProperties->SetDikeHeight(make_unique<double>(8));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.0403132797601268);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            33, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.02));
        locationConstructionProperties->SetDikeHeight(make_unique<double>(5.65));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.360805793202144);
    }

    #pragma endregion

    #pragma region Schematization 2

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            40, GrassRevetmentTopLayerType::OpenSod);

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 5311;

        AssertOutput(*calculator, 24.68131275788636, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            30, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetDikeHeight(make_unique<double>(9.5));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.868617343967244);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            35, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(1.2));
        locationConstructionProperties->SetDikeHeight(make_unique<double>(9.6));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 51672;

        AssertOutput(*calculator, 1.11910058435611, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            35, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(1.2));
        locationConstructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(1.3));
        locationConstructionProperties->SetFixedNumberOfWaves(make_unique<int>(5000));
        locationConstructionProperties->SetDikeHeight(make_unique<double>(9.7));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.688425139553067);
    }

    #pragma endregion

    #pragma region Schematization 3

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            60, GrassRevetmentTopLayerType::OpenSod);

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 33915;

        AssertOutput(*calculator, 1.99284873782755, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization3Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            50, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetDikeHeight(make_unique<double>(6.7));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 23118;

        AssertOutput(*calculator, 12.994355885402687, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization3Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            50, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.9));
        locationConstructionProperties->SetFixedNumberOfWaves(make_unique<int>(15000));
        locationConstructionProperties->SetDikeHeight(make_unique<double>(9));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 48552;

        AssertOutput(*calculator, 1.03611132410722, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentOvertoppingCalculationTest,
           GivenCalculationInputForSchematization3Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            50, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetCriticalCumulativeOverload(make_unique<double>(7500));
        locationConstructionProperties->SetCriticalFrontVelocity(make_unique<double>(5.5));
        locationConstructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(1.25));
        locationConstructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(1.33));
        locationConstructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0.85));
        locationConstructionProperties->SetFixedNumberOfWaves(make_unique<int>(15000));
        locationConstructionProperties->SetFrontVelocityCwo(make_unique<double>(1.6));
        locationConstructionProperties->SetAccelerationAlphaAForCrest(make_unique<double>(1.1));
        locationConstructionProperties->SetAccelerationAlphaAForInnerSlope(make_unique<double>(1.5));

        builder->AddGrassOvertoppingLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        AssertOutput(*calculator, 0.407672739747293);
    }

    #pragma endregion
}

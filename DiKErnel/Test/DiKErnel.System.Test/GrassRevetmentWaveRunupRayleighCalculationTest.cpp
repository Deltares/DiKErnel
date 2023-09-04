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

    struct GrassRevetmentWaveRunupRayleighCalculationTest : CalculationTestBase
    {
        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization1()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 0, 0.5, 3, 50);
            builder->AddTimeStep(3600, 7200, 0.1, 0.7, 3.5, 45);
            builder->AddTimeStep(7200, 10800, 0.2, 1, 4, 40);
            builder->AddTimeStep(10800, 14400, 0.3, 1.3, 4.3, 35);
            builder->AddTimeStep(14400, 18000, 0.4, 1.5, 4.5, 30);
            builder->AddTimeStep(18000, 21600, 0.5, 1.8, 4.8, 25);
            builder->AddTimeStep(21600, 25200, 0.6, 2.1, 5.2, 20);
            builder->AddTimeStep(25200, 28800, 0.7, 2.5, 5.5, 15);
            builder->AddTimeStep(28800, 32400, 0.7, 2.8, 5.8, 10);
            builder->AddTimeStep(32400, 36000, 0.6, 2.8, 6, 5);
            builder->AddTimeStep(36000, 39600, 0.5, 2.5, 6, 0);
            builder->AddTimeStep(39600, 43200, 0.4, 2.1, 5.8, 0);
            builder->AddTimeStep(43200, 46800, 0.3, 1.8, 5.5, 5);
            builder->AddTimeStep(46800, 50400, 0.2, 1.5, 5.2, 10);
            builder->AddTimeStep(50400, 54000, 0.1, 1.3, 4.8, 15);
            builder->AddTimeStep(54000, 57600, 0, 1, 4.5, 20);

            builder->AddDikeProfileSegment(0, 0, 25, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(25, CharacteristicPointType::OuterCrest);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization2()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 0, 0.3, 3, 50);
            builder->AddTimeStep(3600, 7200, 0.1, 0.4, 3.5, 45);
            builder->AddTimeStep(7200, 10800, 0.2, 0.5, 3.9, 40);
            builder->AddTimeStep(10800, 14400, 0.3, 0.6, 4.2, 35);
            builder->AddTimeStep(14400, 18000, 0.4, 0.7, 4.6, 30);
            builder->AddTimeStep(18000, 21600, 0.5, 0.8, 4.9, 25);
            builder->AddTimeStep(21600, 25200, 0.6, 0.9, 5.2, 20);
            builder->AddTimeStep(25200, 28800, 0.7, 1, 5.5, 15);
            builder->AddTimeStep(28800, 32400, 0.7, 1.1, 5.7, 10);
            builder->AddTimeStep(32400, 36000, 0.6, 1.1, 5.7, 5);
            builder->AddTimeStep(36000, 39600, 0.5, 1, 5.5, 0);
            builder->AddTimeStep(39600, 43200, 0.4, 0.9, 5.2, 0);
            builder->AddTimeStep(43200, 46800, 0.3, 0.8, 4.9, 5);
            builder->AddTimeStep(46800, 50400, 0.2, 0.7, 4.6, 10);
            builder->AddTimeStep(50400, 54000, 0.1, 0.6, 4.2, 15);
            builder->AddTimeStep(54000, 57600, 0, 0.5, 3.9, 20);

            builder->AddDikeProfileSegment(0, 0, 25, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(25, CharacteristicPointType::OuterCrest);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization3()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 0.5, 2.4, 4, 20);
            builder->AddTimeStep(3600, 7200, 0.6, 2.5, 4.2, 20);
            builder->AddTimeStep(7200, 10800, 0.7, 2.7, 4.4, 20);
            builder->AddTimeStep(10800, 14400, 0.8, 2.8, 4.5, 20);
            builder->AddTimeStep(14400, 18000, 0.9, 2.9, 4.8, 20);
            builder->AddTimeStep(18000, 21600, 0.95, 3, 5, 20);
            builder->AddTimeStep(21600, 25200, 1, 2.9, 5.2, 20);
            builder->AddTimeStep(25200, 28800, 0.95, 2.9, 5.5, 15);
            builder->AddTimeStep(28800, 32400, 0.8, 2.8, 5.8, 10);
            builder->AddTimeStep(32400, 36000, 0.6, 2.8, 6, 5);
            builder->AddTimeStep(36000, 39600, 0.5, 2.5, 6, 0);
            builder->AddTimeStep(39600, 43200, 0.4, 2.1, 5.8, 0);
            builder->AddTimeStep(43200, 46800, 0.3, 1.8, 5.5, 5);
            builder->AddTimeStep(46800, 50400, 0.2, 1.5, 5.2, 10);
            builder->AddTimeStep(50400, 54000, 0.1, 1.3, 4.8, 15);
            builder->AddTimeStep(54000, 57600, 0, 1, 4.5, 20);

            builder->AddDikeProfileSegment(0, 0, 25, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(25, CharacteristicPointType::OuterCrest);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization4()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(-7200, -6840, 0, 0.5, 3, 50);
            builder->AddTimeStep(-6840, -6120, 0.1, 0.7, 3.5, 45);
            builder->AddTimeStep(-6120, -5040, 0.2, 1, 4, 40);
            builder->AddTimeStep(-5040, -3600, 0.3, 1.3, 4.3, 35);
            builder->AddTimeStep(-3600, -1800, 0.4, 1.5, 4.5, 30);
            builder->AddTimeStep(-1800, 360, 0.5, 1.8, 4.8, 25);
            builder->AddTimeStep(360, 2880, 0.6, 2.1, 5.2, 20);
            builder->AddTimeStep(2880, 5760, 0.7, 2.5, 5.5, 15);
            builder->AddTimeStep(5760, 9000, 0.7, 2.8, 5.8, 10);
            builder->AddTimeStep(9000, 12600, 0.6, 2.8, 6, 5);
            builder->AddTimeStep(12600, 16560, 0.5, 2.5, 6, 0);
            builder->AddTimeStep(16560, 20880, 0.4, 2.1, 5.8, 0);
            builder->AddTimeStep(20880, 25560, 0.3, 1.8, 5.5, 5);
            builder->AddTimeStep(25560, 30600, 0.2, 1.5, 5.2, 10);
            builder->AddTimeStep(30600, 36000, 0.1, 1.3, 4.8, 15);
            builder->AddTimeStep(36000, 43200, 0, 1, 4.5, 20);

            builder->AddDikeProfileSegment(0, 0, 25, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(25, CharacteristicPointType::OuterCrest);

            return builder;
        }
    };

    #pragma region Schematization 1

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 40451;

        AssertOutput(*calculator, 1.1742487455486512, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetCriticalCumulativeOverload(make_unique<double>(8000));
        locationConstructionProperties->SetCriticalFrontVelocity(make_unique<double>(6.2));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 35682;

        AssertOutput(*calculator, 1.6764562740432805, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetFixedNumberOfWaves(make_unique<int>(500));
        locationConstructionProperties->SetFrontVelocityCu(make_unique<double>(1.15));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 35036;

        AssertOutput(*calculator, 1.7908078432838237, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetRepresentativeWaveRunup2PAru(make_unique<double>(1.75));
        locationConstructionProperties->SetRepresentativeWaveRunup2PBru(make_unique<double>(4.3));
        locationConstructionProperties->SetRepresentativeWaveRunup2PCru(make_unique<double>(1.6));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 36169;

        AssertOutput(*calculator, 1.5850428483268622, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::OpenSod);

        locationConstructionProperties->SetRepresentativeWaveRunup2PGammab(make_unique<double>(0.7));
        locationConstructionProperties->SetRepresentativeWaveRunup2PGammaf(make_unique<double>(0.7));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 53050;

        AssertOutput(*calculator, 1.0023806278765424, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetWaveAngleImpactAbeta(make_unique<double>(0.0033));
        locationConstructionProperties->SetWaveAngleImpactBetamax(make_unique<double>(30));
        locationConstructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(1));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 45518;

        AssertOutput(*calculator, 1.0341102733139473, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.3));
        locationConstructionProperties->SetFailureNumber(make_unique<double>(1.1));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 36979;

        AssertOutput(*calculator, 1.4742487455486513, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 2

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::OpenSod);

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 35962;

        AssertOutput(*calculator, 1.5248462052078153, &expectedTimeOfFailure);
    }

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        locationConstructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(1.8));
        locationConstructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(0.9));

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 35645;

        AssertOutput(*calculator, 1.5190845530717538, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 3

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 42138;

        AssertOutput(*calculator, 1.114009765223331, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 4

    TEST_F(GrassRevetmentWaveRunupRayleighCalculationTest,
           GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization4();

        auto locationConstructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            3, 0.3, GrassRevetmentTopLayerType::ClosedSod);

        builder->AddGrassWaveRunupRayleighLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const auto calculator = PerformTest(*calculationInput->GetData(),
            UnitTest::GetInstance()->current_test_info()->test_suite_name(),
            UnitTest::GetInstance()->current_test_info()->name());

        // Then
        constexpr int expectedTimeOfFailure = 18856;

        AssertOutput(*calculator, 1.1736314282928013, &expectedTimeOfFailure);
    }

    #pragma endregion
}

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

    struct AsphaltRevetmentWaveImpactCalculationTest : CalculationTestBase
    {
        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization1()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 2, 1, 4, 0);
            builder->AddTimeStep(3600, 7200, 2.2, 1.5, 5, 0);
            builder->AddTimeStep(7200, 10800, 2.4, 2, 5.5, 0);
            builder->AddTimeStep(10800, 14400, 2.6, 2.4, 6, 0);
            builder->AddTimeStep(14400, 18000, 2.8, 2.5, 6.2, 0);
            builder->AddTimeStep(18000, 21600, 3, 2.6, 6.3, 0);
            builder->AddTimeStep(21600, 25200, 2.8, 2.7, 6.5, 0);
            builder->AddTimeStep(25200, 28800, 2.6, 2.6, 6.6, 0);
            builder->AddTimeStep(28800, 32400, 2.4, 2.5, 6.3, 0);
            builder->AddTimeStep(32400, 36000, 2, 2.4, 6.2, 0);

            builder->AddDikeProfileSegment(0, 0, 30, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization2()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(-3600, -2880, 2, 1, 4, 0);
            builder->AddTimeStep(-2880, -1440, 2.2, 1.5, 5, 0);
            builder->AddTimeStep(-1440, 720, 2.4, 2, 5.5, 0);
            builder->AddTimeStep(720, 3600, 2.6, 2.4, 6, 0);
            builder->AddTimeStep(3600, 7200, 2.8, 2.5, 6.2, 0);
            builder->AddTimeStep(7200, 11520, 3, 2.6, 6.3, 0);
            builder->AddTimeStep(11520, 16560, 2.8, 2.7, 6.5, 0);
            builder->AddTimeStep(16560, 22320, 2.6, 2.6, 6.6, 0);
            builder->AddTimeStep(22320, 28800, 2.4, 2.5, 6.3, 0);
            builder->AddTimeStep(28800, 36000, 2, 2.4, 6.2, 0);

            builder->AddDikeProfileSegment(0, 0, 30, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(30, CharacteristicPointType::OuterCrest);

            return builder;
        }

        [[nodiscard]]
        static unique_ptr<CalculationInputBuilder> CreateBuilderForSchematization3()
        {
            auto builder = make_unique<CalculationInputBuilder>();

            builder->AddTimeStep(0, 3600, 2, 1, 4, 0);
            builder->AddTimeStep(3600, 7200, 2.2, 1.5, 5, 0);
            builder->AddTimeStep(7200, 10800, 2.4, 2, 5.5, 0);
            builder->AddTimeStep(10800, 14400, 2.6, 2.4, 6, 0);
            builder->AddTimeStep(14400, 18000, 2.8, 2.5, 6.2, 0);
            builder->AddTimeStep(18000, 21600, 3, 2.6, 6.3, 0);
            builder->AddTimeStep(21600, 25200, 2.8, 2.7, 6.5, 0);
            builder->AddTimeStep(25200, 28800, 2.6, 2.6, 6.6, 0);
            builder->AddTimeStep(28800, 32400, 2.4, 2.5, 6.3, 0);
            builder->AddTimeStep(32400, 36000, 2, 2.4, 6.2, 0);

            builder->AddDikeProfileSegment(0, 0, 8, 2);
            builder->AddDikeProfileSegment(8, 2, 17, 3);
            builder->AddDikeProfileSegment(17, 3, 35, 7.5);

            builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
            builder->AddDikeProfilePointData(8, CharacteristicPointType::CrestOuterBerm);
            builder->AddDikeProfilePointData(17, CharacteristicPointType::NotchOuterBerm);
            builder->AddDikeProfilePointData(35, CharacteristicPointType::OuterCrest);

            return builder;
        }
    };

    #pragma region Schematization 1

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 28730;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.090455071141477, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000);

        locationConstructionProperties->SetInitialDamage(make_unique<double>(0.4));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 21784;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.5994630284574629, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.15, 18000);

        locationConstructionProperties->SetThicknessSubLayer(make_unique<double>(0.18));
        locationConstructionProperties->SetElasticModulusSubLayer(make_unique<double>(15000));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 24186;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.4504822396893404, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.3, 18000);

        locationConstructionProperties->SetImpactFactors(make_unique<vector<pair<double, double>>>(vector
            {
                pair(0.4, 0.349),
                pair(0.8, 0.123),
                pair(1.2, 0.152),
                pair(1.6, 0.125),
                pair(2.0, 0.088),
                pair(2.4, 0.059),
                pair(2.8, 0.038),
                pair(3.2, 0.024),
                pair(3.6, 0.016),
                pair(4.0, 0.01),
                pair(4.4, 0.007),
                pair(4.8, 0.004),
                pair(5.2, 0.003),
                pair(5.6, 0.002),
                pair(6.0, 0.001)
            }));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 28534;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.1209751340365248, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.38, 18000);

        locationConstructionProperties->SetDepthFactors(make_unique<vector<pair<double, double>>>(vector
            {
                pair(-0.99, 0.00009647),
                pair(-0.9, 0.0007544),
                pair(-0.81, 0.004299),
                pair(-0.72, 0.01785),
                pair(-0.63, 0.05403),
                pair(-0.54, 0.1192),
                pair(-0.45, 0.1916),
                pair(-0.36, 0.2244),
                pair(-0.27, 0.1916),
                pair(-0.18, 0.1192),
                pair(-0.09, 0.05403),
                pair(0.0, 0.01785),
                pair(0.09, 0.004299),
                pair(0.18, 0.0007544),
                pair(0.27, 0.00009647)
            }));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 22915;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.330223366658833, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.45, 18000);

        locationConstructionProperties->SetWidthFactors(make_unique<vector<pair<double, double>>>(vector
            {
                pair(0.1, 0.0),
                pair(0.25, 0.018),
                pair(0.4, 0.09),
                pair(0.55, 0.153),
                pair(0.7, 0.168),
                pair(0.85, 0.15),
                pair(1.0, 0.119),
                pair(1.15, 0.089),
                pair(1.3, 0.064),
                pair(1.45, 0.045),
                pair(1.6, 0.031),
                pair(1.75, 0.022),
                pair(1.9, 0.015),
                pair(2.05, 0.01),
                pair(2.2, 0.007)
            }));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 24516;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.3929836399508819, &expectedTimeOfFailure);
    }

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization1();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.35, 18000);

        locationConstructionProperties->SetStiffnessRelationNu(make_unique<double>(0.3));
        locationConstructionProperties->SetFatigueAlpha(make_unique<double>(0.4));
        locationConstructionProperties->SetFatigueBeta(make_unique<double>(4.5));
        locationConstructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0.9));
        locationConstructionProperties->SetImpactNumberC(make_unique<double>(0.95));
        locationConstructionProperties->SetDensityOfWater(make_unique<double>(1000));

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 25376;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.286077744433424, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 2

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization2();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 16415;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.4248173105992974, &expectedTimeOfFailure);
    }

    #pragma endregion

    #pragma region Schematization 3

    TEST_F(AsphaltRevetmentWaveImpactCalculationTest,
           GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult)
    {
        // Given
        const auto builder = CreateBuilderForSchematization3();

        auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            12.5, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

        builder->AddAsphaltWaveImpactLocation(move(locationConstructionProperties));

        const auto calculationInput = builder->Build();

        // When
        const Calculator calculator(*calculationInput->GetData());

        // Then
        constexpr int expectedTimeOfFailure = 28730;

        AssertOutput(calculator, calculationInput->GetData()->GetLocationDependentInputItems(), 1.090455071141477, &expectedTimeOfFailure);
    }

    #pragma endregion
}

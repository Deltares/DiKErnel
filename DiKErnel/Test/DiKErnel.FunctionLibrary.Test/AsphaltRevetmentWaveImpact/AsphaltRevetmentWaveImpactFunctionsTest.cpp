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

#include "AsphaltRevetmentWaveImpactFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto logFailureTension = 0.193124598;
        constexpr auto averageNumberOfWaves = 6492.937853;
        constexpr auto maximumPeakStress = 0.0160884;
        constexpr auto stiffnessRelation = 1.185626183;
        constexpr auto computationalThickness = 0.16;
        constexpr auto outerSlope = 0.232914161;

        const vector widthFactors
        {
            pair(0.1, 0.0392),
            pair(0.2, 0.0738),
            pair(0.3, 0.1002),
            pair(0.4, 0.1162),
            pair(0.5, 0.1213),
            pair(0.6, 0.1168),
            pair(0.7, 0.1051),
            pair(0.8, 0.089),
            pair(0.9, 0.0712),
            pair(1.0, 0.0541),
            pair(1.1, 0.0391),
            pair(1.2, 0.0269),
            pair(1.3, 0.0216),
            pair(1.4, 0.015),
            pair(1.5, 0.0105)
        };

        const vector depthFactors
        {
            pair(-1.0, 0.0244),
            pair(-0.875, 0.0544),
            pair(-0.75, 0.0938),
            pair(-0.625, 0.1407),
            pair(-0.5, 0.1801),
            pair(-0.375, 0.1632),
            pair(-0.25, 0.1426),
            pair(-0.125, 0.0994),
            pair(0.0, 0.06),
            pair(0.125, 0.0244),
            pair(0.25, 0.0169)
        };

        const vector impactFactors
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

        constexpr auto z = 2.988;
        constexpr auto waterLevel = 3.8;
        constexpr auto waveHeightHm0 = 1.6;
        constexpr auto fatigueAlpha = 0.42;
        constexpr auto fatigueBeta = 4.76;
        constexpr auto impactNumberC = 1.0;

        // Call
        const auto incrementDamage = AsphaltRevetmentWaveImpactFunctions::IncrementDamage(
            logFailureTension,
            averageNumberOfWaves,
            maximumPeakStress,
            stiffnessRelation,
            computationalThickness,
            outerSlope,
            widthFactors,
            depthFactors,
            impactFactors,
            z,
            waterLevel,
            waveHeightHm0,
            fatigueAlpha,
            fatigueBeta,
            impactNumberC);

        // Assert
        ASSERT_DOUBLE_EQ(7.94813500019044, incrementDamage);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, LogFailureTension_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto failureTension = 1.56;

        // Call
        const auto logFailureTension = AsphaltRevetmentWaveImpactFunctions::LogFailureTension(
            failureTension);

        // Assert
        ASSERT_DOUBLE_EQ(0.19312459835446161, logFailureTension);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, MaximumPeakStress_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto waveHeightHm0 = 1.6;
        constexpr auto gravitationalAcceleration = 9.81;
        constexpr auto densityOfWater = 1025;

        // Call
        const auto maximumPeakStress = AsphaltRevetmentWaveImpactFunctions::MaximumPeakStress(
            waveHeightHm0,
            gravitationalAcceleration,
            densityOfWater);

        // Assert
        ASSERT_DOUBLE_EQ(0.0160884, maximumPeakStress);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, StiffnessRelation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto computationalThickness = 0.16;
        constexpr auto equivalentElasticModulus = 18214;
        constexpr auto soilElasticity = 56.0;
        constexpr auto stiffnessRelationNu = 0.35;

        // Call
        const auto stiffnessRelation = AsphaltRevetmentWaveImpactFunctions::StiffnessRelation(
            computationalThickness,
            equivalentElasticModulus,
            soilElasticity,
            stiffnessRelationNu);

        // Assert
        ASSERT_DOUBLE_EQ(1.1856261832690844, stiffnessRelation);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, ComputationalThickness_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto thicknessUpperLayer = 0.16;
        constexpr auto thicknessSubLayer = 0.23;
        constexpr auto elasticModulusUpperLayer = 18214;
        constexpr auto elasticModulusSubLayer = 19214;

        // Call
        const auto computationalThickness = AsphaltRevetmentWaveImpactFunctions::ComputationalThickness(
            thicknessUpperLayer,
            thicknessSubLayer,
            elasticModulusUpperLayer,
            elasticModulusSubLayer);

        // Assert
        ASSERT_DOUBLE_EQ(0.387174648559827, computationalThickness);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsTest, OuterSlope_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto slopeLowerPosition = 2.4;
        constexpr auto slopeLowerLevel = 1.75;
        constexpr auto slopeUpperPosition = 10.2;
        constexpr auto slopeUpperLevel = 2.95;

        // Call
        const auto outerSlope = AsphaltRevetmentWaveImpactFunctions::OuterSlope(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                                slopeUpperLevel);

        // Assert
        ASSERT_DOUBLE_EQ(0.153846153846154, outerSlope);
    }
}

// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "AsphaltRevetmentWaveImpact.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto logFailureTension = 0.193124598;
        const auto averageNumberOfWaves = 6492.937853;
        const auto maximumPeakStress = 0.0160884;
        const auto stiffnessRelation = 1.185626183;
        const auto computationalThickness = 0.16;
        const auto outerSlope = 0.232914161;

        const vector widthFactors
        {
            tuple(0.1, 0.0392),
            tuple(0.2, 0.0738),
            tuple(0.3, 0.1002),
            tuple(0.4, 0.1162),
            tuple(0.5, 0.1213),
            tuple(0.6, 0.1168),
            tuple(0.7, 0.1051),
            tuple(0.8, 0.089),
            tuple(0.9, 0.0712),
            tuple(1.0, 0.0541),
            tuple(1.1, 0.0391),
            tuple(1.2, 0.0269),
            tuple(1.3, 0.0216),
            tuple(1.4, 0.015),
            tuple(1.5, 0.0105)
        };

        const vector depthFactors
        {
            tuple(-1.0, 0.0244),
            tuple(-0.875, 0.0544),
            tuple(-0.75, 0.0938),
            tuple(-0.625, 0.1407),
            tuple(-0.5, 0.1801),
            tuple(-0.375, 0.1632),
            tuple(-0.25, 0.1426),
            tuple(-0.125, 0.0994),
            tuple(0.0, 0.06),
            tuple(0.125, 0.0244),
            tuple(0.25, 0.0169)
        };

        const vector impactFactors
        {
            tuple(2.0, 0.039),
            tuple(2.4, 0.1),
            tuple(2.8, 0.18),
            tuple(3.2, 0.235),
            tuple(3.6, 0.2),
            tuple(4.0, 0.13),
            tuple(4.4, 0.08),
            tuple(4.8, 0.02),
            tuple(5.2, 0.01),
            tuple(5.6, 0.005),
            tuple(6.0, 0.001)
        };

        const auto positionZ = 2.988;
        const auto waterLevel = 3.8;
        const auto waveHeightHm0 = 1.6;
        const auto fatigueAlpha = 0.42;
        const auto fatigueBeta = 4.76;
        const auto impactNumberC = 1.0;

        // Call
        const auto incrementDamage = AsphaltRevetmentWaveImpact::IncrementDamage(
            logFailureTension,
            averageNumberOfWaves,
            maximumPeakStress,
            stiffnessRelation,
            computationalThickness,
            outerSlope,
            widthFactors,
            depthFactors,
            impactFactors,
            positionZ,
            waterLevel,
            waveHeightHm0,
            fatigueAlpha,
            fatigueBeta,
            impactNumberC);

        // Assert
        ASSERT_DOUBLE_EQ(7.94813500019044, incrementDamage);
    }

    TEST(AsphaltRevetmentWaveImpactTest, LogFailureTension_ValidInput_ExpectedValue)
    {
        // Setup
        const auto failureTension = 1.56;

        // Call
        const auto logFailureTension = AsphaltRevetmentWaveImpact::LogFailureTension(
            failureTension);

        // Assert
        ASSERT_DOUBLE_EQ(0.19312459835446161, logFailureTension);
    }

    TEST(AsphaltRevetmentWaveImpactTest, MaximumPeakStress_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeightHm0 = 1.6;
        const auto gravitationalAcceleration = 9.81;
        const auto densityOfWater = 1025;

        // Call
        const auto maximumPeakStress = AsphaltRevetmentWaveImpact::MaximumPeakStress(
            waveHeightHm0,
            gravitationalAcceleration,
            densityOfWater);

        // Assert
        ASSERT_DOUBLE_EQ(0.0160884, maximumPeakStress);
    }

    TEST(AsphaltRevetmentWaveImpactTest, StiffnessRelation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto computationalThickness = 0.16;
        const auto equivalentElasticModulus = 18214;
        const auto soilElasticity = 56.0;
        const auto stiffnessRelationNu = 0.35;

        // Call
        const auto stiffnessRelation = AsphaltRevetmentWaveImpact::StiffnessRelation(
            computationalThickness,
            equivalentElasticModulus,
            soilElasticity,
            stiffnessRelationNu);

        // Assert
        ASSERT_DOUBLE_EQ(1.1856261832690844, stiffnessRelation);
    }

    TEST(AsphaltRevetmentWaveImpactTest, ComputationalThickness_ValidInput_ExpectedValue)
    {
        // Setup
        const auto thicknessUpperLayer = 0.16;
        const auto thicknessSubLayer = 0.23;
        const auto elasticModulusUpperLayer = 18214;
        const auto elasticModulusSubLayer = 19214;

        // Call
        const auto computationalThickness = AsphaltRevetmentWaveImpact::ComputationalThickness(
            thicknessUpperLayer,
            thicknessSubLayer,
            elasticModulusUpperLayer,
            elasticModulusSubLayer);

        // Assert
        ASSERT_DOUBLE_EQ(0.387174648559827, computationalThickness);
    }
}

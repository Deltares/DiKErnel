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

#include "AssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace TestUtil;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupRayleighLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        const string name = "Test";
        const auto x = 0.1;
        const auto outerSlope = 0.2;
        const auto positionZ = 0.3;

        // Call
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(name, x, outerSlope, positionZ, topLayerType);

        // Assert
        AssertHelper::AssertIsInstanceOf<GrassRevetmentWaveRunupLocationConstructionProperties>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(outerSlope, constructionProperties.GetOuterSlope());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalCumulativeOverload());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalFrontVelocity());
        ASSERT_EQ(nullptr, constructionProperties.GetIncreasedLoadTransitionAlphaM());
        ASSERT_EQ(nullptr, constructionProperties.GetReducedStrengthTransitionAlphaS());
        ASSERT_EQ(nullptr, constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PAru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PBru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PCru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PGammab());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactAbeta());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactBetamax());
        ASSERT_EQ(nullptr, constructionProperties.GetFixedNumberOfWaves());
        ASSERT_EQ(nullptr, constructionProperties.GetFrontVelocityCu());
    }

    TEST(GrassRevetmentWaveRunupRayleighLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        const string name = "Test";
        const auto x = 0.1;
        const auto outerSlope = 0.2;
        const auto positionZ = 0.3;
        const auto initialDamage = 0.4;
        const auto failureNumber = 0.5;
        const auto criticalCumulativeOverload = 0.6;
        const auto criticalFrontVelocity = 0.7;
        const auto increasedLoadTransitionAlphaM = 0.8;
        const auto reducedStrengthTransitionAlphaS = 0.9;
        const auto averageNumberOfWavesCtm = 1.0;
        const auto representativeWaveRunup2PAru = 1.1;
        const auto representativeWaveRunup2PBru = 1.2;
        const auto representativeWaveRunup2PCru = 1.3;
        const auto representativeWaveRunup2PGammab = 1.4;
        const auto representativeWaveRunup2PGammaf = 1.5;
        const auto waveAngleImpactAbeta = 1.6;
        const auto waveAngleImpactBetamax = 1.7;
        const auto fixedNumberOfWaves = 18;
        const auto frontVelocityCu = 1.9;

        GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(name, x, outerSlope, positionZ, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetRepresentativeWaveRunup2PAru(make_unique<double>(representativeWaveRunup2PAru));
        constructionProperties.SetRepresentativeWaveRunup2PBru(make_unique<double>(representativeWaveRunup2PBru));
        constructionProperties.SetRepresentativeWaveRunup2PCru(make_unique<double>(representativeWaveRunup2PCru));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(make_unique<double>(representativeWaveRunup2PGammab));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(make_unique<double>(representativeWaveRunup2PGammaf));
        constructionProperties.SetWaveAngleImpactAbeta(make_unique<double>(waveAngleImpactAbeta));
        constructionProperties.SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));
        constructionProperties.SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCu(make_unique<double>(frontVelocityCu));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(outerSlope, constructionProperties.GetOuterSlope());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(criticalCumulativeOverload, *constructionProperties.GetCriticalCumulativeOverload());
        ASSERT_DOUBLE_EQ(criticalFrontVelocity, *constructionProperties.GetCriticalFrontVelocity());
        ASSERT_DOUBLE_EQ(increasedLoadTransitionAlphaM, *constructionProperties.GetIncreasedLoadTransitionAlphaM());
        ASSERT_DOUBLE_EQ(reducedStrengthTransitionAlphaS, *constructionProperties.GetReducedStrengthTransitionAlphaS());
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, *constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2PAru, *constructionProperties.GetRepresentativeWaveRunup2PAru());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2PBru, *constructionProperties.GetRepresentativeWaveRunup2PBru());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2PCru, *constructionProperties.GetRepresentativeWaveRunup2PCru());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2PGammab, *constructionProperties.GetRepresentativeWaveRunup2PGammab());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2PGammaf, *constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        ASSERT_DOUBLE_EQ(waveAngleImpactAbeta, *constructionProperties.GetWaveAngleImpactAbeta());
        ASSERT_DOUBLE_EQ(waveAngleImpactBetamax, *constructionProperties.GetWaveAngleImpactBetamax());
        ASSERT_EQ(fixedNumberOfWaves, *constructionProperties.GetFixedNumberOfWaves());
        ASSERT_DOUBLE_EQ(frontVelocityCu, *constructionProperties.GetFrontVelocityCu());
    }
}

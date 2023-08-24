// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.Integration.Test.Data
{
    TEST(GrassRevetmentWaveRunupLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;

        // Call
        const GrassRevetmentWaveRunupLocationConstructionPropertiesMock constructionProperties(x, outerSlope, topLayerType);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(outerSlope, constructionProperties.GetOuterSlope());
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
    }

    TEST(GrassRevetmentWaveRunupLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;
        constexpr auto initialDamage = 0.3;
        constexpr auto failureNumber = 0.4;
        constexpr auto criticalCumulativeOverload = 0.5;
        constexpr auto criticalFrontVelocity = 0.6;
        constexpr auto increasedLoadTransitionAlphaM = 0.7;
        constexpr auto reducedStrengthTransitionAlphaS = 0.8;
        constexpr auto averageNumberOfWavesCtm = 0.9;
        constexpr auto representativeWaveRunup2PAru = 1.0;
        constexpr auto representativeWaveRunup2PBru = 1.1;
        constexpr auto representativeWaveRunup2PCru = 1.2;
        constexpr auto representativeWaveRunup2PGammab = 1.3;
        constexpr auto representativeWaveRunup2PGammaf = 1.4;
        constexpr auto waveAngleImpactAbeta = 1.5;
        constexpr auto waveAngleImpactBetamax = 1.6;

        GrassRevetmentWaveRunupLocationConstructionPropertiesMock constructionProperties(x, outerSlope, topLayerType);

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

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(outerSlope, constructionProperties.GetOuterSlope());
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
    }
}

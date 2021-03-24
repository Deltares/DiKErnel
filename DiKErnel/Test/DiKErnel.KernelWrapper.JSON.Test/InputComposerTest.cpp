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

#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>

#include "InputComposer.h"
#include "InputData.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    using namespace std;
    using namespace testing;

    struct InputComposerTest : Test
    {
        const string _filePathWithAllParameters =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "inputWithAllParameters.json").string();

        const string _filePathWithMandatoryParameters =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "inputWithMandatoryParameters.json").string();

        void AssertCalculationData(
            const CalculationData& calculationData) const
        {
            vector<int> expectedValues;

            expectedValues.push_back(0);
            expectedValues.push_back(100);
            expectedValues.push_back(500);
            expectedValues.push_back(800);
            expectedValues.push_back(1200);
            expectedValues.push_back(2000);

            ASSERT_EQ(expectedValues, calculationData.GetTimes());
        }

        void AssertHydraulicLoads(
            const HydraulicLoads& hydraulicLoads) const
        {
            const auto& boundaryConditionsPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[0].get(), 0.1, 0.5, 2.0, -10.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[1].get(), 0.5, 0.8, 6.0, -5.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[2].get(), 1.15, 1.2, 6.0, 0.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[3].get(), 1.77, 1.5, 7.0, 7.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[4].get(), 2.0, 0.5, 4.0, 8.0);
        }

        void AssertBoundaryConditionsForTimeStep(
            const BoundaryConditionsPerTimeStep& boundaryConditionsForTimeStep,
            const double expectedWaterLevel,
            const double expectedWaveHeightHm0,
            const double expectedWavePeriodTm10,
            const double expectedWaveAngle) const
        {
            ASSERT_DOUBLE_EQ(expectedWaterLevel, boundaryConditionsForTimeStep.GetWaterLevel());
            ASSERT_DOUBLE_EQ(expectedWaveHeightHm0, boundaryConditionsForTimeStep.GetWaveHeightHm0());
            ASSERT_DOUBLE_EQ(expectedWavePeriodTm10, boundaryConditionsForTimeStep.GetWavePeriodTm10());
            ASSERT_DOUBLE_EQ(expectedWaveAngle, boundaryConditionsForTimeStep.GetWaveAngle());
        }

        void AssertCalculationLocations(
            const vector<reference_wrapper<CalculationLocation>>& calculationLocations,
            const double expectedCriticalDamageLocation1,
            const double expectedCriticalDamageLocation2) const
        {
            AssertCalculationLocation(calculationLocations[0].get(), "LocatieZwak", "Noorse Steen", 1.65, 0.3,
                                      0.0, expectedCriticalDamageLocation1, "NatuurSteen",
                                      2.9, 4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 0.1, 0.6, 4.0, 0.1,
                                      0.2, 4.0, 0.42, 0.9, 0.96, 0.11, 78.0, 0.25, 0.9);
            AssertCalculationLocation(calculationLocations[1].get(), "LocatieSterk", "Noorse Steen", 1.65, 0.7,
                                      0.1, expectedCriticalDamageLocation2, "NatuurSteen",
                                      2.9, 4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 0.1, 0.6, 4.0, 0.1,
                                      0.2, 4.0, 0.42, 0.9, 0.96, 0.11, 78.0, 0.3, 1.0);
        }

        void AssertCalculationLocation(
            const CalculationLocation& calculationLocation,
            const string& expectedName,
            const string& expectedTypeTopLayer,
            const double expectedRelativeDensity,
            const double expectedThicknessTopLayer,
            const double expectedInitialDamage,
            const double expectedCriticalDamage,
            const string& expectedCalculationMethodSort,
            const double expectedXIb,
            const double expectedAp,
            const double expectedBp,
            const double expectedCp,
            const double expectedNp,
            const double expectedAs,
            const double expectedBs,
            const double expectedCs,
            const double expectedNs,
            const double expectedAul,
            const double expectedBul,
            const double expectedCul,
            const double expectedAll,
            const double expectedBll,
            const double expectedCll,
            const double expectedAsmax,
            const double expectedBsmax,
            const double expectedAwi,
            const double expectedBwi,
            const double expectedBetamax,
            const double expectedTanA,
            const double expectedPositionZ) const
        {
            ASSERT_EQ(expectedName, calculationLocation.GetName());

            AssertDamageVariables(
                calculationLocation.GetDamageVariables(),
                expectedInitialDamage,
                expectedCriticalDamage);

            AssertRevetment(
                calculationLocation.GetRevetment(),
                expectedTypeTopLayer,
                expectedRelativeDensity,
                expectedThicknessTopLayer,
                expectedCalculationMethodSort,
                expectedXIb,
                expectedAp,
                expectedBp,
                expectedCp,
                expectedNp,
                expectedAs,
                expectedBs,
                expectedCs,
                expectedNs,
                expectedAul,
                expectedBul,
                expectedCul,
                expectedAll,
                expectedBll,
                expectedCll,
                expectedAsmax,
                expectedBsmax,
                expectedAwi,
                expectedBwi,
                expectedBetamax
            );

            AssertProfileSchematization(
                calculationLocation.GetProfileSchematization(),
                expectedTanA,
                expectedPositionZ);
        }

        void AssertDamageVariables(
            const DamageVariables& damageVariables,
            const double expectedInitialDamage,
            const double expectedCriticalDamage)
        const
        {
            ASSERT_DOUBLE_EQ(expectedInitialDamage, damageVariables.GetInitialDamage());
            ASSERT_DOUBLE_EQ(expectedCriticalDamage, damageVariables.GetCriticalDamage());
        }

        void AssertRevetment(
            const Revetment& revetment,
            const string& expectedTypeTopLayer,
            const double expectedRelativeDensity,
            const double expectedThicknessTopLayer,
            const string& expectedCalculationMethodSort,
            const double expectedXIb,
            const double expectedAp,
            const double expectedBp,
            const double expectedCp,
            const double expectedNp,
            const double expectedAs,
            const double expectedBs,
            const double expectedCs,
            const double expectedNs,
            const double expectedAul,
            const double expectedBul,
            const double expectedCul,
            const double expectedAll,
            const double expectedBll,
            const double expectedCll,
            const double expectedAsmax,
            const double expectedBsmax,
            const double expectedAwi,
            const double expectedBwi,
            const double expectedBetamax
        ) const
        {
            ASSERT_EQ(expectedTypeTopLayer, revetment.GetTypeTopLayer());
            ASSERT_DOUBLE_EQ(expectedRelativeDensity, revetment.GetRelativeDensity());
            ASSERT_DOUBLE_EQ(expectedThicknessTopLayer, revetment.GetThicknessTopLayer());

            AssertCalculationMethod(
                revetment.GetCalculationMethod(),
                expectedCalculationMethodSort,
                expectedXIb,
                expectedAp,
                expectedBp,
                expectedCp,
                expectedNp,
                expectedAs,
                expectedBs,
                expectedCs,
                expectedNs,
                expectedAul,
                expectedBul,
                expectedCul,
                expectedAll,
                expectedBll,
                expectedCll,
                expectedAsmax,
                expectedBsmax,
                expectedAwi,
                expectedBwi,
                expectedBetamax
            );
        }

        void AssertCalculationMethod(
            const CalculationMethod& calculationMethod,
            const string& expectedCalculationMethodSort,
            const double expectedXIb,
            const double expectedAp,
            const double expectedBp,
            const double expectedCp,
            const double expectedNp,
            const double expectedAs,
            const double expectedBs,
            const double expectedCs,
            const double expectedNs,
            const double expectedAul,
            const double expectedBul,
            const double expectedCul,
            const double expectedAll,
            const double expectedBll,
            const double expectedCll,
            const double expectedAsmax,
            const double expectedBsmax,
            const double expectedAwi,
            const double expectedBwi,
            const double expectedBetamax

        ) const
        {
            ASSERT_EQ(expectedCalculationMethodSort, calculationMethod.GetCalculationMethodSort());

            AssertHydraulicLoadOnNaturalStone(
                calculationMethod.GetHydraulicLoadOnNaturalStone(),
                expectedXIb,
                expectedAp,
                expectedBp,
                expectedCp,
                expectedNp,
                expectedAs,
                expectedBs,
                expectedCs,
                expectedNs
            );

            AssertUpperLimitLoadingOfNaturalStone(
                calculationMethod.GetUpperLimitLoadingOfNaturalStone(),
                expectedAul,
                expectedBul,
                expectedCul
            );
            AssertLowerLimitLoadingOfNaturalStone(
                calculationMethod.GetLowerLimitLoadingOfNaturalStone(),
                expectedAll,
                expectedBll,
                expectedCll
            );
            AssertDistanceMaximumWaveElevationNaturalStone(
                calculationMethod.GetDistanceMaximumWaveElevationNaturalStone(),
                expectedAsmax,
                expectedBsmax
            );
            AssertNormativeWidthOfWaveImpact(
                calculationMethod.GetNormativeWidthOfWaveImpact(),
                expectedAwi,
                expectedBwi
            );
            AssertWaveAngleImpact(
                calculationMethod.GetWaveAngleImpact(),
                expectedBetamax
            );
        }

        void AssertHydraulicLoadOnNaturalStone(
            const HydraulicLoadOnNaturalStone& hydraulicLoadOnNaturalStone,
            const double expectedXIb,
            const double expectedAp,
            const double expectedBp,
            const double expectedCp,
            const double expectedNp,
            const double expectedAs,
            const double expectedBs,
            const double expectedCs,
            const double expectedNs
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedXIb, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneXIb());
            ASSERT_DOUBLE_EQ(expectedAp, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneAp());
            ASSERT_DOUBLE_EQ(expectedBp, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneBp());
            ASSERT_DOUBLE_EQ(expectedCp, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneCp());
            ASSERT_DOUBLE_EQ(expectedNp, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneNp());
            ASSERT_DOUBLE_EQ(expectedAs, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneAs());
            ASSERT_DOUBLE_EQ(expectedBs, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneBs());
            ASSERT_DOUBLE_EQ(expectedCs, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneCs());
            ASSERT_DOUBLE_EQ(expectedNs, hydraulicLoadOnNaturalStone.GetHydraulicLoadOnNaturalStoneNs());
        }

        void AssertUpperLimitLoadingOfNaturalStone(
            const UpperLimitLoadingOfNaturalStone& upperLimitLoadingOfNaturalStone,
            const double expectedAul,
            const double expectedBul,
            const double expectedCul
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedAul, upperLimitLoadingOfNaturalStone.GetUpperLimitLoadingOfNaturalStoneAul());
            ASSERT_DOUBLE_EQ(expectedBul, upperLimitLoadingOfNaturalStone.GetUpperLimitLoadingOfNaturalStoneBul());
            ASSERT_DOUBLE_EQ(expectedCul, upperLimitLoadingOfNaturalStone.GetUpperLimitLoadingOfNaturalStoneCul());
        }

        void AssertLowerLimitLoadingOfNaturalStone(
            const LowerLimitLoadingOfNaturalStone& lowerLimitLoadingOfNaturalStone,
            const double expectedAll,
            const double expectedBll,
            const double expectedCll
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedAll, lowerLimitLoadingOfNaturalStone.GetLowerLimitLoadingOfNaturalStoneAll());
            ASSERT_DOUBLE_EQ(expectedBll, lowerLimitLoadingOfNaturalStone.GetLowerLimitLoadingOfNaturalStoneBll());
            ASSERT_DOUBLE_EQ(expectedCll, lowerLimitLoadingOfNaturalStone.GetLowerLimitLoadingOfNaturalStoneCll());
        }

        void AssertDistanceMaximumWaveElevationNaturalStone(
            const DistanceMaximumWaveElevationNaturalStone& distanceMaximumWaveElevationNaturalStone,
            const double expectedAsmax,
            const double expectedBsmax
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedAsmax, distanceMaximumWaveElevationNaturalStone.GetDistanceMaximumWaveElevationNaturalStoneAsmax());
            ASSERT_DOUBLE_EQ(expectedBsmax, distanceMaximumWaveElevationNaturalStone.GetDistanceMaximumWaveElevationNaturalStoneBsmax());
        }

        void AssertNormativeWidthOfWaveImpact(
            const NormativeWidthOfWaveImpact& normativeWidthOfWaveImpact,
            const double expectedAwi,
            const double expectedBwi
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedAwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactNaturalStoneAwi());
            ASSERT_DOUBLE_EQ(expectedBwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactNaturalStoneBwi());
        }

        void AssertWaveAngleImpact(
            const WaveAngleImpact& waveAngleImpact,
            const double expectedBetamax
        ) const
        {
            ASSERT_DOUBLE_EQ(expectedBetamax, waveAngleImpact.GetWaveAngleImpactOnNaturalStoneBetamax());
        }

        void AssertProfileSchematization(
            const ProfileSchematization& profileSchematization,
            const double expectedTanA,
            const double expectedPositionZ) const
        {
            ASSERT_DOUBLE_EQ(expectedTanA, profileSchematization.GetTanA());
            ASSERT_DOUBLE_EQ(expectedPositionZ, profileSchematization.GetPositionZ());
        }
    };

    TEST_F(InputComposerTest, GivenFileWithAllInputParametersAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(_filePathWithAllParameters);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations(), 1.0, 1.05);
    }

    TEST_F(InputComposerTest, GivenFileWithMandatoryInputParametersAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(_filePathWithMandatoryParameters);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations(), 1.0, 1.0);
    }
}
